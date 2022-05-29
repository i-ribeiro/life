#include "cell.h"
#include <stdlib.h>

int xytoi(short x, short y)
{
	// wrap values
	x %= g_sim_sx;					// upper bound
	y %= g_sim_sy;

	if (x < 0) x = x + g_sim_sx;	// lower bound
	if (y < 0) y = y + g_sim_sy;	

	// flatten coordinates to index
	return x + (y * g_sim_sx);
}

cell getcell(short x, short y)
{
	return g_cells[xytoi(x, y)];
}

void setcell(short x, short y, cell value)
{
	// set value in buffer cells array. call update() to propagate to the master cells array
	g_cells_buffer[xytoi(x, y)] = value;
}

void apply(void)
{
	// propagate each value in the buffer cells array to the master grid
	for (int i = 0; i < g_sim_sx * g_sim_sy; ++i)
		g_cells[i] = g_cells_buffer[i];
}

void randomize(void)
{
	// set each cell to a random value (0..1)
	for (unsigned short y = 0; y < g_sim_sy; ++y)
	{
		for (unsigned short x = 0; x < g_sim_sx; ++x)
		{
			unsigned short val = rand() % 2;
			setcell(x, y, val);
		}
	}

	// apply updates
	apply();
}