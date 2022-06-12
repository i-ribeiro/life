/**** Includes ****/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "life.h"


/**** Defines ****/

#define OPTSTR "hx:y:g:d:s:"


/**** Function Declarations ****/

/*
 * Handle system signals.
 */
void sighandler(int signum);

/*
 * Display the help page.
 */
void help(void);

/*
 * Retrieve the dimensions of the host terminal.
 */
void getwinsize(unsigned short int *x, unsigned short int *y);


/**** Main ****/

int main(int argc, char *argv[])
{
	/* handle system signals */

	signal(SIGABRT, sighandler);
	signal(SIGHUP, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGSEGV, sighandler);
	signal(SIGSTOP, sighandler);
	signal(SIGTSTP, sighandler);
	signal(SIGTERM, sighandler);


	/* set default simulation settings */

	unsigned short sx = GRID_SZ_FULL;	// simulation size x 		(default: fullscreen)
	unsigned short sy = GRID_SZ_FULL;	// simulation size y 		(default: fullscreen)
	int maxg = ENDLESS;					// maximum generations 		(default: unlimited)
	unsigned delay = 10;				// update delay 			(default: 10ms)
	unsigned seed = SEED_RAND;			// simulation seed 			(default: random)
	

	/* parse args */

	char opt;
	// getopt externs
	extern char *optarg;
	extern int opterr;

	while ((opt = getopt(argc, argv, OPTSTR)) != -1)
	{
		char *endptr;
		long x;			// used for all arguments

		switch (opt)
		{
		case 'h':		// help
			help();
			exit(EXIT_SUCCESS);
			break;

		case 'x':		// sim size x
			x = strtoul(optarg, &endptr, 10);	// base 10

			if (x > (long) 0)
				sx = (unsigned short) x;

			else
			{
				fprintf(stderr, "%c: Expected a positive, non-zero integer.\n", opt);
				exit(EXIT_FAILURE);
			}

			break;

		case 'y':		// sim size y
			x = strtoul(optarg, &endptr, 10);

			if (x > (long) 0)
				sy = (unsigned short) x;

			else
			{
				fprintf(stderr, "%c: Expected a positive, non-zero integer.\n", opt);
				exit(EXIT_FAILURE);
			}

			break;

		case 'g':		// max generations
			maxg = strtol(optarg, &endptr, 10);

			if (maxg >= (long) ENDLESS && endptr != optarg)	// if endptr == optarg, optarg is not a number
				maxg = maxg;

			else
			{
				fprintf(stderr, "%c: Expected an integer greater than %d.\n", opt, ENDLESS);
				exit(EXIT_FAILURE);
			}

			break;

		case 'd':		// delay between updates
			x = strtoul(optarg, &endptr, 10);

			if (x >= (long) 0 && endptr != optarg)
				delay = (unsigned) x;

			else
			{
				fprintf(stderr, "%c: Expected a positive integer.\n", opt);
				exit(EXIT_FAILURE);
			}

			break;

		case 's':		// sim seed
			x = strtoul(optarg, &endptr, 10);

			if (x >= (long) SEED_RAND && endptr != optarg)
				seed = (unsigned) x;

			else
			{
				fprintf(stderr, "%c: Expected a positive integer.\n", opt);
				exit(EXIT_FAILURE);
			}

			break;

		case '?':
			exit(EXIT_FAILURE);
			break;

		default:
			abort();
			break;
		}
	}


	/* set the simulation seed */

	if (seed == SEED_RAND) seed = (unsigned) time(NULL);
	srand(seed);


	/* set simulation size to terminal dimensions if set to fullscreen */

	unsigned short wx = 0, wy = 0;
	getwinsize(&wx, &wy);
	if (sx == GRID_SZ_FULL) sx = (wx / 2) - (1 - wx % 2);
	if (sy == GRID_SZ_FULL) sy = wy - 1;


	/* simulate */

	initialize(sx, sy);
	unsigned g = simulate(maxg, delay);
	terminate();
	

	/* end */

	printf(
		"\nSimulation stopped at generation %u."
		"\nSeed: %u \n"
	, g - 1
	, seed);

	return EXIT_SUCCESS;
}


/**** Function definitions ****/

void sighandler(int signum)
{
	switch (signum)
	{
	default:
		stop();		// stop on any signal received to deallocate resources
		break;
	}
}

void getwinsize(unsigned short int *x, unsigned short int *y)
{
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    *x = w.ws_col;
	*y = w.ws_row;
}

void help(void)
{
	puts(
		"Conway's Game of Life \n\n"

		"USAGE\n"
			"\tlife [OPTIONS]\n\n"

			"\tNote: simulates endlessly by default. Press Ctrl+C to stop simulating or\n"
			"\tuse the -g option to specify a maximum number of generations.\n\n"

		"OPTIONS\n"
			"-d [ms]:\tSpecify the delay between updates in miliseconds. Default value is 10ms.\n"
			"\t\tIncreasing this value can help with flickering.\n"
			"\t\tMust be a positive value or zero.\n\n"

			"-h:\t\tDisplay the help page.\n\n"

			"-g [N]:\t\tSpecify the maximum number of generations. Default is endless.\n"
			"\t\tSimulation ends when this value is reached.\n"
			"\t\tMust be a positive value or zero.\n\n"

			"-s [N]:\t\tSpecify the simulation seed. Default value is random.\n"
			"\t\tMust be a positive value or zero. Zero is random.\n\n"

			"-x [N]:\t\tSpecify the simulation size in cells along the x-axis. Fills the terminal by default\n"
			"\t\tMust be a positive, nonzero value.\n\n"

			"-y [N]:\t\tSpecify the simulation size in cells along the y-axis. Fills the terminal by default\n"
			"\t\tMust be a positive, nonzero value.\n");
}