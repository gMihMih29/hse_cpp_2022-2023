#!/bin/bash

# Run from build directory

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 task-name"
    exit 1
fi

TASK_PATH=../tasks/$1
CLANG_PATH=../run-clang-format.py

if [ ! -f compile_commands.json ]; then
    echo "Run this script from the build directory"
    exit 1
fi

if [ "$#" -eq 2 ]; then
    TASK_PATH=../../tasks/$1
    CLANG_PATH=../../run-clang-format.py
fi

$CLANG_PATH -r "$TASK_PATH" -e '*/test.cpp' && find "$TASK_PATH" -type f \( -name '*.cpp' -o -name '*.h' \) -not -name 'test.cpp' | xargs clang-tidy-14 '-header-filter=.*'
