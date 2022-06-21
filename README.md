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

## Exemplo

Para gerar chave a partir de um valor `B` recebido:
```
$ ./dh keygen 42E5103996D51DDA4F6B31BC2A5B106F41C38DC02824F0B07A2C7D06F265072CE61091AD98C8506F8A75043319092D7445671AFA6AE21302924C557E4894A5E13BEFDCEFFD013DC5A625DC3977493EC6DE6907858DB2DF6014A859DD5C9FDAAAE955996334F71F866B9543966435082394CCAC82BCA749264056ED0093E93950
```
O comando gera o valor `A` e a chave `K`.
```
79b14c2bdc34790611a8fe9418509ec65d16989bf282da619a85641562b8274a38aecb6c69ac169d2ff5e5055b09aefb5e5fe8e783bc07b9bc543a3b0082b7f443c3eab5bee374054fda5230a4863413e680b2e48440ca7b9d01c1d99462070ef5ff7c72421d60363a07d84cfb6455751dd8e6ff0e6b45098be21d706ae910ce
012702EFE8AFA149E05D97116AD1E516
```

Para descriptografar, reverter, e criptografar mensagem:
```
$ ./dh reverse 2493AF7B3958F7D4A870B6E040ACD580E2937CD28DE32445418334184DEA29478FCD15739629A8225F4F06B106033856CB34F50087410F45914CFEE3FA0F87D18E82A69F7FBAA017E5906796BC55744EBF4912D46970C4132C91C083D21DCC34 012702EFE8AFA149E05D97116AD1E516
```
Onde o primeiro argumento é a mensagem e o segundo a chave gerada anteriormente.
A saída é a mensagem recebida em texto claro e a mesma revertida e cifrada.
```
Legal Angelo. Agora inverte esta msg e manda ela de volta cifrada.
DED7942FC0F0010735C0EA13D2C8691804BA799A98A12F83F8691089D74237780B6DB8BD250658808A4DEFE80D7EF0465040D0092FD0C203AA107CE1392E3654E6B604B10DC37C2115A8B0BC9C4DC355CA513CA904B9DA5F6B8FE8E43E830A94
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
