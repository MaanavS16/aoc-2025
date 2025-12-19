#!/usr/bin/env bash
set -euo pipefail

CXX=g++
CXXFLAGS="-O3 -Wall -std=c++20"

FILE=""     # Which cpp file to run
MODE="actual"  # test or actual input

# Parse args
for arg in "$@"; do
  case "$arg" in
    --file=*) FILE="${arg#*=}" ;;
    --mode=*) MODE="${arg#*=}" ;;
    *)
      echo "Unknown argument: $arg"
      exit 1
      ;;
  esac
done

if [[ -z "$FILE" ]]; then
  echo "Please specify a file with --file=<name>"
  exit 1
fi

SRC="src/${FILE}.cpp"
EXE="./${FILE}"
INPUT="input/${FILE}_${MODE}"

if [[ ! -f "$SRC" ]]; then
  echo "Source file not found: $SRC"
  exit 1
fi

if [[ ! -f "$INPUT" ]]; then
  echo "Input file not found: $INPUT"
  exit 1
fi

echo "Compiling $SRC..."
$CXX $CXXFLAGS "$SRC" -o "$EXE"

echo "Running $EXE with $INPUT..."
cat "$INPUT" | "$EXE"
