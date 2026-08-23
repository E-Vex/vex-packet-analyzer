#!/usr/bin/env bash
# scripts/build/progress.sh <src> <obj>
# Safe to run under `make -jN`: the completed-count is incremented
# through a flock'd counter file, so percentages stay correct even
# when several files finish at nearly the same time.
set -euo pipefail

src="$1"
obj="$2"

: "${VX_CC:?VX_CC not set}"
: "${VX_TOTAL:?VX_TOTAL not set}"
: "${VX_PROGRESS_DIR:?VX_PROGRESS_DIR not set}"

mkdir -p "$VX_PROGRESS_DIR" "$(dirname "$obj")"
lockfile="$VX_PROGRESS_DIR/.lock"
counter="$VX_PROGRESS_DIR/.count"

if [ "${VX_COLOR:-0}" = "1" ]; then
    C_DIM=$'\033[2m'; C_RESET=$'\033[0m'
    C_PCT=$'\033[32m'; C_TIME=$'\033[33m'; C_ERR=$'\033[31m'
else
    C_DIM=""; C_RESET=""; C_PCT=""; C_TIME=""; C_ERR=""
fi

printf '%sCompiling%s %s\n' "$C_DIM" "$C_RESET" "$src"

start=$(date +%s.%N)
logfile=$(mktemp)
# shellcheck disable=SC2086
if ! "$VX_CC" $VX_CFLAGS -c "$src" -o "$obj" 2>"$logfile"; then
    printf '%s-- failed: %s --%s\n' "$C_ERR" "$src" "$C_RESET" >&2
    cat "$logfile" >&2
    rm -f "$logfile"
    exit 1
fi
end=$(date +%s.%N)

if [ -s "$logfile" ]; then
    cat "$logfile" >&2
fi
rm -f "$logfile"

dur=$(awk -v s="$start" -v e="$end" 'BEGIN{printf "%.2f", e - s}')
size=$(du -h "$obj" | cut -f1)

# Atomically bump the shared completed-file counter.
count=$(
    {
        flock -x 200
        n=$(( $(cat "$counter" 2>/dev/null || echo 0) + 1 ))
        echo "$n" > "$counter"
        echo "$n"
    } 200>"$lockfile"
)

pct=$(awk -v c="$count" -v t="$VX_TOTAL" 'BEGIN{ t = (t=="" || t==0) ? 1 : t; printf "%d", (c/t)*100 }')

printf '%s%3d%%%s  -> %-30s %s(%5s)%s %s(%ss)%s\n' \
    "$C_PCT" "$pct" "$C_RESET" \
    "$(basename "$obj")" \
    "$C_DIM" "$size" "$C_RESET" \
    "$C_TIME" "$dur" "$C_RESET"

