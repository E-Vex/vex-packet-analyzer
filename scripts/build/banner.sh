#!/usr/bin/env bash
# scripts/build/banner.sh
# Prints the VETRIX ASCII banner with the Makefile version tag.
set -euo pipefail

MAKEFILE_VERSION="${VX_MAKEFILE_VERSION:-1.0}"
COLOR="${VX_COLOR:-0}"

if [ "$COLOR" = "1" ]; then
    C_LOGO=$'\033[36m'   # cyan
    C_TAG=$'\033[1m'     # bold
    C_RESET=$'\033[0m'
else
    C_LOGO=""; C_TAG=""; C_RESET=""
fi

# ANSI Shadow "VETRIX"
banner=(
    '██╗   ██╗███████╗████████╗██████╗ ██╗██╗  ██╗'
    '██║   ██║██╔════╝╚══██╔══╝██╔══██╗██║╚██╗██╔╝'
    '██║   ██║█████╗     ██║   ██████╔╝██║ ╚███╔╝ '
    '╚██╗ ██╔╝██╔══╝     ██║   ██╔══██╗██║ ██╔██╗ '
    ' ╚████╔╝ ███████╗   ██║   ██║  ██║██║██╔╝ ██╗'
    '  ╚═══╝  ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝'
)

echo
for i in "${!banner[@]}"; do
    line="${banner[$i]}"
    if [ "$i" -eq 2 ]; then
        printf ' %s%s%s   %sMakefile v%s%s\n' \
            "$C_LOGO" "$line" "$C_RESET" "$C_TAG" "$MAKEFILE_VERSION" "$C_RESET"
    else
        printf ' %s%s%s\n' "$C_LOGO" "$line" "$C_RESET"
    fi
done
