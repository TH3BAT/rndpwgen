# rndpwgen

A tiny offline Base58 password generator written in C.

## Features

* Cryptographically secure randomness
* Base58 character set (avoids `0`, `O`, `I`, and `l`)
* First character is always numeric (a nod to an older Bitcoin wallet convention)
* Single-file utility with no external dependencies
* Small executable (~35 KB)

## Build

### macOS

```bash
cc rndpwgen.c -o rndpwgen
```

### Linux

```bash
cc rndpwgen.c -o rndpwgen
```

## Usage

Generate a 34-character password:

```bash
./rndpwgen 34
```

Example output:

```text
7QmF3nKpW6Yt9R...
```

## Notes

This program generates passwords entirely offline.

The implementation uses platform-specific cryptographically secure random number generators behind a small abstraction layer while keeping the remainder of the code portable.

## License

MIT

History

This utility was originally written to simplify the generation of long random passwords for environments requiring frequent password changes. It has since been modernized with cryptographically secure randomness while remaining a small, single-file offline utility.


