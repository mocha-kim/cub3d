#include "../includes/cub3d.h"

int		window_init(t_info *info)
{
	info->mlx = mlx_init();
	if (!(info->mlx))
		return (-1);
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!(info->win))
		return (-1);
	return (0);
}

void	dir_init(t_info *info)
{
	if (info->conf.dir == 'N')
	{
		info->dirX = 0;
		info->dirY = 1;
	}
	else if (info->conf.dir == 'S')
	{
		info->dirX = 0;
		info->dirY = -1;
	}
	else if (info->conf.dir == 'W')
	{
		info->dirX = -1;
		info->dirY = 0;
	}
	else
	{
		info->dirX = 1;
		info->dirY = 0;
	}
}

void	info_init(t_info *info)
{
	int i;
	int j;

	info->posX = info->conf.pos_x;
	info->posY = info->conf.pos_y;
	dir_init(info);
	info->planeX = 0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	key_init(t_info *info)
{
	info->key.a = 0;
	info->key.w = 0;
	info->key.s = 0;
	info->key.d = 0;
}

int		tex_init(t_info *info)
{
	int i;
	int j;

	info->texture = (int **)malloc(sizeof(int *) * TEXTURES);
	if (!(info->texture))
		return (-1);
	i = 0;
	while (i < TEXTURES)
	{
		info->texture[i] = (int *)malloc(sizeof(int) *
				(TEX_HEIGHT * TEX_WIDTH));
		if (!(info->texture[i]))
		{
			tex_free(info, i);
			return (-1);
		}
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}