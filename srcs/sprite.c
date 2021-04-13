#include "../includes/cub3d.h"

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

void	calc_sprite_vars(t_sprt_line *sprt, int *order, t_info *info, int i)
{
	double	inv_det;

	sprt->x = info->sprite[order[i]].x - info->posX;
	sprt->y = info->sprite[order[i]].y - info->posY;
	inv_det = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
	sprt->transX = inv_det * (info->dirY * sprt->x - info->dirX * sprt->y);
	sprt->transY = inv_det * (-info->planeY * sprt->x + info->planeX * sprt->y);
	sprt->screenX = (int)((info->conf.req_width / 2)
				* (1 + sprt->transX / sprt->transY));
	sprt->vMoveScreen = (int)(V_MOVE / sprt->transY);
	sprt->height = (int)fabs((info->conf.req_height / sprt->transY) / V_DIV);
	sprt->drawStartY = -sprt->height / 2 + info->conf.req_height / 2 + sprt->vMoveScreen;
	if (sprt->drawStartY < 0)
		sprt->drawStartY = 0;
	sprt->drawEndY = sprt->height / 2 + info->conf.req_height / 2 + sprt->vMoveScreen;
	if (sprt->drawEndY >= info->conf.req_height)
		sprt->drawEndY = info->conf.req_height - 1;
	sprt->width = (int)fabs((info->conf.req_height / sprt->transY) / U_DIV);
	sprt->drawStartX = -sprt->width / 2 + sprt->screenX;
	if (sprt->drawStartX < 0)
		sprt->drawStartX = 0;
	sprt->drawEndX = sprt->width / 2 + sprt->screenX;
	if (sprt->drawEndX >= info->conf.req_width)
		sprt->drawEndX = info->conf.req_width - 1;
}

void	coord_sprite_tex(t_info *info, int *order, t_sprt_line *sprt, int i)
{
	int	stripe;
	int	y;
	int	d;

	stripe = sprt->drawStartX - 1;
	while (++stripe < sprt->drawEndX)
	{
		sprt->texX = (int)((256 * (stripe - (-sprt->width / 2 + sprt->screenX))
					* TEX_WIDTH / sprt->width) / 256);
		if (sprt->transY > 0 && stripe > 0 && stripe < info->conf.req_width
					&& sprt->transY < info->zBuffer[stripe])
		{
			y = sprt->drawStartY - 1;
			while (++y < sprt->drawEndY)
			{
				d = (y - sprt->vMoveScreen) * 256 - info->conf.req_height * 128
					+ sprt->height * 128;
				sprt->texY = ((d * TEX_HEIGHT) / sprt->height) / 256;
				sprt->color = info->texture[info->sprite[order[i]].texture]
							[TEX_WIDTH * sprt->texY + sprt->texX];
				if ((sprt->color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = sprt->color;
			}
		}
	}
}

void	calc_sprite(t_info *info)
{
	int			i;
	int			sprite_order[TEXTURES - 6];
	double		sprite_dist[TEXTURES - 6];
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
	sort_sprites(sprite_order, sprite_dist, TEXTURES - 6);
	i = 0;
	while (i < TEXTURES - 6)
	{
		calc_sprite_vars(&sprite, sprite_order, info, i);
		coord_sprite_tex(info, sprite_order, &sprite, i);
		i++;
	}
}
