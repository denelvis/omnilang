export interface LLMProvider {
  generateCode(systemPrompt: string, userPrompt: string, model?: string): Promise<string>;
}
