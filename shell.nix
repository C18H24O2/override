{
  pkgs ? import <nixpkgs> {},
}:

(pkgs.mkShell.override {
  stdenv = pkgs.llvmPackages_21.stdenv;
}) {
  nativeBuildInputs = with pkgs; [
    ltrace
    ghidra-bin
    strace
    ropgadget
    sshpass
    python313
  ];
}
