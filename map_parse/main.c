#include "config/config.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_config config;

	if (argc < 2 || (argc == 3 && !ft_strcmp(argv[2], "--save")))
		return (write(2, "Error\n", 6));
	if (!parse_config(&config, argv[1]))
		return (write(2, "Error\n", 6));
	printf("height: %d, width: %d\n", config.req_height, config.req_width);
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", config.tex_path[T_NO], config.tex_path[T_SO], config.tex_path[T_WE], config.tex_path[T_EA]);
	printf("SKY: %X\nFLOOR: %X\n", config.cf_color[0], config.cf_color[1]);
	printf("SPRITE: %s\n", config.tex_path[T_SPRITE]);
	clear_config(&config);
	return (0);
}
