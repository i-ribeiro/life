#pragma once
#include <stdint.h>

typedef uint8_t cell;

// externs from game.h
extern unsigned short g_sim_sx;
extern unsigned short g_sim_sy;
extern cell * g_cells;
extern cell * g_cells_buffer;

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