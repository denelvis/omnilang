use clap::{Parser, Subcommand};
use colored::Colorize;
use std::path::Path;
use std::path::PathBuf;

/// OmniLang — the specification language for AI-native development.
///
/// Write specs, not code. Let AI agents generate verified implementations.
#[derive(Parser)]
#[command(name = "omni", version, about, long_about = None)]
#[command(propagate_version = true)]
struct Cli {
    #[command(subcommand)]
    command: Commands,

    /// Enable verbose output
    #[arg(long, global = true)]
    verbose: bool,

    /// Suppress all output except errors
    #[arg(long, global = true)]
    quiet: bool,
}

#[derive(Subcommand)]
enum Commands {
    /// Validate OmniLang specifications (no AI, no cost).
    Check {
        /// Path to .omni files or directory to check.
        #[arg(default_value = ".")]
        path: String,

        /// Output format: human (default) or json
        #[arg(long, default_value = "human")]
        format: String,
    },

    /// Show execution plan and estimated cost (dry run).
    Plan {
        /// Path to .omni files or directory to plan.
        #[arg(default_value = ".")]
        path: String,
    },

    /// Build: analyze → generate → verify → emit artifacts.
    Build {
        /// Path to .omni files or directory to build.
        #[arg(default_value = ".")]
        path: String,

        /// Target language for code generation.
        #[arg(long, default_value = "typescript")]
        target: String,

        /// Enable parallel multi-agent generation.
        #[arg(long)]
        parallel: bool,

        /// [DEPRECATED] Wire format. Ignored — always uses minified JSON.
        #[arg(long, default_value = "json", hide = true)]
        wire_format: String,

        /// Maximum build budget in dollars.
        #[arg(long)]
        budget: Option<f64>,
    },

    /// Initialize a new OmniLang project.
    Init {
        /// Project name (creates a directory).
        #[arg(default_value = ".")]
        name: String,
    },

    /// Verify build artifacts: parse test reports and coverage data.
    Verify {
        /// Path to the build output directory.
        #[arg(default_value = "build")]
        path: String,

        /// Print detailed compliance report.
        #[arg(long)]
        report: bool,

        /// Output format: 'human' (default) or 'json' for CI.
        #[arg(long, default_value = "human")]
        format: String,

        /// Directory to store evidence artifacts (test reports, coverage, chain.json).
        #[arg(long, default_value = "evidence")]
        evidence_dir: String,
    },
}

fn main() {
    let cli = Cli::parse();

    let exit_code = match cli.command {
        Commands::Check { path, format } => cmd_check(&path, &format, cli.verbose, cli.quiet),
        Commands::Plan { path } => cmd_plan(&path),
        Commands::Build {
            path,
            target,
            parallel,
            wire_format,
            budget,
        } => cmd_build(&path, &target, parallel, &wire_format, budget),
        Commands::Init { name } => cmd_init(&name),
        Commands::Verify {
            path,
            report,
            format,
            evidence_dir,
        } => cmd_verify(&path, report, &format, &evidence_dir),
    };

    std::process::exit(exit_code);
}

fn cmd_check(path: &str, format: &str, verbose: bool, quiet: bool) -> i32 {
    let files = collect_omni_files(path);

    if files.is_empty() {
        if !quiet {
            eprintln!(
                "{} no .omni files found in '{}'",
                "error:".red().bold(),
                path
            );
        }
        return 1;
    }

    let mut total_errors = 0;
    let mut total_warnings = 0;
    let mut _total_infos = 0;

    for file_path in &files {
        let source = match std::fs::read_to_string(file_path) {
            Ok(s) => s,
            Err(e) => {
                eprintln!(
                    "{} cannot read '{}': {}",
                    "error:".red().bold(),
                    file_path,
                    e
                );
                total_errors += 1;
                continue;
            }
        };

        // Run the full pipeline
        let (ir, diagnostics, parse_errors) = omni_analyzer::parse_and_analyze(&source);

        // Report parse errors
        for err in &parse_errors {
            if format == "json" {
                println!(
                    "{}",
                    serde_json::json!({
                        "file": file_path,
                        "level": "error",
                        "message": err.to_string(),
                    })
                );
            } else if !quiet {
                eprintln!("{} {} {}", "error:".red().bold(), file_path.dimmed(), err);
            }
            total_errors += 1;
        }

        // Report analyzer diagnostics
        for diag in &diagnostics {
            match diag.kind {
                omni_analyzer::DiagnosticKind::Error => {
                    total_errors += 1;
                    if format == "json" {
                        println!(
                            "{}",
                            serde_json::json!({
                                "file": file_path,
                                "level": "error",
                                "message": diag.message,
                            })
                        );
                    } else if !quiet {
                        eprintln!(
                            "{} {} {}",
                            "error:".red().bold(),
                            file_path.dimmed(),
                            diag.message
                        );
                    }
                }
                omni_analyzer::DiagnosticKind::Warning => {
                    total_warnings += 1;
                    if format == "json" {
                        println!(
                            "{}",
                            serde_json::json!({
                                "file": file_path,
                                "level": "warning",
                                "message": diag.message,
                            })
                        );
                    } else if !quiet {
                        eprintln!(
                            "{} {} {}",
                            "warning:".yellow().bold(),
                            file_path.dimmed(),
                            diag.message
                        );
                    }
                }
                omni_analyzer::DiagnosticKind::Info => {
                    _total_infos += 1;
                    if verbose && format != "json" {
                        eprintln!(
                            "{} {} {}",
                            "info:".blue().bold(),
                            file_path.dimmed(),
                            diag.message
                        );
                    }
                }
            }
        }

        // Print summary for this file if verbose
        if verbose
            && !quiet
            && format != "json"
            && let Some(ir) = &ir
        {
            eprintln!(
                "  {} {} types, {} services, {} RPCs, {} tests, {} metrics",
                "✓".green().bold(),
                ir.stats.type_count,
                ir.stats.service_count,
                ir.stats.rpc_count,
                ir.stats.test_count,
                ir.stats.metric_count,
            );
        }
    }

    // Final summary
    if !quiet && format != "json" {
        eprintln!();
        if total_errors == 0 {
            eprintln!(
                "{} checked {} file(s): {} error(s), {} warning(s)",
                "✅".green(),
                files.len(),
                total_errors,
                total_warnings,
            );
        } else {
            eprintln!(
                "{} checked {} file(s): {} error(s), {} warning(s)",
                "❌".red(),
                files.len(),
                total_errors,
                total_warnings,
            );
        }
    }

    if total_errors > 0 { 1 } else { 0 }
}

fn cmd_plan(path: &str) -> i32 {
    let files = collect_omni_files(path);

    if files.is_empty() {
        eprintln!(
            "{} no .omni files found in '{}'",
            "error:".red().bold(),
            path
        );
        return 1;
    }

    // Parse and analyze all files
    for file_path in &files {
        let source = match std::fs::read_to_string(file_path) {
            Ok(s) => s,
            Err(e) => {
                eprintln!(
                    "{} cannot read '{}': {}",
                    "error:".red().bold(),
                    file_path,
                    e
                );
                return 1;
            }
        };

        let (ir, diagnostics, parse_errors) = omni_analyzer::parse_and_analyze(&source);

        if !parse_errors.is_empty() {
            eprintln!("{} fix parse errors first", "error:".red().bold());
            return 1;
        }

        let has_errors = diagnostics
            .iter()
            .any(|d| d.kind == omni_analyzer::DiagnosticKind::Error);
        if has_errors {
            eprintln!("{} fix analysis errors first", "error:".red().bold());
            return 1;
        }

        if let Some(ir) = ir {
            println!("{}", "📋 Execution Plan".bold());
            println!();
            println!("  Module: {}", ir.module_path.join(".").cyan());
            println!(
                "  Types:  {} | Services: {} | RPCs: {} | Tests: {} | Metrics: {}",
                ir.stats.type_count.to_string().green(),
                ir.stats.service_count.to_string().green(),
                ir.stats.rpc_count.to_string().green(),
                ir.stats.test_count.to_string().green(),
                ir.stats.metric_count.to_string().green(),
            );
            println!();

            if !ir.services.is_empty() {
                println!("  {}", "Build order:".bold());
                for (i, service) in ir.services.iter().enumerate() {
                    println!(
                        "    {}. {} — {} RPC(s), {} constraint(s), {} metric(s)",
                        i + 1,
                        service.name.cyan(),
                        service.rpc_count,
                        service.constraint_count,
                        service.metric_count,
                    );
                }
            }
            println!();
            println!(
                "  {} Ready to build. Run 'omni build' to generate the implementation.",
                "✓".green().bold()
            );
        }
    }

    0
}

fn cmd_build(
    path: &str,
    target: &str,
    parallel: bool,
    wire_format: &str,
    budget: Option<f64>,
) -> i32 {
    println!(
        "{} Building specifications in: {}",
        "🔨".yellow(),
        path.cyan()
    );
    println!("   Target language: {}", target.green());

    if parallel {
        println!("   {} Multi-agent parallel generation", "⚡".yellow());
    }
    if wire_format != "json" {
        eprintln!(
            "{} --wire-format {} is deprecated and ignored. Using minified JSON.",
            "warning:".yellow().bold(),
            wire_format
        );
    }
    if let Some(max_budget) = budget {
        println!(
            "   {} Budget limit: ${}",
            "💰".yellow(),
            format!("{:.2}", max_budget).green()
        );
    }

    // 1. Verify node and npm are installed
    if !verify_node_installed() {
        eprintln!(
            "{} Node.js and npm are required to run the code generator. Please install them and try again.",
            "error:".red().bold()
        );
        return 1;
    }

    // 2. Find runtime directory
    let runtime_dir = match find_runtime_dir() {
        Some(dir) => dir,
        None => {
            eprintln!(
                "{} could not find the 'runtime' directory in workspace.",
                "error:".red().bold()
            );
            return 1;
        }
    };

    // 3. Auto-build runtime if necessary
    if !build_runtime_if_needed(&runtime_dir) {
        eprintln!(
            "{} failed to compile the TypeScript runtime.",
            "error:".red().bold()
        );
        return 1;
    }

    // 4. Collect and process files
    let files = collect_omni_files(path);
    if files.is_empty() {
        eprintln!(
            "{} no .omni files found in '{}'",
            "error:".red().bold(),
            path
        );
        return 1;
    }

    // Ensure cache folder exists
    let cache_dir = std::path::Path::new(".omni-cache");
    if let Err(e) = std::fs::create_dir_all(cache_dir) {
        eprintln!(
            "{} failed to create .omni-cache directory: {}",
            "error:".red().bold(),
            e
        );
        return 1;
    }

    let mut exit_code = 0;

    for file_path in &files {
        let source = match std::fs::read_to_string(file_path) {
            Ok(s) => s,
            Err(e) => {
                eprintln!(
                    "{} cannot read '{}': {}",
                    "error:".red().bold(),
                    file_path,
                    e
                );
                return 1;
            }
        };

        // Parse and analyze
        let (ir, diagnostics, parse_errors) = omni_analyzer::parse_and_analyze(&source);

        // Report parse errors
        let mut has_errors = false;
        for err in &parse_errors {
            eprintln!("{} {} {}", "error:".red().bold(), file_path.dimmed(), err);
            has_errors = true;
        }

        // Report analyzer diagnostics
        for diag in &diagnostics {
            match diag.kind {
                omni_analyzer::DiagnosticKind::Error => {
                    eprintln!(
                        "{} {} {}",
                        "error:".red().bold(),
                        file_path.dimmed(),
                        diag.message
                    );
                    has_errors = true;
                }
                omni_analyzer::DiagnosticKind::Warning => {
                    eprintln!(
                        "{} {} {}",
                        "warning:".yellow().bold(),
                        file_path.dimmed(),
                        diag.message
                    );
                }
                _ => {}
            }
        }

        if has_errors {
            return 1;
        }

        if let Some(ir) = ir {
            // Write IR to cache
            let file_stem = std::path::Path::new(file_path)
                .file_stem()
                .and_then(|s| s.to_str())
                .unwrap_or("spec");
            let ir_file_name = format!("{}_ir.json", file_stem);
            let ir_path = cache_dir.join(&ir_file_name);

            let ir_json = match serde_json::to_string_pretty(&ir) {
                Ok(json) => json,
                Err(e) => {
                    eprintln!(
                        "{} failed to serialize Spec IR: {}",
                        "error:".red().bold(),
                        e
                    );
                    return 1;
                }
            };

            if let Err(e) = std::fs::write(&ir_path, ir_json) {
                eprintln!(
                    "{} failed to write Spec IR to cache: {}",
                    "error:".red().bold(),
                    e
                );
                return 1;
            }

            println!(
                "{} Serialized Spec IR to {}",
                "✓".green().bold(),
                ir_path.to_string_lossy().cyan()
            );

            // Execute runtime
            println!("{} Invoking generator runtime...", "🚀".green());
            let mut cmd = std::process::Command::new("node");
            cmd.arg(runtime_dir.join("dist").join("index.js"))
                .arg(&ir_path)
                .arg("--output")
                .arg("build")
                .arg("--target")
                .arg(target);

            if parallel {
                cmd.arg("--parallel");
            }
            // wire_format is deprecated — always JSON, don't pass to runtime
            if let Some(max_budget) = budget {
                cmd.arg("--budget").arg(format!("{:.2}", max_budget));
            }

            let status = cmd.status();

            match status {
                Ok(stat) => {
                    if !stat.success() {
                        exit_code = stat.code().unwrap_or(1);
                        break;
                    }
                }
                Err(e) => {
                    eprintln!(
                        "{} failed to execute code generator runtime: {}",
                        "error:".red().bold(),
                        e
                    );
                    exit_code = 1;
                    break;
                }
            }
        }
    }

    exit_code
}

fn cmd_init(name: &str) -> i32 {
    let dir = Path::new(name);

    if name != "."
        && let Err(e) = std::fs::create_dir_all(dir)
    {
        eprintln!("{} cannot create directory: {}", "error:".red().bold(), e);
        return 1;
    }

    // Create omni.toml
    let config = r#"[package]
name = "my-project"
version = "0.1.0"

[build]
target = "typescript"
output_dir = "build"
"#;
    let _ = std::fs::write(dir.join("omni.toml"), config);

    // Create src/main.omni
    let _ = std::fs::create_dir_all(dir.join("src"));
    let main_omni = r#"module hello

type GreetingId = UUID

type Greeting = struct {
  id: GreetingId
  message: String
  created_at: DateTime
}

service GreetingService {
  goal: "Provide friendly greetings"

  constraints:
    - latency(p95: 100ms)

  rpc SayHello {
    inputs:
      name: String
    outputs:
      greeting: Greeting

    postconditions:
      - greeting.message != ""

    tests:
      - scenario: "Greet a user"
        given: name == "World"
        expect: greeting.message == "Hello, World!"
  }
}
"#;
    let _ = std::fs::write(dir.join("src/main.omni"), main_omni);

    // Create .gitignore
    let gitignore = "build/\ntarget/\n.omni-cache/\n";
    let _ = std::fs::write(dir.join(".gitignore"), gitignore);

    println!(
        "{} Initialized OmniLang project in '{}'",
        "✨".green(),
        name.cyan()
    );
    println!();
    println!("  Next steps:");
    println!("    {} Edit {}", "1.".dimmed(), "src/main.omni".cyan());
    println!("    {} Run  {}", "2.".dimmed(), "omni check".green());
    println!("    {} Run  {}", "3.".dimmed(), "omni build".green());
    0
}

fn cmd_verify(path: &str, report: bool, format: &str, evidence_dir: &str) -> i32 {
    let build_dir = Path::new(path);

    if !build_dir.is_dir() {
        if format == "json" {
            println!(
                "{{\"error\":\"build directory '{}' does not exist\",\"status\":\"error\"}}",
                path
            );
        } else {
            eprintln!(
                "{} build directory '{}' does not exist",
                "error:".red().bold(),
                path
            );
        }
        return 1;
    }

    if format != "json" {
        println!(
            "{} Scanning build artifacts in: {}",
            "🔍".cyan(),
            path.cyan()
        );
    }

    // 1. Scan for JUnit XML test reports
    let junit_files = find_files_by_extension(build_dir, "xml");
    let mut total_suites = 0;
    let mut total_tests = 0;
    let mut total_failures = 0;
    let mut total_errors = 0;
    let mut suite_summaries: Vec<(String, usize, usize, usize)> = Vec::new();

    for junit_path in &junit_files {
        if let Ok(content) = std::fs::read_to_string(junit_path)
            && (content.contains("<testsuite") || content.contains("<testsuites"))
        {
            let suites = parse_junit_suites(&content);
            for suite in &suites {
                total_suites += 1;
                total_tests += suite.tests;
                total_failures += suite.failures;
                total_errors += suite.errors;
                suite_summaries.push((
                    suite.name.clone(),
                    suite.tests,
                    suite.failures,
                    suite.errors,
                ));
            }
        }
    }

    // 2. Scan for LCOV coverage reports
    let lcov_files = find_files_by_extension(build_dir, "info");
    let mut coverage_lines_hit = 0usize;
    let mut coverage_lines_total = 0usize;

    for lcov_path in &lcov_files {
        if let Ok(content) = std::fs::read_to_string(lcov_path) {
            let (hit, total) = parse_lcov_summary(&content);
            coverage_lines_hit += hit;
            coverage_lines_total += total;
        }
    }

    let lcov_direct: Vec<PathBuf> = find_files_by_name(build_dir, "lcov.info");
    for lcov_path in &lcov_direct {
        if !lcov_files.contains(lcov_path)
            && let Ok(content) = std::fs::read_to_string(lcov_path)
        {
            let (hit, total) = parse_lcov_summary(&content);
            coverage_lines_hit += hit;
            coverage_lines_total += total;
        }
    }

    // 3. Store evidence artifacts in evidence/ directory
    let evidence_path = Path::new(evidence_dir);
    let _ = std::fs::create_dir_all(evidence_path);

    for junit_path in &junit_files {
        if let Some(file_name) = junit_path.file_name() {
            let _ = std::fs::copy(junit_path, evidence_path.join(file_name));
        }
    }
    for lcov_path in lcov_files.iter().chain(lcov_direct.iter()) {
        if let Some(file_name) = lcov_path.file_name() {
            let _ = std::fs::copy(lcov_path, evidence_path.join(file_name));
        }
    }

    // 4. Generate evidence/chain.json
    let all_tests_pass = total_failures == 0 && total_errors == 0;
    let coverage_pct = if coverage_lines_total > 0 {
        Some((coverage_lines_hit as f64 / coverage_lines_total as f64) * 100.0)
    } else {
        None
    };

    let chain_json = build_chain_json(
        path,
        total_suites,
        total_tests,
        total_failures,
        total_errors,
        coverage_lines_hit,
        coverage_lines_total,
        coverage_pct,
        &junit_files,
        &lcov_files,
        &lcov_direct,
    );
    let chain_path = evidence_path.join("chain.json");
    let _ = std::fs::write(&chain_path, chain_json);

    // 5. Output
    if format == "json" {
        let output = build_json_output(
            all_tests_pass,
            total_suites,
            total_tests,
            total_failures,
            total_errors,
            coverage_lines_hit,
            coverage_lines_total,
            coverage_pct,
            evidence_dir,
            &chain_path,
            &suite_summaries,
        );
        println!("{}", output);
    } else {
        print_human_report(
            path,
            report,
            evidence_dir,
            total_suites,
            total_tests,
            total_failures,
            total_errors,
            all_tests_pass,
            coverage_pct,
            coverage_lines_hit,
            coverage_lines_total,
            &junit_files,
            &suite_summaries,
        );
    }

    if total_suites > 0 && !all_tests_pass {
        1
    } else {
        0
    }
}

#[allow(clippy::too_many_arguments)]
fn build_chain_json(
    build_path: &str,
    total_suites: usize,
    total_tests: usize,
    total_failures: usize,
    total_errors: usize,
    coverage_lines_hit: usize,
    coverage_lines_total: usize,
    coverage_pct: Option<f64>,
    junit_files: &[PathBuf],
    lcov_files: &[PathBuf],
    lcov_direct: &[PathBuf],
) -> String {
    let all_tests_pass = total_failures == 0 && total_errors == 0;
    let mut chain_entries = Vec::new();

    if total_suites > 0 {
        let junit_artifacts: Vec<String> = junit_files
            .iter()
            .filter_map(|p| p.file_name().map(|n| n.to_string_lossy().to_string()))
            .collect();
        let artifacts_str = format!(
            "[{}]",
            junit_artifacts
                .iter()
                .map(|a| format!("\"{}\"", a))
                .collect::<Vec<_>>()
                .join(",")
        );
        chain_entries.push(format!(
            "{{\"constraint\":\"all tests pass\",\"evidence_type\":\"junit_xml\",\"result\":\"{}\",\"details\":{{\"suites\":{},\"tests\":{},\"failures\":{},\"errors\":{}}},\"artifacts\":{}}}",
            if all_tests_pass { "pass" } else { "fail" },
            total_suites,
            total_tests,
            total_failures,
            total_errors,
            artifacts_str
        ));
    }

    if let Some(pct) = coverage_pct {
        let lcov_artifacts: Vec<String> = lcov_files
            .iter()
            .chain(lcov_direct.iter())
            .filter_map(|p| p.file_name().map(|n| n.to_string_lossy().to_string()))
            .collect();
        let artifacts_str = format!(
            "[{}]",
            lcov_artifacts
                .iter()
                .map(|a| format!("\"{}\"", a))
                .collect::<Vec<_>>()
                .join(",")
        );
        chain_entries.push(format!(
            "{{\"constraint\":\"code coverage\",\"evidence_type\":\"lcov\",\"result\":\"{}\",\"details\":{{\"lines_hit\":{},\"lines_total\":{},\"coverage_pct\":\"{:.1}\"}},\"artifacts\":{}}}",
            if pct >= 80.0 { "pass" } else { "warn" },
            coverage_lines_hit,
            coverage_lines_total,
            pct,
            artifacts_str
        ));
    }

    format!(
        "{{\n  \"version\": \"{}\",\n  \"build_dir\": \"{}\",\n  \"chain\": [\n    {}\n  ]\n}}",
        env!("CARGO_PKG_VERSION"),
        build_path,
        chain_entries.join(",\n    ")
    )
}

#[allow(clippy::too_many_arguments)]
fn build_json_output(
    all_tests_pass: bool,
    total_suites: usize,
    total_tests: usize,
    total_failures: usize,
    total_errors: usize,
    coverage_lines_hit: usize,
    coverage_lines_total: usize,
    coverage_pct: Option<f64>,
    evidence_dir: &str,
    chain_path: &Path,
    suite_summaries: &[(String, usize, usize, usize)],
) -> String {
    let suites_json: Vec<String> = suite_summaries
        .iter()
        .map(|(name, tests, failures, errors)| {
            format!(
                "{{\"name\":\"{}\",\"tests\":{},\"failures\":{},\"errors\":{}}}",
                name, tests, failures, errors
            )
        })
        .collect();

    format!(
        "{{\n  \"status\": \"{}\",\n  \"tests\": {{\n    \"suites\": {},\n    \"total\": {},\n    \"failures\": {},\n    \"errors\": {},\n    \"pass\": {}\n  }},\n  \"coverage\": {{\n    \"lines_hit\": {},\n    \"lines_total\": {},\n    \"pct\": {}\n  }},\n  \"evidence_dir\": \"{}\",\n  \"chain_file\": \"{}\",\n  \"suites\": [{}]\n}}",
        if all_tests_pass { "pass" } else { "fail" },
        total_suites,
        total_tests,
        total_failures,
        total_errors,
        all_tests_pass,
        coverage_lines_hit,
        coverage_lines_total,
        coverage_pct.map_or("null".to_string(), |v| format!("{:.1}", v)),
        evidence_dir,
        chain_path.display(),
        suites_json.join(",")
    )
}

#[allow(clippy::too_many_arguments)]
fn print_human_report(
    path: &str,
    report: bool,
    evidence_dir: &str,
    total_suites: usize,
    total_tests: usize,
    total_failures: usize,
    total_errors: usize,
    all_tests_pass: bool,
    coverage_pct: Option<f64>,
    coverage_lines_hit: usize,
    coverage_lines_total: usize,
    junit_files: &[PathBuf],
    suite_summaries: &[(String, usize, usize, usize)],
) {
    println!();
    println!("{}", "📋 Verification Report".bold());
    println!();

    if total_suites > 0 {
        println!(
            "  {} Test Results (from {} JUnit report(s)):",
            "🧪".green(),
            junit_files.len()
        );
        println!(
            "     Suites: {} | Tests: {} | Failures: {} | Errors: {}",
            total_suites.to_string().cyan(),
            total_tests.to_string().green(),
            if total_failures > 0 {
                total_failures.to_string().red().bold()
            } else {
                total_failures.to_string().green().bold()
            },
            if total_errors > 0 {
                total_errors.to_string().red().bold()
            } else {
                total_errors.to_string().green().bold()
            },
        );

        if report {
            println!();
            for (name, tests, failures, errors) in suite_summaries {
                let status = if *failures == 0 && *errors == 0 {
                    "✓".green().bold()
                } else {
                    "✗".red().bold()
                };
                println!(
                    "     {} {} — {} test(s), {} failure(s), {} error(s)",
                    status,
                    name.cyan(),
                    tests,
                    failures,
                    errors
                );
            }
        }
        println!();
    } else {
        println!(
            "  {} No JUnit XML test reports found in '{}'",
            "⚠".yellow(),
            path
        );
        println!();
    }

    if let Some(pct) = coverage_pct {
        let coverage_str = format!("{:.1}%", pct);
        let coverage_colored = if pct >= 80.0 {
            coverage_str.green().bold()
        } else if pct >= 50.0 {
            coverage_str.yellow().bold()
        } else {
            coverage_str.red().bold()
        };
        println!(
            "  {} Code Coverage: {} ({}/{} lines)",
            "📊".green(),
            coverage_colored,
            coverage_lines_hit,
            coverage_lines_total
        );
        println!();
    } else {
        println!(
            "  {} No LCOV coverage reports found in '{}'",
            "⚠".yellow(),
            path
        );
        println!();
    }

    println!(
        "  {} Evidence stored in: {}",
        "📁".cyan(),
        evidence_dir.cyan()
    );

    if total_suites > 0 && all_tests_pass {
        println!("  {} All tests passing. Contracts verified.", "✅".green());
    } else if total_suites > 0 {
        println!(
            "  {} {} failure(s) and {} error(s) detected. Contracts not fully verified.",
            "❌".red(),
            total_failures,
            total_errors
        );
    } else {
        println!(
            "  {} No test reports found. Run 'omni build' first to generate artifacts.",
            "ℹ".blue()
        );
    }
}

/// Collect all `.omni` files from a path (file or directory).
fn collect_omni_files(path: &str) -> Vec<String> {
    let p = Path::new(path);

    if p.is_file() && path.ends_with(".omni") {
        return vec![path.to_string()];
    }

    if p.is_dir() {
        let mut files = Vec::new();
        collect_omni_files_recursive(p, &mut files);
        files.sort();
        return files;
    }

    Vec::new()
}

fn collect_omni_files_recursive(dir: &Path, files: &mut Vec<String>) {
    if let Ok(entries) = std::fs::read_dir(dir) {
        for entry in entries.flatten() {
            let path = entry.path();
            if path.is_dir() {
                collect_omni_files_recursive(&path, files);
            } else if path.extension().is_some_and(|ext| ext == "omni") {
                files.push(path.to_string_lossy().to_string());
            }
        }
    }
}

fn verify_node_installed() -> bool {
    let node_check = std::process::Command::new("node")
        .arg("-v")
        .stdout(std::process::Stdio::null())
        .stderr(std::process::Stdio::null())
        .status();
    let npm_check = std::process::Command::new("npm")
        .arg("-v")
        .stdout(std::process::Stdio::null())
        .stderr(std::process::Stdio::null())
        .status();

    matches!((node_check, npm_check), (Ok(n), Ok(p)) if n.success() && p.success())
}

fn find_runtime_dir() -> Option<std::path::PathBuf> {
    let mut dir = std::env::current_dir().ok()?;
    for _ in 0..5 {
        let runtime_path = dir.join("runtime");
        if runtime_path.join("package.json").exists() {
            return Some(runtime_path);
        }
        if let Some(parent) = dir.parent() {
            dir = parent.to_path_buf();
        } else {
            break;
        }
    }
    None
}

fn build_runtime_if_needed(runtime_dir: &std::path::Path) -> bool {
    let dist_index = runtime_dir.join("dist").join("index.js");
    if dist_index.exists() {
        return true;
    }

    println!(
        "{} Dist files not found. Compiling TypeScript runtime first...",
        "⏳".yellow()
    );

    // npm install
    println!("   Running npm install in {}...", runtime_dir.display());
    let install_status = std::process::Command::new("npm")
        .arg("install")
        .current_dir(runtime_dir)
        .status();

    match install_status {
        Ok(s) if s.success() => {}
        _ => return false,
    }

    // npm run build
    println!("   Running npm run build...");
    let build_status = std::process::Command::new("npm")
        .arg("run")
        .arg("build")
        .current_dir(runtime_dir)
        .status();

    matches!(build_status, Ok(s) if s.success())
}

/// Find all files with a given extension recursively under a directory.
fn find_files_by_extension(dir: &Path, ext: &str) -> Vec<PathBuf> {
    let mut results = Vec::new();
    find_files_recursive(dir, &mut results, |p| {
        p.extension().is_some_and(|e| e == ext)
    });
    results
}

/// Find all files with a given name recursively under a directory.
fn find_files_by_name(dir: &Path, name: &str) -> Vec<PathBuf> {
    let mut results = Vec::new();
    find_files_recursive(dir, &mut results, |p| {
        p.file_name().is_some_and(|n| n == name)
    });
    results
}

fn find_files_recursive(
    dir: &Path,
    results: &mut Vec<PathBuf>,
    predicate: impl Fn(&Path) -> bool + Copy,
) {
    if let Ok(entries) = std::fs::read_dir(dir) {
        for entry in entries.flatten() {
            let path = entry.path();
            if path.is_dir() {
                // Skip node_modules and target directories
                let name = path.file_name().unwrap_or_default();
                if name == "node_modules" || name == "target" {
                    continue;
                }
                find_files_recursive(&path, results, predicate);
            } else if predicate(&path) {
                results.push(path);
            }
        }
    }
}

struct JunitSuite {
    name: String,
    tests: usize,
    failures: usize,
    errors: usize,
}

/// Simple JUnit XML parser that extracts <testsuite> attributes.
fn parse_junit_suites(xml: &str) -> Vec<JunitSuite> {
    let mut suites = Vec::new();

    for line in xml.lines() {
        let trimmed = line.trim();
        if trimmed.starts_with("<testsuite ") || trimmed.starts_with("<testsuite>") {
            let name = extract_xml_attr(trimmed, "name").unwrap_or_else(|| "(unnamed)".to_string());
            let tests = extract_xml_attr(trimmed, "tests")
                .and_then(|v| v.parse::<usize>().ok())
                .unwrap_or(0);
            let failures = extract_xml_attr(trimmed, "failures")
                .and_then(|v| v.parse::<usize>().ok())
                .unwrap_or(0);
            let errors = extract_xml_attr(trimmed, "errors")
                .and_then(|v| v.parse::<usize>().ok())
                .unwrap_or(0);
            suites.push(JunitSuite {
                name,
                tests,
                failures,
                errors,
            });
        }
    }

    suites
}

/// Extract a simple XML attribute value: name="value"
fn extract_xml_attr(element: &str, attr: &str) -> Option<String> {
    let pattern = format!("{}=\"", attr);
    if let Some(start) = element.find(&pattern) {
        let after = &element[start + pattern.len()..];
        if let Some(end) = after.find('"') {
            return Some(after[..end].to_string());
        }
    }
    None
}

/// Parse LCOV .info content and return (lines_hit, lines_total).
fn parse_lcov_summary(content: &str) -> (usize, usize) {
    let mut lines_hit = 0usize;
    let mut lines_total = 0usize;

    for line in content.lines() {
        let trimmed = line.trim();
        if let Some(rest) = trimmed.strip_prefix("LH:")
            && let Ok(n) = rest.trim().parse::<usize>()
        {
            lines_hit += n;
        } else if let Some(rest) = trimmed.strip_prefix("LF:")
            && let Ok(n) = rest.trim().parse::<usize>()
        {
            lines_total += n;
        }
    }

    (lines_hit, lines_total)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_junit_suites() {
        let xml = r#"<?xml version="1.0"?>
<testsuites>
  <testsuite name="CheckoutService" tests="3" failures="0" errors="0" time="0.123">
    <testcase name="should place order"/>
  </testsuite>
  <testsuite name="PaymentService" tests="5" failures="1" errors="0" time="0.456">
    <testcase name="should process"/>
  </testsuite>
</testsuites>"#;
        let suites = parse_junit_suites(xml);
        assert_eq!(suites.len(), 2);
        assert_eq!(suites[0].name, "CheckoutService");
        assert_eq!(suites[0].tests, 3);
        assert_eq!(suites[0].failures, 0);
        assert_eq!(suites[1].name, "PaymentService");
        assert_eq!(suites[1].tests, 5);
        assert_eq!(suites[1].failures, 1);
    }

    #[test]
    fn test_parse_lcov_summary() {
        let lcov = "SF:src/services/Checkout.ts\nDA:1,1\nDA:2,0\nLF:10\nLH:8\nend_of_record\n";
        let (hit, total) = parse_lcov_summary(lcov);
        assert_eq!(hit, 8);
        assert_eq!(total, 10);
    }

    #[test]
    fn test_extract_xml_attr() {
        let element = r#"<testsuite name="MyService" tests="5" failures="1" errors="0">"#;
        assert_eq!(
            extract_xml_attr(element, "name"),
            Some("MyService".to_string())
        );
        assert_eq!(extract_xml_attr(element, "tests"), Some("5".to_string()));
        assert_eq!(extract_xml_attr(element, "missing"), None);
    }
}
