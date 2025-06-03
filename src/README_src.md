# DIA - Duplicate Image Analyzer

A blazing fast, cross-platform CLI tool to find and delete duplicate images using cryptographic hashes.

## Folder Structure

```
src/
  main.c         // Entry point, argument parsing, program flow
  file_scan.c    // Directory traversal and file collection
  hash.c         // Hashing logic (MD5/SHA256)
  duplicate.c    // Duplicate detection and deletion
  log.c          // Logging utilities
  prompt.c       // Interactive prompt logic
  file_scan.h
  hash.h
  duplicate.h
  log.h
  prompt.h
include/         // (optional: for public headers)
Makefile
README.md
```

## Build

- Run `make` to build the project.
- The output binary will be `dia`.

## Usage

See README.md for usage instructions.