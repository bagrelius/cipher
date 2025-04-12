# Cypher

Cypher is a command-line tool for encrypting and decrypting files using AES encryption in CBC mode. It allows users to securely encrypt files and later decrypt them using a specified key and initialization vector (IV).

## Features

- Encrypt files with AES encryption in CBC mode.
- Decrypt encrypted files back to their original content.
- Specify custom keys and initialization vectors.

## Requirements

- C++11 or later
- Crypto++ library

## Installation

1. Install the Crypto++ library on your system.
2. Clone this repository to your local machine.
3. Build the project using the provided `Makefile`:

   ```
   make
   ```

## Usage

```
./cypher -f <filename> [-k <key>] [-i <iv>] [-d <decrypt extension>]
```
