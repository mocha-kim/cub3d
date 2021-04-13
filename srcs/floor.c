#include "../includes/cub3d.h"

void	calc_floor(t_back_line *line, t_vector *vec)
{
	if (vec->side == X_PLANE && vec->rayDirX > 0)
	{
		line->floorXWall = vec->mapX;
		line->floorYWall = vec->mapY + line->wallX;
	}
	else if (vec->side == X_PLANE && vec->rayDirX < 0)
	{
		line->floorXWall = vec->mapX + 1.0;
		line->floorYWall = vec->mapY + line->wallX;
	}
	else if (vec->side == Y_PLANE && vec->rayDirY > 0)
	{
		line->floorXWall = vec->mapX + line->wallX;
		line->floorYWall = vec->mapY;
	}
	else
	{
		line->floorXWall = vec->mapX + line->wallX;
		line->floorYWall = vec->mapY + 1.0;
	}
}

void	coord_floor_tex(int x, t_back_line *line, t_vector *vec, t_info *info)
{
	double	weight;
	int		y;
	int		floor_tex;
	int		tex_tmp;

	if (line->drawEnd < 0)
		line->drawEnd = info->conf.req_height;
	y = line->drawEnd + 1;
	while (y < info->conf.req_height)
	{
		weight = (info->conf.req_height / (2.0 * y - info->conf.req_height)) / vec->perpWallDist;
		floor_tex = T_FLOOR;
		tex_tmp = TEX_WIDTH * line->floorTexY + line->floorTexX;
		info->buf[y][x] = (info->texture[floor_tex][tex_tmp] >> 1) & 8355711;
		info->buf[info->conf.req_height - y][x] = info->texture[6][tex_tmp];
		y++;
	}
}

void	coord_floor_color(int x, t_back_line *line, t_info *info)
{
	int		y;

	if (line->drawEnd < 0)
		line->drawEnd = info->conf.req_height;
	y = line->drawEnd + 1;
	while (y < info->conf.req_height)
	{
		info->buf[y][x] = info->conf.cf_color[1];
		info->buf[info->conf.req_height - y][x] = info->conf.cf_color[0];
		y++;
	}
}