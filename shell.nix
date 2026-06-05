with import <nixpkgs> {};

mkShell {
  buildInputs = [
    gcc
    gnumake
    gdb
    valgrind
    git
    curl
  ];
}
