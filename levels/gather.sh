#!/usr/bin/env bash

if [ $# -ne 2 ]; then
	echo "Usage: $0 <ip> <level>"
    exit 1
fi

IP=$1
LEVEL=$2
if [[ $LEVEL == all ]]; then
	for i in level{00..09}; do
		./$0 $IP $i
	done
	exit
fi

mkdir -p bins

if [[ $LEVEL == level00 ]]; then
	set -x
	sshpass -p "level00" scp -P 4242 $LEVEL@$IP:$LEVEL bins/$LEVEL
elif [[ $LEVEL == level* ]]; then
	level=${LEVEL#level0}
	flag=$(cat level0$((level-1))/flag)
	set -x
	sshpass -p "$flag" scp -P 4242 $LEVEL@$IP:$LEVEL bins/$LEVEL
fi
