#!/usr/bin/env bash
set -e
mkdir -p bin
make all
echo "Build completo. Binarios en ./bin"