#include "../includes/cub3d_bonus.h"

void	draw_rectangle(t_info *info, int x, int y, int color)
{
	int i;
	int j;
	int	width;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			width = info->conf.map_col * TILE_SIZE;
			info->img.data[(y  + i) * width + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_info *info)
{
	int		i;
	int		j;

	i = 0;
	while (i < info->conf.map_row)
	{
		j = 0;
		while (j < info->conf.map_col)
		{
			if (info->conf.map[i][j] == 1)
				draw_rectangle(info, j, i, 0xFFFFFF);
			else
				draw_rectangle(info, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

