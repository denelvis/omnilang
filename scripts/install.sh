#!/bin/sh
# OmniLang installer script
# Usage: curl -sSL https://omnilang.dev/install.sh | sh
#   or:  wget -qO- https://omnilang.dev/install.sh | sh

set -e

REPO="denelvis/omnilang"
INSTALL_DIR="${OMNI_INSTALL_DIR:-$HOME/.local/bin}"

# Detect OS and architecture
detect_platform() {
    OS="$(uname -s)"
    ARCH="$(uname -m)"

    case "$OS" in
        Linux*)   PLATFORM="linux" ;;
        Darwin*)  PLATFORM="macos" ;;
        MINGW*|MSYS*|CYGWIN*) PLATFORM="windows" ;;
        *)
            echo "Error: Unsupported OS: $OS"
            exit 1
            ;;
    esac

    case "$ARCH" in
        x86_64|amd64) ARCH_SUFFIX="x64" ;;
        arm64|aarch64) ARCH_SUFFIX="arm64" ;;
        *)
            echo "Error: Unsupported architecture: $ARCH"
            exit 1
            ;;
    esac

    ASSET_NAME="omni-${PLATFORM}-${ARCH_SUFFIX}"
    echo "Detected platform: ${PLATFORM}-${ARCH_SUFFIX}"
}

# Get the latest release version
get_latest_version() {
    VERSION="$(curl -sSf "https://api.github.com/repos/${REPO}/releases/latest" \
        | grep '"tag_name"' \
        | head -1 \
        | sed 's/.*"tag_name": "\(.*\)".*/\1/')"

    if [ -z "$VERSION" ]; then
        echo "Error: Could not determine latest version."
        exit 1
    fi

    echo "Latest version: $VERSION"
}

# Download and install
install() {
    DOWNLOAD_URL="https://github.com/${REPO}/releases/download/${VERSION}/${ASSET_NAME}.tar.gz"

    echo "Downloading ${DOWNLOAD_URL}..."

    TMPDIR="$(mktemp -d)"
    trap 'rm -rf "$TMPDIR"' EXIT

    curl -sSfL "$DOWNLOAD_URL" -o "$TMPDIR/${ASSET_NAME}.tar.gz"

    echo "Extracting..."
    tar -xzf "$TMPDIR/${ASSET_NAME}.tar.gz" -C "$TMPDIR"

    echo "Installing to ${INSTALL_DIR}..."
    mkdir -p "$INSTALL_DIR"
    cp "$TMPDIR/${ASSET_NAME}" "$INSTALL_DIR/omni"
    chmod +x "$INSTALL_DIR/omni"

    echo ""
    echo "✅ OmniLang installed successfully!"
    echo "   Binary: ${INSTALL_DIR}/omni"
    echo "   Version: $(${INSTALL_DIR}/omni version 2>/dev/null || echo "$VERSION")"
    echo ""

    # Check if install dir is in PATH
    case ":$PATH:" in
        *":${INSTALL_DIR}:"*) ;;
        *)
            echo "⚠️  ${INSTALL_DIR} is not in your PATH."
            echo "   Add it with:"
            echo ""
            echo "     export PATH=\"${INSTALL_DIR}:\$PATH\""
            echo ""
            echo "   Or add this line to your shell profile (~/.bashrc, ~/.zshrc, etc.)"
            ;;
    esac
}

main() {
    echo "🚀 Installing OmniLang..."
    echo ""
    detect_platform
    get_latest_version
    install
}

main
