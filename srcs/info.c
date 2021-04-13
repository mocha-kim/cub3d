#include "../includes/cub3d.h"

void	ptr_init(t_info *info)
{
	info->buf = 0;
	info->texture = 0;
	info->zBuffer = 0;
	info->img.img_ptr = 0;
	info->img.data = 0;
	info->mlx = 0;
	info->win = 0;
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

int		buf_init(t_info *info)
{
	int i;
	int j;

	info->buf = (int**)malloc(sizeof(int*) * info->conf.req_height);
	if (!(info->buf))
		return (-1);
	i = 0;
	while (i < info->conf.req_height)
	{
		info->buf[i] = (int*)malloc((sizeof(int) * info->conf.req_width));
		if (!(info->buf[i]))
		{
			buf_free(info, i);
			return (-1);
		}
		j = 0;
		while (j < info->conf.req_width)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	key_init(t_info *info)
{
	info->key.a = 0;
	info->key.w = 0;
	info->key.s = 0;
	info->key.d = 0;
}

int		info_init(t_info *info)
{
	info->posX = info->conf.pos_x;
	info->posY = info->conf.pos_y;
	dir_init(info);
	info->planeX = 0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	key_init(info);
	if (buf_init(info) == -1 || tex_init(info) == -1)
		return (-1);
	info->zBuffer = (double*)malloc(sizeof(double) * info->conf.req_width);
	return (0);
}