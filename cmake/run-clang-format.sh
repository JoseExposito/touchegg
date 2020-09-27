#!/bin/bash
# Bash script check code style issues with clang-format and show a nice diff

hasWerror=$(clang-format --help | grep Werror)
if [ -z "$hasWerror" ]; then
  WerrorFlag=""
else
  WerrorFlag="--Werror"
fi

result=$(find src -type f \( -name \*.cpp -o -name \*.h \) -exec sh -c 'clang-format --style=file $1 "$0" | diff -u "$0" -' {} $WerrorFlag \;)

if [ -z "$result" ]; then
  exit 0
else
  echo "$result"
  exit 1
fi
