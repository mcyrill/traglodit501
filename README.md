# traglodit501 Text File Archiver

## Introduction

Traglodit501 is a command-line text file archiver that utilizes the Huffman algorithm for compression. It allows you to compress and decompress text files in ASCII format efficiently.

## Installation

To install Traglodit501, follow the steps below:
1. Clone the repository from GitHub:
   ```bash
   git clone https://github.com/mcyrill/traglodit501
   ```
2. Navigate to the project directory:
   ```bash
   cd traglodit501
   ```
3. Build project via cmake:
   ```bash
   cmake .
   cmake --build .
   ```
## Usage

Traglodit501 provides a simple command-line interface for compressing and decompressing text files. Follow the instructions below to use the tool:

### Compression

To compress a text file, use the following command:
```bash
traglodit501 encode --file filename
```
Replace filename with the path to the text file you want to compress. The compressed file will be saved in the same directory with a .traglodit501 extension.

### Decompression
To decompress a compressed file, use the following command:

```bash
traglodit501 decode --file filename
```

Replace filename with the path to the compressed file you want to decompress. The decompressed file will be saved in the same directory with the original file extension.

## Examples

Here are some examples of using Traglodit501:

1. Compressing a text file:
   ```bash
   traglodit501 encode --file example.txt
   ```
   This command will compress the example.txt file and save it as example.txt.traglodit501.
2. Decompressing a file:
   ```bash
   traglodit501 decode --file example.txt.traglodit501
   ```
   This command will decompress the example.txt.t501 file and save it as example.txt.