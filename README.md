# Conway's Game of Life

## COMPATIBILITY
Life is compatible with Linux.

## BUILDING
To build, clone this repository and type:
```make life```

Or if you don't have Make installed:
```gcc -o bin/life src/*.c```

## DESCRIPTION
*From https://en.wikipedia.org/wiki/Conway's_Game_of_Life:*
> The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.

This program is a finite Game of Life simulator that will display the simulation on the terminal in real time. A solid character represents a living cell and whitespace represents a dead cell. Whether a cell lives or dies each generation is determined by three rules:

1. Any living cell with two or three neighbors survives.
2. Any dead cell with exactly three living neighbors becomes a living cell.
3. All other cells die or remain dead.

## USAGE
life [OPTIONS]

Note: simulates endlessly by default. Press Ctrl+C to stop simulating or use the -g option to specify a maxiumum number of generations.

## OPTIONS
-d [ms]:	Specify the delay between updates in miliseconds. Default value is 10ms.
			Increasing this value can help with flickering.
			Must be a positive value or zero.

-h:			Display the help page.

-g [N]:     Specify the maximum number of generations. Default is endless.
			Simulation ends when this value is reached.
			Must be a positive value or zero.

-s [N]:		Specify the simulation seed. Default value is random.
			Must be a positive value or zero. Zero is random.

-x [N]:		Specify the simulation size in cells along the x-axis. Fills the terminal by default.
			Must be a positive, nonzero value.

-y [N]:		Specify the simulation size in cells along the y-axis. Fills the terminal by default.
			Must be a positive, nonzero value.