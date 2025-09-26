#!/usr/bin/env bash
# exit on error
set -o errexit

# Install C++ build essentials
echo "Installing C++ build tools..."
apt-get update && apt-get install -y cmake g++ make

# Build the C++ application
echo "Building the C++ scheduler..."
mkdir -p build
cd build
cmake ..
make
cd ..

# Install Python dependencies
pip install -r requirements.txt
