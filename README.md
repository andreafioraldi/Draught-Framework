> At least for the people who send me mail about a new language that they're designing, the general advice is: do it to learn about how to write a compiler. Don't have any expectations that anyone will use it, unless you hook up with some sort of organization in a position to push it hard. It's a lottery, and some can buy a lot of the tickets. There are plenty of beautiful languages (more beautiful than C) that didn't catch on. But someone does win the lottery, and doing a language at least teaches you something.
>
> Dennis Ritchie

# Draught Framework
is a software framework composed of three core components:
+ Dubbel, a run-time environment with its bytecode and its assembly
+ Stout, an untyped programming language that is compiled to Dubbel bytecode
+ IPA, a set of class libraries written in Stout and C++

Dubbel is composed of a virtual machine, an assembler, a disassembler, and an archive utility.
The archiver stores multiple bytecode files connected to the main file as libraries.
It also has a module called Dubbel Builder, a library designed to simplify the creation of compilers that target the Dubbel bytecode.

Stout comes with a compiler and a shell.

To compile with Visual Studio put the MPIR and MPFR libs and headers in the project root folder.
You can download precompiled MPIR and MPFR at :
+ (x86) http://andreafioraldi.altervista.org/mpir_mpfr_msvcx86.zip
+ (x86_64) http://andreafioraldi.altervista.org/mpir_mpfr_msvcx86_64.zip

(ported from a 2015 SourceForge project that I made)
