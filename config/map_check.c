#include "config.h"

int		check_map_row(t_list *map_buffer)
{
	int row;

	row = 0;
	while (map_buffer)
	{
		map_buffer = map_buffer->next;
		row++;
	}
	return (row);
}

int		check_map_col(t_list *map_buffer)
{
	int col;
	int max_col;

	max_col = 0;
	while (map_buffer)
	{
		col = ft_strlen(map_buffer->content) - 1;
		while (map_buffer->content[col] == ' ')
			col--;
		if (max_col < col + 1)
			max_col = col + 1;
		map_buffer = map_buffer->next;
	}
	return (max_col);
}

int		check_map(t_config *config, int *row, int *col)
{
	int r;
	int c;

	if (config->map[r][c] == ' ')
		return (0);
	if (config->map[r][c] == '1' || config->map[r][c] == '0')
}

int		valid_map_check(t_config *config)
{
	int r;
	int c;
	int is_valid;
	int ;

	is_valid = 0;
	if (config->map_row <= 2 || config->map_col <= 2)
		return (0);
	r = 0;
	while (r < config->map_row)
	{
		c = 0;
		while (c < config->map_col)
		{
			if (config->map[r][c] == '0')
			{
				is_valid = 1;
				if (check_map(config, r, c) == 0)
				{
					write(2, "Error\n", 6);
					return (0);
				}
			}
			c++;
		}
		r++;
	}
	if (!is_valid)
		write(2, "Error\n", 6);
}