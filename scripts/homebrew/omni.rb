# typed: false
# frozen_string_literal: true

# Homebrew formula for OmniLang CLI
# Install: brew install omnilang/tap/omni
class Omni < Formula
  desc "The specification language for AI-native development"
  homepage "https://github.com/denelvis/omnilang"
  version "0.6.0"
  license any_of: ["Apache-2.0", "MIT"]

  on_macos do
    if Hardware::CPU.arm?
      url "https://github.com/denelvis/omnilang/releases/download/v#{version}/omni-macos-arm64.tar.gz"
      sha256 "PLACEHOLDER_SHA256_MACOS_ARM64"
    else
      url "https://github.com/denelvis/omnilang/releases/download/v#{version}/omni-macos-x64.tar.gz"
      sha256 "PLACEHOLDER_SHA256_MACOS_X64"
    end
  end

  on_linux do
    url "https://github.com/denelvis/omnilang/releases/download/v#{version}/omni-linux-x64.tar.gz"
    sha256 "PLACEHOLDER_SHA256_LINUX_X64"
  end

  def install
    # The tarball contains a single binary named omni-<platform>-<arch>
    Dir.glob("omni-*").each do |binary|
      bin.install binary => "omni"
    end
  end

  test do
    assert_match "omni #{version}", shell_output("#{bin}/omni version")
  end
end
