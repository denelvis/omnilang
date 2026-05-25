use clap::{Parser, Subcommand};
use colored::Colorize;
use std::path::Path;

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
    },

    /// Initialize a new OmniLang project.
    Init {
        /// Project name (creates a directory).
        #[arg(default_value = ".")]
        name: String,
    },
}

fn main() {
    let cli = Cli::parse();

    let exit_code = match cli.command {
        Commands::Check { path, format } => cmd_check(&path, &format, cli.verbose, cli.quiet),
        Commands::Plan { path } => cmd_plan(&path),
        Commands::Build { path, target } => cmd_build(&path, &target),
        Commands::Init { name } => cmd_init(&name),
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

fn cmd_build(path: &str, target: &str) -> i32 {
    println!(
        "{} Building specifications in: {}",
        "🔨".yellow(),
        path.cyan()
    );
    println!("   Target language: {}", target.green());

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
            let status = std::process::Command::new("node")
                .arg(runtime_dir.join("dist").join("index.js"))
                .arg(ir_path)
                .arg("--output")
                .arg("build")
                .arg("--target")
                .arg(target)
                .status();

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
