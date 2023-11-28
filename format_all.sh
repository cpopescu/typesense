#!/bin/bash

# Formats all source files in place
for ext in h cc proto; do
    for dir in include src test; do
      find ${dir} -name "*.${ext}" | xargs clang-format --style=Google -i
    done
done
buildifier -r .
