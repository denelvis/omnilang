import { LLMProvider } from "./base";
import { AnthropicProvider } from "./anthropic";
import { OllamaProvider } from "./ollama";
import { LlamaCppProvider } from "./llamacpp";

export { LLMProvider, AnthropicProvider, OllamaProvider, LlamaCppProvider };

export function getLLMProvider(providerName?: string): LLMProvider {
  const name = providerName || process.env.OMNI_LLM_PROVIDER || "anthropic";
  
  switch (name.toLowerCase()) {
    case "ollama":
      return new OllamaProvider();
    case "llamacpp":
    case "llama.cpp":
    case "ollamacpp":
    case "ollama.cpp":
      return new LlamaCppProvider();
    case "anthropic":
    default:
      return new AnthropicProvider();
  }
}
