#!/usr/bin/env bash

. $(dirname $0)/common.sh

echo "Running VM"
qemu-system-x86_64 \
    -m 2G \
    -cdrom "$ISO" \
    -enable-kvm \
    -cpu host \
    -smp 4
