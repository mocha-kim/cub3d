#include "config/config.h"

int main(int argc, char *argv[])
{
	t_config config;

	if (argc < 2 || (argc == 3 && !ft_strcmp(argv[2], "--save")))
		return (write(2, "Error\n", 6));
	if (!parse_config(&config, argv[1]))
		return (write(2, "Error\n", 6));
}
