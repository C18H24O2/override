{
  pkgs ? import <nixpkgs> {},
}:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    ltrace
    ghidra-bin
    strace
  ];
}
