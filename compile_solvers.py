#!/usr/bin/python

from pathlib import Path
import sys
import subprocess

begin, end = map(int, sys.argv[1:3])

Path('solvers').mkdir(exist_ok=True)

for i in range(begin, end + 1):
    _ = subprocess.Popen(['c++', 'solver.cpp', '-o', f'solvers/{i}', '-O2', f'-DN={i}'])
