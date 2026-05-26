import * as fs from "fs";
import * as path from "path";
import pc from "picocolors";

export interface IgnoreRegion {
  x: number;
  y: number;
  width: number;
  height: number;
}

export interface VisualSpec {
  componentName: string;
  tolerance?: number; // threshold e.g. 0.05
  ignoreRegions?: IgnoreRegion[];
  goldenDir?: string;
}

/**
 * @deprecated Use real visual regression testing tools (e.g., Playwright, BackstopJS).
 * @internal This is a mock simulation layer and should not be used in production.
 */
export class VisualTestRunner {
  private goldenDir: string;

  constructor(customGoldenDir?: string) {
    this.goldenDir = customGoldenDir || path.resolve(process.cwd(), ".golden");
    if (!fs.existsSync(this.goldenDir)) {
      fs.mkdirSync(this.goldenDir, { recursive: true });
    }
  }

  public runVisualTest(spec: VisualSpec): { success: boolean; diffPixels: number; message: string } {
    const componentName = spec.componentName;
    const tolerance = spec.tolerance ?? 0.05; // 5% default
    const ignoreRegions = spec.ignoreRegions ?? [];
    const goldenPath = path.join(this.goldenDir, `${componentName}.golden.png`);

    console.log(`[Visual Testing] Running visual test for component: ${pc.cyan(componentName)}`);
    console.log(`[Visual Testing] Golden file: ${pc.dim(goldenPath)}`);
    console.log(`[Visual Testing] Tolerance threshold: ${pc.yellow(tolerance * 100 + "%")}`);

    // If golden file does not exist, write a mock golden image (represents initial capture)
    if (!fs.existsSync(goldenPath)) {
      fs.writeFileSync(goldenPath, `MOCK_PNG_DATA_FOR_${componentName.toUpperCase()}`);
      console.log(`[Visual Testing] ${pc.yellow("⚠ Golden file not found. Created initial golden file.")}`);
      return {
        success: true,
        diffPixels: 0,
        message: "Initial golden file captured."
      };
    }

    // Simulate/run screenshot comparison
    // In a real browser context, we would take a screenshot using Puppeteer/Playwright
    // For compiler testing, we simulate comparison. Let's make it fail if a spec specifies
    // a failing mock case or calculate a realistic pixel diff.
    const hasFailingSpec = componentName.toLowerCase().includes("fail");
    const diffPixels = hasFailingSpec ? 150 : 0;
    const totalPixels = 10000;
    const diffRatio = diffPixels / totalPixels;

    if (diffRatio > tolerance) {
      const msg = `Visual mismatch in '${componentName}'! Diff ratio: ${(diffRatio * 100).toFixed(2)}% > tolerance: ${(tolerance * 100).toFixed(2)}%`;
      console.error(pc.red(`[Visual Testing] ❌ ${msg}`));
      this.renderSideBySideDiff(componentName, ignoreRegions);
      return {
        success: false,
        diffPixels,
        message: msg
      };
    }

    console.log(`[Visual Testing] ${pc.green("✓")} Visual verification passed. Mismatch ratio: ${(diffRatio * 100).toFixed(2)}%`);
    return {
      success: true,
      diffPixels,
      message: "Visual verification passed."
    };
  }

  private renderSideBySideDiff(componentName: string, ignoreRegions: IgnoreRegion[]): void {
    console.log("\n" + pc.bold("=== SIDE-BY-SIDE VISUAL DIFF VIEW ==="));
    console.log(`Component: ${componentName}`);
    console.log("-----------------------------------------");
    console.log("      [GOLDEN]          |        [ACTUAL]        ");
    console.log("------------------------+------------------------");
    
    // Render ASCII representation of the layout differences
    const grid = [
      [" ", " ", " ", " ", " ", " ", " ", " "],
      [" ", "H", "E", "A", "D", "E", "R", " "],
      [" ", " ", " ", " ", " ", " ", " ", " "],
      [" ", " ", "D", "I", "F", "F", " ", " "], // Highlighted diff area
      [" ", " ", " ", " ", " ", " ", " ", " "],
      [" ", "F", "O", "O", "T", "E", "R", " "],
    ];

    for (let r = 0; r < grid.length; r++) {
      let goldenLine = "";
      let actualLine = "";
      for (let c = 0; c < grid[r].length; c++) {
        const char = grid[r][c];
        const isIgnore = ignoreRegions.some(reg => reg.x === c && reg.y === r);

        if (char === "D" || char === "I" || char === "F") {
          goldenLine += pc.green(char);
          actualLine += isIgnore ? pc.yellow("I") : pc.red("X"); // X for diff, I for ignored
        } else {
          goldenLine += char;
          actualLine += char;
        }
      }
      console.log(`   | ${goldenLine.padEnd(20)} | | ${actualLine.padEnd(20)} |`);
    }
    console.log("-----------------------------------------\n");
  }
}
