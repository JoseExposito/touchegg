#!/bin/bash
# Bash script check code style issues with cpplint.py

find src -type f \( -name \*.cpp -o -name \*.h \) -print0 | xargs -0 python3 ./cmake/cpplint.py --root src
