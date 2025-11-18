#!/usr/bin/env bash

set -o pipefail

if [ $# -ne 1 ]; then
	echo "Usage: $0 <ip>"
	exit 1
fi

IP=$1

function test() {
	local lvl=$1
	if ! [ -d $lvl ]; then
		echo "$lvl does not exist"
		return
	fi
	if ! [ -f $lvl/flag ]; then
		echo "$lvl doesn't have a flag"
		return
	fi
	echo -n "Testing $lvl flag..."
	local flag=$(cat $lvl/flag)
	local next=$2
	SSHPASS="$flag" sshpass -e ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no $next@$IP -p 4242 "exit" >/dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo " KO"
		return
	fi
	echo " OK"
}

echo "Doing a test connect on level00..."
SSHPASS="level00" sshpass -e ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no level00@$IP -p 4242 "exit"
if [ $? -ne 0 ]; then
	echo "Could not connect to level00, something's wrong"
	echo "Maybe try running 'ssh -p 4242 level00@$IP' first to accept the public key"
	exit 1
fi


for lvl in {0..8}; do
	test "level0$lvl" "level0$((lvl+1))"
done
test "level09" "end"
