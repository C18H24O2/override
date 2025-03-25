#!/usr/bin/env bash

. $(dirname $0)/common.sh

echo "Running VM"
VM_NAME="Override_VM"
VBoxManage unregistervm "$VM_NAME" --delete || true
VBoxManage createvm --name "$VM_NAME" --register
VBoxManage modifyvm "$VM_NAME" --memory 2048 --cpus 2 --ostype Debian --nic1 nat
VBoxManage storagectl "$VM_NAME" --name "IDE Controller" --add ide
VBoxManage storageattach "$VM_NAME" --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium "$ISO"
VBoxManage modifyvm "$VM_NAME" --nic1 bridged --bridgeadapter1 "${1:-eno2}"
VBoxManage startvm "$VM_NAME"
