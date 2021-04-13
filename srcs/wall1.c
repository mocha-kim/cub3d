#include "../includes/cub3d.h"

void	calc_vars(int x, t_vector *vec, t_info *info)
{
	double	camera_x;

	camera_x = 2 * x / (double)info->conf.req_width - 1;
	vec->rayDirX = info->dirX + info->planeX * camera_x;
	vec->rayDirY = info->dirY + info->planeY * camera_x;
	vec->mapX = (int)info->posX;
	vec->mapY = (int)info->posY;
	vec->deltaDistX = fabs(1 / vec->rayDirX);
	vec->deltaDistY = fabs(1 / vec->rayDirY);
}

void	calc_dists(t_vector *vec, t_info *info)
{
	if (vec->rayDirX < 0)
	{
		vec->stepX = -1;
		vec->sideDistX = (info->posX - vec->mapX) * vec->deltaDistX;
	}
	else
	{
		vec->stepX = 1;
		vec->sideDistX = (vec->mapX + 1.0 - info->posX) * vec->deltaDistX;
	}
	if (vec->rayDirY < 0)
	{
		vec->stepY = -1;
		vec->sideDistY = (info->posY - vec->mapY) * vec->deltaDistY;
	}
	else
	{
		vec->stepY = 1;
		vec->sideDistY = (vec->mapY + 1.0 - info->posY) * vec->deltaDistY;
	}
}

void	ray_cast(t_vector *vec, t_info *info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vec->sideDistX < vec->sideDistY)
		{
			vec->sideDistX += vec->deltaDistX;
			vec->mapX += vec->stepX;
			vec->side = X_PLANE;
		}
		else
		{
			vec->sideDistY += vec->deltaDistY;
			vec->mapY += vec->stepY;
			vec->side = Y_PLANE;
		}
		if (info->conf.map[vec->mapX][vec->mapY] > 0)
			hit = 1;
	}
}

void	calc_back(t_info *info)
{
	t_vector	vec;
	t_back_line	line;
	int			x;

	x = 0;
	while (x < info->conf.req_width)
	{
		calc_vars(x, &vec, info);
		printf("calc_vars\n");
		calc_dists(&vec, info);
		printf("calc_dists\n");
		ray_cast(&vec, info);
		printf("ray_cast\n");
		calc_line(&line, &vec, info);
		printf(" .");
		calc_wall(&line, &vec, info);
		printf(" .");
		coord_wall_tex(x, &line, info);
		printf(" .");
		calc_floor(&line, &vec);
		printf(" .");
		coord_floor_color(x, &line, info);
		printf(" .");
		info->zBuffer[x] = vec.perpWallDist;
		x++;
	}
}
