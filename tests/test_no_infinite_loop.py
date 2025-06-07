import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / 'src'

BIN = ROOT / 'tests' / 'parser_test'

# Compile the test helper
COMPILE_CMD = [
    'gcc',
    '-I', str(SRC),
    str(SRC / 'parser.c'),
    str(SRC / 'split.c'),
    str(SRC / 'string_utils.c'),
    str(SRC / 'atoi_utils.c'),
    str(SRC / 'free_utils.c'),
    str('tests/parser_test_main.c'),
    '-o', str(BIN)
]

subprocess.run(COMPILE_CMD, check=True)

def run_program(args):
    result = subprocess.run([str(BIN)] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=2)
    return result.returncode, result.stdout.decode()


def test_no_duplicates():
    # numbers passed in a single argument, the parser should succeed
    code, out = run_program(['1 2 3'])
    assert code == 0
    assert 'OK' in out


def test_with_duplicates():
    code, out = run_program(['1', '1'])
    # Should exit with error code 1 but not hang
    assert code == 1
    assert 'ERROR' in out
