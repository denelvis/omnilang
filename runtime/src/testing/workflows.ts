import pc from "picocolors";

export interface Transition {
  from: string;
  to: string;
  trigger?: string;
  guard?: string;
  actions: string[];
}

export interface WorkflowConfig {
  name: string;
  states: string[];
  transitions: Transition[];
}

function sanitizeIdentifier(name: string): string {
  let clean = name.replace(/[^a-zA-Z0-9_$]/g, "_");
  clean = clean.replace(/_+/g, "_");
  clean = clean.replace(/^_+|_+$/g, "");
  if (/^[0-9]/.test(clean)) {
    clean = "_" + clean;
  }
  clean = clean.replace(/_([a-zA-Z0-9])/g, (g) => g[1].toUpperCase());
  if (clean.length > 0) {
    clean = clean[0].toLowerCase() + clean.slice(1);
  }
  return clean || "trigger";
}

export class WorkflowGenerator {
  public generateStateMachine(w: WorkflowConfig): string {
    console.log(`[Workflow Gen] Generating State Machine for: ${pc.cyan(w.name)}`);
    console.log(`[Workflow Gen] States: ${pc.yellow(w.states.join(", "))}`);

    const statesEnum = w.states.map(s => `  ${s} = "${s}",`).join("\n");
    const transitionMethods = w.transitions.map(t => {
      const triggerName = t.trigger ? sanitizeIdentifier(t.trigger) : `goto${t.to}`;
      return `
  public async ${triggerName}(): Promise<void> {
    if (this.currentState !== State.${t.from}) {
      throw new Error(\`Invalid transition: cannot trigger ${triggerName} from state \${this.currentState}\`);
    }
    ${t.guard ? `if (!this.checkGuard("${t.guard}")) { throw new Error("Guard conditions not satisfied"); }` : ""}
    
    console.log(\`Transitioning state from ${t.from} to ${t.to} via ${triggerName}\`);
    this.currentState = State.${t.to};
    
    ${t.actions.map(act => `await this.executeAction("${act}");`).join("\n    ")}
  }`;
    }).join("\n");

    const code = `
export enum State {
${statesEnum}
}

export class ${w.name}StateMachine {
  private currentState: State = State.${w.states[0] || "Init"};

  constructor() {
    console.log("State Machine ${w.name} initialized in state: " + this.currentState);
  }

  public getCurrentState(): State {
    return this.currentState;
  }

  private checkGuard(guardName: string): boolean {
    // Simulated guard condition check
    return true;
  }

  private async executeAction(actionName: string): Promise<void> {
    console.log(\`Executing transition action: \${actionName}\`);
  }
${transitionMethods}
}
`;
    return code.trim();
  }
}
