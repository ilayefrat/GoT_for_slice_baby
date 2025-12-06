#!/bin/bash

# Stop the script immediately if any command fails
set -e

echo "--- 🧹 Cleaning Build Directory ---"
rm -rf ../build
mkdir ../build

echo "--- 🔨 Compiling ---"
# Run make (assuming your Makefile handles the ../build path)
make

echo "--- 🚀 Running with Sudo ---"


sudo ../build/main test_l2_eviction
