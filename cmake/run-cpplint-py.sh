#!/bin/bash
# Bash script check code style issues with cpplint.py

find src -type f \( -name \*.cpp -o -name \*.h \) | xargs python2 ./cmake/cpplint.py --root src
