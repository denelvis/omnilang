import pc from "picocolors";
import { LLMProvider } from "./base";
import { AnthropicProvider } from "./anthropic";

export class OllamaProvider implements LLMProvider {
  private isMock: boolean;
  private host: string;
  private model: string;
  private mockProvider?: AnthropicProvider;

  constructor() {
    this.isMock = process.env.OMNI_MOCK_LLM === "true";
    this.host = process.env.OLLAMA_HOST || "http://localhost:11434";
    this.model = process.env.OLLAMA_MODEL || "qwen2.5-coder:latest";
    if (this.isMock) {
      this.mockProvider = new AnthropicProvider();
    }
  }

  public async generateCode(systemPrompt: string, userPrompt: string, model?: string): Promise<string> {
    if (this.isMock) {
      console.log(pc.blue("   [MOCK LLM] Simulating Ollama response..."));
      if (!this.mockProvider) {
        this.mockProvider = new AnthropicProvider();
      }
      return this.mockProvider.getMockResponse(systemPrompt, userPrompt);
    }

    const isCloudModel = model && (model.startsWith("claude-") || model.startsWith("gpt-") || model.startsWith("gemini-"));
    const selectedModel = (model && !isCloudModel) ? model : (process.env.OLLAMA_MODEL || process.env.OMNI_MODEL || this.model);
    console.log(pc.blue(`   [Ollama] Calling model: ${selectedModel} at ${this.host}...`));
    const url = `${this.host}/api/chat`;

    try {
      const response = await fetch(url, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({
          model: selectedModel,
          messages: [
            { role: "system", content: systemPrompt },
            { role: "user", content: userPrompt }
          ],
          stream: false,
          options: {
            temperature: 0.2
          }
        })
      });

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status} (${response.statusText})`);
      }

      const data = await response.json() as any;
      if (data && data.message && typeof data.message.content === "string") {
        return data.message.content;
      }

      throw new Error(`Unexpected response structure from Ollama API: ${JSON.stringify(data)}`);
    } catch (error: any) {
      console.error(pc.red(`   [Ollama] Error communicating with Ollama: ${error.message}`));
      throw error;
    }
  }
}
