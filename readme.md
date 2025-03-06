# `simple_lang_compiler_8_bit.cpp` for 8_bit_cpu

A minimalistic compiler for SimpleLang targeting an 8-bit CPU architecture. This project implements a complete compiler pipeline including lexical analysis, parsing, and code generation for a simple high-level language.

## About SimpleLang

SimpleLang is a basic high-level language designed for educational purposes, which includes:

- Variable declarations (`int a;`)
- Assignment statements (`a = 10;`)
- Arithmetic operations (`+`, `-`)
- Conditional statements (`if (a == b) { ... }`)

Example program:

```
// Variable declaration 
int a;
int b; 
int c; 

// Assignment 
a = 10; 
b = 20; 
c = a + b; 

// Conditional 
if (c == 30) { 
  c = c + 1; 
}
```

## Project Structure

```
.
├── README.md
├── include
│   ├── code_generator.hpp
│   ├── lexer.hpp
│   ├── parser.hpp
│   └── types.hpp
├── src
│   ├── code_generator.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   └── parser.cpp
├── CMakeLists.txt
└── test_program.sl
```

## Building the Project

### Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++17 support (GCC, Clang, MSVC)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simplelang-compiler.git
   cd simplelang-compiler
   ```

2. Generate the build files:
   ```bash
   cmake -B build
   ```

3. Build the project:
   ```bash
   cd build
   make
   ```

4. Run the compiler:
   ```bash
   ./bin/simple_compiler ../test_program.sl output.asm
   ```

## Usage

```
simple_compiler <input_file> <output_file>
```

Where:
- `<input_file>` is a SimpleLang source file
- `<output_file>` is the name for the generated assembly output

## Compiler Pipeline

1. **Lexical Analysis**: Tokenizes the source code into a stream of tokens
2. **Parsing**: Constructs an Abstract Syntax Tree (AST) from the token stream
3. **Code Generation**: Translates the AST into assembly code for the target 8-bit CPU

## Target Architecture

This compiler generates assembly code for the 8-bit CPU described in the [lightcode/8bit-computer](https://github.com/lightcode/8bit-computer) project. The CPU is implemented in Verilog and includes a simple instruction set suitable for educational purposes.

## Development

To contribute to the project:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Commit your changes: `git commit -am 'Add feature'`
4. Push to the branch: `git push origin feature-name`
5. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Based on the 8-bit CPU design from [lightcode/8bit-computer](https://github.com/lightcode/8bit-computer)
- Inspired by various compiler design textbooks and resources
