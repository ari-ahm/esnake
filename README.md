# README

## Overview
This project centers on a specialized Snake bot designed to navigate the game board efficiently. It excels at discovering optimal moves and adapting to changing conditions.

## Key Features
- Outperforms similar algorithms with higher success rates.
- Achieves fewer steps than the “almighty” algorithm.

## Flaws
Although this Snake bot outperforms the “almighty” algorithm, it cannot achieve 100% success. The “almighty” algorithm follows a Hamiltonian path from the start, ensuring it covers every cell. In contrast, this bot does not follow a Hamiltonian path, which can lead to situations where most of the cells are occupied, and it's not possible to switch to a state that is a Hamiltonian path (which the snake should reach to complete).

## Usage
1. Build the project via the provided Makefile.
2. Run the executable with `./build/esnake`.
3. Alternatively, you can use the `run.sh` script to start the Snake game.

## Command Line Inputs
You can customize the game by providing command line arguments when running the executable:

1. **Width**: Set the width of the game board.
2. **Height**: Set the height of the game board.
3. **Seed**: Provide a seed for the random number generator to ensure reproducible results.

Example usage:
```sh
./bin/esnake [width] [height] [seed]
```

If no arguments are provided, the default values will be used.

## Controls
- **Arrow Keys**: Control the snake's direction (when bot mode is off).
- **C**: Decrease the game speed.
- **X**: Increase the game speed.
- **B**: Toggle bot mode on/off. (bot is enabled by default)

Enjoy testing this experiment in AI-driven Snake gameplay!


![mmli](https://github.com/user-attachments/assets/4829cea7-f7fc-40f5-b2f3-2c051e7379a7)
