#include "main.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Argument invalid\n");
		return (0);
	}
	init_philos(argc, argv);
	return (0);
}
