#!/bin/bash
# Test script for Holberton Simple Shell 0.1

SHELL="./hsh"
TEST_FILE="test_ls_2"

# Prepare test file
echo "/bin/ls" > $TEST_FILE

echo "===== TEST 1: Run interactive shell and exit ====="
(
    echo "exit"
) | $SHELL

echo
echo "===== TEST 2: Valid command /bin/ls ====="
(
    echo "/bin/ls"
    echo "exit"
) | $SHELL

echo
echo "===== TEST 3: Invalid command qwerty ====="
(
    echo "qwerty"
    echo "exit"
) | $SHELL

echo
echo "===== TEST 4: Using file input ====="
cat $TEST_FILE | $SHELL

echo
echo "===== TEST 5: EOF (Ctrl+D) handling ====="
(
    sleep 1
    # just simulate EOF, no input
) | $SHELL

echo
echo "===== TEST 6: SIGINT (Ctrl+C) handling ====="
(
    sleep 1
    kill -s SIGINT $$
    echo "exit"
) | $SHELL

# Clean up
rm -f $TEST_FILE
