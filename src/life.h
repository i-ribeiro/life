#pragma once
#include <stdint.h>

#define LIVE 1
#define DEAD 0

#define DISPLAY_LIVE '#'
#define DISPLAY_DEAD ' '

#define GRID_SZ_FULL 0
#define ENDLESS -1
#define SEED_RAND 0

/*
 * Type to represent a cell.
 */
typedef uint8_t cell;

/*
 * Start simulation. 
 * maxit: The maximum number of generations before simulation stops. Set to ENDLESS for unlimited generations.
 * delay: the delay between updates in miliseconds.
 * Returns the number of generations simulated.
 */
int simulate(int maxit, unsigned delay);

/*
 * Stop simulation.
 */
void stop(void);

/*
 * Initialize the grid.
 * Must be called before simulation can start.
 * sx: Simulation size along the X axis.
 * sy: Simulation size along the Y axis.
 */
void initialize(int sx, int sy);

/*
 * Deallocate resources.
 */
void terminate(void);

/*
 * Count the number of live neighbors for a given cell.
 * x: The X component of the target cell.
 * y: The Y component of the target cell.
 * Returns the number of living neighbors.
 */
int count(short x, short y);

/*
 * Evaluate the state of a cell.
 * Returns either LIVE or DEAD representing the updated state of the cell.
 */
cell evaluate(short x, short y);

/*
 * Update the game.
 */
void update(void);

/*
 * Print the grid to the console.
 */
void draw(void);

/*
 * Translate a 2D cell coordinate to an array index.
 * Any values that exceed simulation boudaries are wrapped.
 * x: The X component of the target cell.
 * y: The Y component of the target cell.
 * Returns an array index.
 */
int xytoi(short x, short y);

/*
 * Get the value of a cell.
 * x: The X component of the target cell.
 * y: The Y component of the target cell.
 * Returns either LIVE or DEAD representing the state of the cell.
 */
cell getcell(short x, short y);

/*
 * Set the value of a cell.
 * Buffered - call apply() to finalize.
 * x: The X component of the target cell.
 * y: The Y component of the target cell.
 * value: The value to assign to the target cell. Set to LIVE or DEAD.
 */
void setcell(short x, short y, cell value);

/*
 * Apply buffer values.
 */
void apply(void);

/*
 * Randomize the board. 
 */
void randomize(void);