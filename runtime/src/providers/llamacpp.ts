import pc from "picocolors";
import { LLMProvider } from "./base";
import { AnthropicProvider } from "./anthropic";

export class LlamaCppProvider implements LLMProvider {
  private isMock: boolean;
  private host: string;
  private mockProvider?: AnthropicProvider;

  constructor() {
    this.isMock = process.env.OMNI_MOCK_LLM === "true";
    this.host = process.env.LLAMACPP_HOST || process.env.OLLAMA_CPP_HOST || "http://localhost:8080";
    if (this.isMock) {
      this.mockProvider = new AnthropicProvider();
    }
  }

  public async generateCode(systemPrompt: string, userPrompt: string, model?: string): Promise<string> {
    if (this.isMock) {
      console.log(pc.blue("   [MOCK LLM] Simulating llama.cpp response..."));
      if (!this.mockProvider) {
        this.mockProvider = new AnthropicProvider();
      }
      return this.mockProvider.getMockResponse(systemPrompt, userPrompt);
    }

    console.log(pc.blue(`   [llama.cpp] Calling model at ${this.host}...`));
    
    // Try the OpenAI-compatible chat completions endpoint first
    const openAiUrl = `${this.host}/v1/chat/completions`;
    
    try {
      const response = await fetch(openAiUrl, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({
          messages: [
            { role: "system", content: systemPrompt },
            { role: "user", content: userPrompt }
          ],
          temperature: 0.2,
          stream: false
        })
      });

      if (response.ok) {
        const data = await response.json() as any;
        if (data && data.choices && data.choices[0] && data.choices[0].message) {
          return data.choices[0].message.content;
        }
      }
    } catch (e) {
      // Fall through to native completion endpoint if OpenAI-compatible endpoint fails
    }

    // Fallback: Native llama.cpp /completion endpoint
    const nativeUrl = `${this.host}/completion`;
    console.log(pc.blue(`   [llama.cpp] Falling back to native completion endpoint: ${nativeUrl}...`));

    try {
      const prompt = `<|system|>\n${systemPrompt}\n<|user|>\n${userPrompt}\n<|assistant|>\n`;
      const response = await fetch(nativeUrl, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({
          prompt,
          temperature: 0.2,
          stream: false
        })
      });

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status} (${response.statusText})`);
      }

      const data = await response.json() as any;
      if (data && typeof data.content === "string") {
        return data.content;
      }

      throw new Error(`Unexpected response structure from llama.cpp API: ${JSON.stringify(data)}`);
    } catch (error: any) {
      console.error(pc.red(`   [llama.cpp] Error communicating with llama.cpp: ${error.message}`));
      throw error;
    }
  }
}
