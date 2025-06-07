#!/usr/bin/env bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <ip> <level>"
	echo "Note that logging in as \"level1\" will use the flag from \"level0\""
    exit 1
fi

IP=$1

if [[ $2 == level00 ]]; then
	set -x
	sshpass -p "level00" ssh $2@$IP -p 4242
elif [[ $2 == level* ]]; then
	level=${2#level}
	flag=$(cat level$((level-1))/flag)
	set -x
	sshpass -p "$flag" ssh $2@$IP -p 4242
fi
