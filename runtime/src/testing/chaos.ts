import pc from "picocolors";

export type FaultKind = "network-partition" | "service-crash" | "cpu-exhaustion" | "clock-skew";

export interface ChaosSpec {
  targetService: string;
  fault: FaultKind;
  durationMs: number;
  expectedMaxRecoveryTimeMs?: number;
}

export interface ChaosTestResult {
  fault: FaultKind;
  survived: boolean;
  recoveryTimeMs: number;
  message: string;
}

/**
 * @deprecated Use real chaos-testing frameworks.
 * @internal This is a mock simulation layer and should not be used in production.
 */
export class ChaosRunner {
  public injectFault(spec: ChaosSpec): ChaosTestResult {
    console.log(`[Chaos Engineering] Injecting fault: ${pc.red(spec.fault.toUpperCase())} on service: ${pc.cyan(spec.targetService)}`);
    console.log(`[Chaos Engineering] Duration: ${spec.durationMs}ms, Max Recovery Time Allowed: ${spec.expectedMaxRecoveryTimeMs ?? "unlimited"}ms`);

    // Simulate resilience behavior
    let survived = true;
    let recoveryTimeMs = 150; // default simulation

    switch (spec.fault) {
      case "service-crash":
        console.log(`   [Chaos] Simulating service crash... Node manager triggers auto-restart.`);
        recoveryTimeMs = 350;
        break;
      case "network-partition":
        console.log(`   [Chaos] Simulating network partition... Re-routing requests to standby node.`);
        recoveryTimeMs = 120;
        break;
      case "cpu-exhaustion":
        console.log(`   [Chaos] Simulating CPU exhaustion... Request throttling active.`);
        recoveryTimeMs = 80;
        break;
      case "clock-skew":
        console.log(`   [Chaos] Simulating clock skew... NTP synchronization corrected offset.`);
        recoveryTimeMs = 50;
        break;
    }

    if (spec.targetService.toLowerCase().includes("brittle")) {
      survived = false;
      recoveryTimeMs = 5000;
    }

    if (spec.expectedMaxRecoveryTimeMs && recoveryTimeMs > spec.expectedMaxRecoveryTimeMs) {
      survived = false;
    }

    const message = survived
      ? `Service '${spec.targetService}' successfully survived ${spec.fault} and recovered in ${recoveryTimeMs}ms.`
      : `Service '${spec.targetService}' failed to recover in time (recovery time: ${recoveryTimeMs}ms > max allowed: ${spec.expectedMaxRecoveryTimeMs ?? 0}ms).`;

    if (survived) {
      console.log(`[Chaos Engineering] ${pc.green("✓")} Resilience check passed: ${message}`);
    } else {
      console.error(pc.red(`[Chaos Engineering] ❌ Resilience check failed: ${message}`));
    }

    return {
      fault: spec.fault,
      survived,
      recoveryTimeMs,
      message
    };
  }
}
