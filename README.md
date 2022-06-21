# https-dh

Implementação do funcionamento parcial de HTTPS para o curso de criptografia do PPGCC - PUCRS.

## Pré-Requisitos

* Compilador `g++` com suporte a std `c++17`
* Biblioteca `CLI11`
* Biblioteca `cryptopp`
* Biblioteca `GMP`

## Compilando

```
meson build
ninja -C build
```
## Executando

```
$ ./dh --help
Partial HTTPS functionality example.
Usage: ./dh [OPTIONS] SUBCOMMAND

Options:
  -h,--help                   Print this help message and exit

Subcommands:
  keygen                      Generate a key based on received B and generated A
  reverse                     Decrypt a CYPHERTEXT, reverse it, and reencrypt using a KEY.
```

```
$ ./dh keygen --help
Generate a key based on received B and generated A
Usage: ./dh keygen [OPTIONS] B

Positionals:
  B TEXT REQUIRED             B value computed from p, g, and b.

Options:
  -h,--help                   Print this help message and exit
```

```
$ ./dh reverse --help
Decrypt a CYPHERTEXT, reverse it, and reencrypt using a KEY.
Usage: ./dh reverse [OPTIONS] CYPHERTEXT KEY

Positionals:
  CYPHERTEXT TEXT REQUIRED    Cyphertext to modify.
  KEY TEXT REQUIRED           AES key.

Options:
  -h,--help                   Print this help message and exit
```
