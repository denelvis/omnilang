import { LLMProvider } from "./base";
import { AnthropicProvider } from "./anthropic";
import { OllamaProvider } from "./ollama";

export { LLMProvider, AnthropicProvider, OllamaProvider };

export function getLLMProvider(providerName?: string): LLMProvider {
  const name = providerName || process.env.OMNI_LLM_PROVIDER || "anthropic";
  
  switch (name.toLowerCase()) {
    case "ollama":
      return new OllamaProvider();
    case "anthropic":
    default:
      return new AnthropicProvider();
  }
}
