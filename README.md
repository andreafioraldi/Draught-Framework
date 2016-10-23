# Draught Framework
is a software framework composed by three core components:
+ Dubbel, a run-time environment with its bytecode and its assembly
+ Stout, an untyped programming language that is compiled to Dubbel bytecode
+ IPA, a set of class libraries written in Stout and C++

Dubbel is composed by a virtual machine, an assembler, a disassembler and an archive utility.
The archiver is used to store multiple bytecode files connected to a main file as libraries.
It also has a module called Dubbel Builder, a library designed to simplify the creation of compilers that target the dubbel bytecode.

Stout come with a compiler and a shell.

To compile with Visual Studio put the MPIR and MPFR libs and headers in the project root folder.
You can download precompiled x86 MPIR and MPFR at http://andreafioraldi.altervista.org/mpir_mpfr_msvcx86.zip
