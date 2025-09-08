# horizon [![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20.html) [![License](https://img.shields.io/github/license/Water-Engine/horizon)](LICENSE) [![LOC](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Water-Engine/horizon/loc/.github/loc_badge.json)](https://github.com/Water-Engine/horizon/actions/workflows/loc.yml) [![Last commit](https://img.shields.io/github/last-commit/Water-Engine/horizon)](https://github.com/Water-Engine/horizon) [![Formatting](https://github.com/Water-Engine/horizon/actions/workflows/format.yml/badge.svg)](https://github.com/Water-Engine/horizon/actions/workflows/format.yml) [![CI](https://github.com/Water-Engine/horizon/actions/workflows/ci.yml/badge.svg)](https://github.com/Water-Engine/horizon/actions/workflows/ci.yml)
A polyglot opening generator, written in C++, powered by Disservin's [chess-library](https://github.com/Disservin/chess-library).

# Getting Started
```shell
git clone https://github.com/Water-Engine/horizon.git
cd horizon
make -j4 run
```

By default, horizon is designed to scan a directory named `pgn` and will build a polyglot `.bin` out of all the files ending in `.pgn`. You can change the parent directory or expected file extension through command line flags. To view the help info, simply pass the `-help` flag to the executable. You can pass flags as follows:
```shell
./horizon -depth=4
```

## Run Options
The following help menu is shown when running horizon with the `-help` flag:
```
Usage: ./horizon [OPTIONS]
OPTIONS:
    -help
        Print this help message
    -depth <int>
        The maximum depth considered an opening position
        Default: 6
    -parent <str>
        The parent directory to search for pgn files
        Default: pgn
    -ext <str>
        The file extension of a pgn file
        Default: .pgn
    -single <str>
        A single filepath to use for the book if full directory scanning is not needed
        Default:
    -output <str>
        The file to output the binary file to
        Default: polyglot.bin
```

# Core Dependencies
- g++ with C++20
- GNU Make
- Clang-format
- [Catch2](https://github.com/catchorg/Catch2) (included in this repository)
- [cloc](https://github.com/AlDanial/cloc) (for cloc make target > optional)
- [python](https://www.python.org/downloads/) for script running

# Game Database
All game data in this repository's included PGN files is provided by [PGN Mentor](https://www.pgnmentor.com/files.html). A wide breadth of openings are included, as well specific games from high level tournaments/player and world championship games.

# A Warning...
This polyglot generator uses the [chess-library](https://github.com/Disservin/chess-library) to generate the corresponding position hashes. Due to the nature of the polyglot format, you must use the same zobrist hashing keys to properly query opening positions. This requires that you use the same library, or that you use the exact same seeded randoms for your hashing implementation. To my knowledge, this library uses the standard polyglot randoms, but I cannot make any guarantee that generated tables will be universally compatible. From a quick check, the randoms align with [python's chess library](https://python-chess.readthedocs.io/en/latest/index.html).

# For Developers
Contributing guidelines, information on tests, formatting, and profiling can be found in [CONTRIBUTING.md](.github/CONTRIBUTING.md).