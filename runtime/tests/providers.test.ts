import { getLLMProvider, AnthropicProvider, OllamaProvider, LlamaCppProvider } from "../src/providers";

describe("LLM Providers Instantiation", () => {
  const originalEnv = process.env;

  beforeEach(() => {
    jest.resetModules();
    process.env = { ...originalEnv };
    process.env.OMNI_MOCK_LLM = "true";
  });

  afterAll(() => {
    process.env = originalEnv;
  });

  test("should resolve default to AnthropicProvider", () => {
    delete process.env.OMNI_LLM_PROVIDER;
    const provider = getLLMProvider();
    expect(provider).toBeInstanceOf(AnthropicProvider);
  });

  test("should resolve ollama name to OllamaProvider", () => {
    const provider = getLLMProvider("ollama");
    expect(provider).toBeInstanceOf(OllamaProvider);
  });

  test("should resolve env var to OllamaProvider", () => {
    process.env.OMNI_LLM_PROVIDER = "ollama";
    const provider = getLLMProvider();
    expect(provider).toBeInstanceOf(OllamaProvider);
  });

  test("should resolve llamacpp names to LlamaCppProvider", () => {
    const names = ["llamacpp", "llama.cpp", "ollamacpp", "ollama.cpp"];
    for (const name of names) {
      const provider = getLLMProvider(name);
      expect(provider).toBeInstanceOf(LlamaCppProvider);
    }
  });

  test("should resolve env var to LlamaCppProvider", () => {
    process.env.OMNI_LLM_PROVIDER = "llama.cpp";
    const provider = getLLMProvider();
    expect(provider).toBeInstanceOf(LlamaCppProvider);
  });
});

describe("LLM Providers Mock Responses", () => {
  beforeEach(() => {
    process.env.OMNI_MOCK_LLM = "true";
  });

  test("OllamaProvider should return mock response", async () => {
    const provider = new OllamaProvider();
    const system = "You are a Rust programmer";
    const user = 'service: "CheckoutService"';
    const response = await provider.generateCode(system, user);
    expect(response).toBeDefined();
    expect(response).toContain("CheckoutService");
  });

  test("LlamaCppProvider should return mock response", async () => {
    const provider = new LlamaCppProvider();
    const system = "You are a Go programmer";
    const user = 'service: "CheckoutService"';
    const response = await provider.generateCode(system, user);
    expect(response).toBeDefined();
    expect(response).toContain("CheckoutService");
  });
});
