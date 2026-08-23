#!/usr/bin/env bash
# scripts/build/summary.sh
set -euo pipefail

COLOR="${VX_COLOR:-0}"
if [ "$COLOR" = "1" ]; then
    C_NAME=$'\033[1m'    # bold
    C_SYM=$'\033[90m'    # grey
    C_VAL=$'\033[0m'
    C_RESET=$'\033[0m'
    C_TITLE=$'\033[1;32m' # bold green
else
    C_NAME=""; C_SYM=""; C_VAL=""; C_RESET=""; C_TITLE=""
fi

row() {
    # $1=name  $2=symbol  $3=value
    printf ' %s%-12s%s %s%s%s %s%s%s\n' \
        "$C_NAME" "$1" "$C_RESET" \
        "$C_SYM" "$2" "$C_RESET" \
        "$C_VAL" "$3" "$C_RESET"
}

row "PLATFORM"  "?|" "${VX_PLATFORM:-unknown}"
row "ARCH"      "?|" "${VX_ARCH:-unknown}"
row "CC"        "?|" "${VX_CC_DISPLAY:-unknown}"
row "MODE"      "?|" "${VX_MODE:-debug}"
row "THREADS"   ":|" "${VX_THREADS:-1}"
row "STD"       "!|" "${VX_STD:-}"
row "WARNFLAGS" ":|" "${VX_WARN:-}"
row "OPTFLAGS"  ":|" "${VX_OPTFLAGS:-}"
row "CFLAGS"    "+|" "${VX_CFLAGS_DISPLAY:-}"
row "LDFLAGS"   "+|" "${VX_LDFLAGS_DISPLAY:-(none)}"

echo
printf ' %sBuilding vetrix%s (v%s) %s %s\n' \
    "$C_TITLE" "$C_RESET" "${VX_VERSION:-0.0.0}" "${VX_PLATFORM:-}" "${VX_ARCH:-}"
echo
