# Cipher

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
./cipher -f <filename> [-k <key>] [-i <iv>] [-d <decrypt extension>]
```

## Options
- -f <filename>: The name of the file to encrypt or decrypt (required).
- -k <key>: The encryption/decryption key (16 bytes). Default: 0123456789ABCDEF.
- -i <iv>: The initialization vector (16 bytes). Default: FEDCBA9876543210.
- -d <decrypt_extension>: Decrypt the file and save it with the specified extension (eg., .txt).

## Examples

1. Encrypting a file 
   ```
   ./cipher -f test.txt -k "1234567890ABCDEF" -i "ABCDEF1234567890"
   ```
2. Decrypt a file
   ```
   ./cipher -f test.enc -d .txt
   ```
