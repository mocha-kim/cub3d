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

int		calc_pattern(double weight, t_back_line *line, t_info *info)
{
	double	curr_floor_x;
	double	curr_floor_y;
	int		check_pattern;

	curr_floor_x = weight * line->floorXWall + (1.0 - weight) * info->posX;
	curr_floor_y = weight * line->floorYWall + (1.0 - weight) * info->posY;
	line->floorTexX = (int)(curr_floor_x * TEX_WIDTH) % TEX_WIDTH;
	line->floorTexY = (int)(curr_floor_y * TEX_HEIGHT) % TEX_HEIGHT;
	check_pattern = ((int)(curr_floor_x) + (int)(curr_floor_y)) % 2;
	return (check_pattern);
}

void	coord_floor_texture(int x, t_back_line *line, t_vector *vec, t_info *info)
{
	double	weight;
	int		y;
	int		check_pattern;
	int		floor_tex;
	int		tex_tmp;

	if (line->drawEnd < 0)
		line->drawEnd = info->conf.req_height;
	y = line->drawEnd + 1;
	while (y < info->conf.req_height)
	{
		weight = (info->conf.req_height / (2.0 * y - info->conf.req_height)) / vec->perpWallDist;
		check_pattern = calc_pattern(weight, line, info);
		if (check_pattern == 0)
			floor_tex = 3;
		else
			floor_tex = 4;
		tex_tmp = TEX_WIDTH * line->floorTexY + line->floorTexX;
		info->buf[y][x] = (info->texture[floor_tex][tex_tmp] >> 1) & 8355711;
		info->buf[info->conf.req_height - y][x] = info->texture[6][tex_tmp];
		y++;
	}
}
