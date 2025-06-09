import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BIN = ROOT / 'push_swap'

# Build the binary once for all tests
subprocess.run(['make', '-C', str(ROOT)], check=True)


def run_push_swap(args):
    result = subprocess.run([str(BIN)] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=2)
    return result.stdout.strip().splitlines()


def test_two_numbers():
    ops = run_push_swap(['2', '1'])
    assert len(ops) == 1
    assert ops[0] == 'sa'


def test_three_reverse():
    ops = run_push_swap(['3', '2', '1'])
    assert len(ops) == 2
    assert ops == ['sa', 'rra']


def test_five_specific():
    ops = run_push_swap(['2', '1', '3', '5', '4'])
    assert len(ops) == 8


def test_hundred_reverse():
    numbers = [str(i) for i in range(100, 0, -1)]
    ops = run_push_swap(numbers)
    assert len(ops) == 1084

