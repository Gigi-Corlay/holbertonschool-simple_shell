#!/bin/bash

echo "=== CHECK FAILURES SIMPLE_SHELL ==="

echo
echo "1) Non-interactive mode (no prompt expected)"
echo "-------------------------------------------"
echo "ls" | ./hsh > out.txt
if grep -q "(\$)" out.txt; then
	echo "❌ FAIL: prompt printed in non-interactive mode"
else
	echo "✅ OK"
fi
cat out.txt
rm -f out.txt

echo
echo "2) cd to invalid directory (error message)"
echo "-------------------------------------------"
echo -e "cd no_such_dir\npwd\nexit" | ./hsh

echo
echo "3) exit builtin (should terminate shell)"
echo "----------------------------------------"
echo -e "exit\nls" | ./hsh

echo
echo "4) SIGINT behavior (Ctrl+C)"
echo "----------------------------------------"
echo "Run ./hsh and press Ctrl+C"
echo "Expected: newline + prompt only"

echo
echo "5) cd without HOME (unset HOME)"
echo "----------------------------------------"
unset HOME
echo -e "cd\npwd\nexit" | ./hsh
export HOME=/Users/$(whoami)

echo
echo "6) cd - (optional but sometimes tested)"
echo "----------------------------------------"
echo -e "pwd\ncd ..\ncd -\npwd\nexit" | ./hsh

echo
echo "7) invalid command"
echo "----------------------------------------"
echo "no_such_command" | ./hsh

echo
echo "=== END CHECKS ==="
