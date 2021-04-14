#include "../includes/cub3d_bonus.h"

void	draw_rectangle(t_info *info, int x, int y, int color)
{
	int i;
	int j;
	int	width;

	width = info->conf.req_width / 100;
	x *= width;
	y *= width;
	i = 0;
	while (i < width && (x + i < info->conf.req_height))
	{
		j = 0;
		while (j < width && (y + j < info->conf.req_width))
		{
			info->buf[x + i][y + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_player(t_info *info, double x, double y, int color)
{
	int i;
	int j;
	int	width;

	width = info->conf.req_width / 100;
	x *= width;
	y *= width;
	i = 0;
	while (i < width && (x + i < info->conf.req_height))
	{
		j = 0;
		while (j < width && (y + j < info->conf.req_width))
		{
			info->buf[(int)(x + i)][(int)(y + j)] = color;
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
			if (info->conf.map[i][j] == '1')
				draw_rectangle(info, j, i, 0xFFFFFF);
			else if (info->conf.map[i][j] == '0')
				draw_rectangle(info, j, i, 0x000000);
			else if (info->conf.map[i][j] == '2')
				draw_rectangle(info, j, i, 0xFFFF00);
			j++;
		}
		i++;
	}
	draw_player(info, info->posY, info->posX, 0xFF0000);
}

