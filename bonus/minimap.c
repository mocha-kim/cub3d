#include "../includes/cub3d_bonus.h"

void	draw_rectangle(t_info *info, int x, int y, int color)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE && i + x < info->conf.req_height)
	{
		j = 0;
		while (j < TILE_SIZE && j + y < info->conf.req_width)
		{
			info->buf[x + i][y + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_info *info)
{
	int		i;
	int		j;
	int		offset_x;

	offset_x = info->conf.req_width / 2;
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

