#!/bin/bash

# Formats all source files in place
for ext in h cc proto; do
    find shapley/ -name "*.${ext}" | xargs clang-format --style=Google -i
done
buildifier -r shapley/
