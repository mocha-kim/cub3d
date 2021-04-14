#include "../includes/cub3d.h"

int		malloc_sprite(t_info *info)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (i < info->conf.map_col)
	{
		j = 0;
		while (j < info->conf.map_row)
		{
			if (info->conf.map[j][i] == '2')
				num++;
			j++;
		}
		i++;
	}
	info->sprite = (t_sprite *)malloc(sizeof(t_sprite) * num);
	if (!info->sprite)
		return (-1);
	return (num);
}

int		sprite_init(t_info *info)
{
	int	i;
	int	j;
	int	k;
	int	num;

	if ((num = malloc_sprite(info)) == -1)
		return (-1);
	i = 0;
	k = 0;
	while (i < info->conf.map_col)
	{
		j = 0;
		while (j < info->conf.map_row)
		{
			if (info->conf.map[j][i] == '2')
			{
				info->sprite[k].x = j;
				info->sprite[k].y = i;
				info->sprite[k].texture = T_SPRITE;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	sort_order(t_pair *sprites, int amount)
{
	int		i;
	int		j;
	t_pair	tmp;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (sprites[j].dist > sprites[j + 1].dist)
			{
				tmp.dist = sprites[j].dist;
				tmp.order = sprites[j].order;
				sprites[j].dist = sprites[j + 1].dist;
				sprites[j].order = sprites[j + 1].order;
				sprites[j + 1].dist = tmp.dist;
				sprites[j + 1].order = tmp.order;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	t_pair	*sprites;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].dist = dist[i];
		sprites[i].order = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].dist;
		order[i] = sprites[amount - i - 1].order;
		i++;
	}
	free(sprites);
}

void	calc_sprite(t_info *info)
{
	int			i;
	int			sprite_order[TEXTURES - 4];
	double		sprite_dist[TEXTURES - 4];
	t_sprt_line	sprite;

	i = 0;
	while (i < TEXTURES - 6)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((info->posX - info->sprite[i].x)
					* (info->posX - info->sprite[i].x)
					+ (info->posY - info->sprite[i].y)
					* (info->posY - info->sprite[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, TEXTURES - 4);
	i = 0;
	while (i < TEXTURES - 6)
	{
		calc_sprite_pos(&sprite, sprite_order, info, i);
		calc_sprite_line(&sprite, info);
		coord_sprite_tex(info, sprite_order, &sprite, i);
		i++;
	}
}