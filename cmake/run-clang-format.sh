#!/bin/bash
# Bash script check code style issues with clang-format and show a nice diff

result=$(find src -type f \( -name \*.cpp -o -name \*.h \) -exec sh -c 'clang-format -style=file --Werror {} | diff -u {} -' \;)

if [ -z "$result" ]; then
  exit 0
else
  echo "$result"
  exit 1
fi
