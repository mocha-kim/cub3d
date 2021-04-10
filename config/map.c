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

void	player_set(t_config *config, int x, int y)
{
	config->pos_x = x;
	config->pos_y = y;
	config->dir = config->map[y][x];
	config->map[y][x] = '0';
}

void	copy_map(t_config *config, t_list *map_buffer)
{
	int		i;
	int		j;

	i = -1;
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
		{
			if (!(map_buffer->content[j]))
			{
				while (j < config->map_col)
					config->map[i][j++] = ' ';
				break ;
			}
			config->map[i][j] = map_buffer->content[j];
			if (ft_strrchr("NSWE", config->map[i][j])
			&& !config->pos_x && !config->pos_y)
				player_set(config, j, i);
		}
		config->map[i][config->map_col] = 0;
		map_buffer = map_buffer->next;
	}
}

int		parse_map(t_config *config, t_list *map_buffer)
{
	int	i;

	if (!(config->map_row = check_map_row(map_buffer)))
		return (0);
	if (!(config->map_col = check_map_col(map_buffer)))
		return (0);
	if (!(config->map = malloc(sizeof(char*) * (config->map_row + 1))))
		return (0);
	i = 0;
	while (i < config->map_row)
		if (!(config->map[i++] = malloc(sizeof(char) * (config->map_col + 1))))
			return (-1);
	copy_map(config, map_buffer);
	config->map[config->map_row] = 0;
	return (valid_map_check(config));
}