/**** Includes ****/

#include "life.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


/**** Statics ****/

/*
 * Whether or not to continue simulating.
 */
static unsigned char g_simulate = 0;

/*
 * Grid size along the X axis.
 */
static unsigned short g_sim_sx = 50;

/*
 * Grid size along the Y axis.
 */
static unsigned short g_sim_sy = 50;

/*
 * Cell values.
 */
static cell * g_cells = NULL;

/*
 * Cell values buffer to hold updated values.
 */
static cell * g_cells_buffer = NULL;


/**** Function Definitions ****/

int simulate(int maxgen, unsigned delay)
{
	g_simulate = 1;

	unsigned i = 0;

	while (g_simulate)
	{
		// stop simulation at max generations, if set
		if (i >= (unsigned) maxgen && maxgen >= 0)
			stop();

		draw();
		update();
		usleep(delay * 1000);
		++i;
	}

	return i;
}

void stop(void)
{
	g_simulate = 0;
}

void initialize(int sx, int sy)
{
	// set simulation size
	g_sim_sx = sx;
	g_sim_sy = sy;

	// allocate cells
	const int size = g_sim_sx * g_sim_sy * sizeof(cell);

	if (g_cells == NULL)
		g_cells = (cell *) malloc(size);
	else
		g_cells = realloc(g_cells, size);

	if (g_cells_buffer == NULL)
		g_cells_buffer = (cell *) malloc(size);
	else
		g_cells_buffer = realloc(g_cells_buffer, size);

	randomize();
}

void terminate(void)
{
	if (g_cells)
		free(g_cells);

	if(g_cells_buffer)
		free(g_cells_buffer);
}

int count(short x, short y)
{
	unsigned short count = 0;

	for (int dy = -1; dy <= 1; ++dy)
	{
		for (int dx = -1; dx <= 1; ++dx)
		{
			int ix = x + dx;
			int iy = y + dy;

			if (ix == x && iy == y)
				continue;			// skip cell if it's the target cell

			if (getcell(ix, iy))
				++count;
		}
	}

	return count;
}

cell evaluate(short x, short y)
{
	cell living = getcell(x, y);
	unsigned short neighbors = count(x, y);

	cell eval = living;

	if (!living && neighbors == 3)		// any dead cell with 3 live neighbors becomes a live cell
		eval = LIVE;

	else if (living && neighbors < 2)	// any living cell with less than three live neighbors becomes a dead cell
		eval = DEAD;

	else if (living && neighbors > 3)	// any living cell with more than three living neighbors becomes a dead cell 
		eval = DEAD;

	return eval;
}

void update(void)
{
	// evaluate each cell and set new value
	for (int y = 0; y < g_sim_sy; ++y)
		for (int x = 0; x < g_sim_sx; ++x)
			setcell(x, y, evaluate(x, y));

	// apply updates 
	apply();
}

void draw(void)
{
	// print each cell as a character 
	for (int y = 0; y < g_sim_sy; ++y)
	{
		for (int x = 0; x < g_sim_sx; ++x)
		{
			char c = getcell(x, y) ? DISPLAY_LIVE : DISPLAY_DEAD;
			putchar(c);
			putchar(' ');
		}
		putchar('\n');
	}
}

int xytoi(short x, short y)
{
	// wrap values
	x %= g_sim_sx;					// upper bound
	y %= g_sim_sy;

	if (x < 0) x = x + g_sim_sx;	// lower bound
	if (y < 0) y = y + g_sim_sy;	

	// flatten coordinates 
	return x + (y * g_sim_sx);
}

cell getcell(short x, short y)
{
	assert(g_cells);			// ensure g_cells is allocated

	return g_cells[xytoi(x, y)];
}

void setcell(short x, short y, cell value)
{
	assert(g_cells_buffer);		// ensure g_cells_buffer is allocated

	// set value in buffer cells array. call update() to propagate to the master cells array
	g_cells_buffer[xytoi(x, y)] = value;
}

void apply(void)
{
	// ensure cells are allocated
	assert(g_cells);
	assert(g_cells_buffer);

	// propagate each value in the buffer cells array to the master grid
	for (int i = 0; i < g_sim_sx * g_sim_sy; ++i)
		g_cells[i] = g_cells_buffer[i];
}

void randomize(void)
{
	// set each cell to a random value (0..1)
	for (unsigned short y = 0; y < g_sim_sy; ++y)
		for (unsigned short x = 0; x < g_sim_sx; ++x)
			setcell(x, y, (cell) rand() % 2);

	// apply updates
	apply();
}