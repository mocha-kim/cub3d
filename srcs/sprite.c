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

void	calc_sprite_vars(t_sprite_line *sprite, int *order, t_info *info, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = info->sprite[order[i]].x - info->posX;
	sprite_y = info->sprite[order[i]].y - info->posY;
	inv_det = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
	sprite->transformX = inv_det * (info->dirY * sprite_x - info->dirX * sprite_y);
	sprite->transformY = inv_det * (-info->planeY * sprite_x + info->planeX * sprite_y);
	sprite->spriteScreenX = (int)((WIN_WIDTH / 2)
			* (1 + sprite->transformX / sprite->transformY));
	sprite->vMoveScreen = (int)(V_MOVE / sprite->transformY);
	sprite->spriteHeight = (int)fabs((WIN_HEIGHT / sprite->transformY) / V_DIV);
	sprite->drawStartY = -sprite->spriteHeight / 2 + WIN_HEIGHT
		/ 2 + sprite->vMoveScreen;
	if (sprite->drawStartY < 0)
		sprite->drawStartY = 0;
	sprite->drawEndY = sprite->spriteHeight / 2 + WIN_HEIGHT
		/ 2 + sprite->vMoveScreen;
	if (sprite->drawEndY >= WIN_HEIGHT)
		sprite->drawEndY = WIN_HEIGHT - 1;
	sprite->spriteWidth = (int)fabs((WIN_HEIGHT / sprite->transformY) / U_DIV);
	sprite->drawStartX = -sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawStartX < 0)
		sprite->drawStartX = 0;
	sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
	if (sprite->drawEndX >= WIN_WIDTH)
		sprite->drawEndX = WIN_WIDTH - 1;
}

void	coord_sprite_texture(t_info *info, int *order, t_sprite_line *sprite, int i)
{
	int	stripe;
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;

	stripe = sprite->drawStartX;
	while (stripe < sprite->drawEndX)
	{
		tex_x = (int)((256 * (stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX))
					* TEX_WIDTH / sprite->spriteWidth) / 256);
		if (sprite->transformY > 0 && stripe > 0 && stripe < WIN_HEIGHT
				&& sprite->transformY < info->zBuffer[stripe])
		{
			y = sprite->drawStartY;
			while (y < sprite->drawEndY)
			{
				d = (y - sprite->vMoveScreen) * 256 - WIN_HEIGHT * 128 + sprite->spriteHeight * 128;
				tex_y = ((d * TEX_HEIGHT) / sprite->spriteHeight) / 256;
				sprite->color = info->texture[info->sprite[order[i]].texture][TEX_WIDTH * tex_y + tex_x];
				if ((sprite->color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = sprite->color;
				y++;
			}
		}
		stripe++;
	}
}

void	calc_sprite(t_info *info)
{
	int				i;
	int				sprite_order[NUM_SPRITES];
	double			sprite_dist[NUM_SPRITES];
	t_sprite_line	sprite;

	i = 0;
	while (i < NUM_SPRITES)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((info->posX - info->sprite[i].x) * (info->posX - info->sprite[i].x) + (info->posY - info->sprite[i].y) * (info->posY - info->sprite[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, NUM_SPRITES);
	i = 0;
	while (i < NUM_SPRITES)
	{
		calc_sprite_vars(&sprite, sprite_order, info, i);
		coord_sprite_texture(info, sprite_order, &sprite, i);
		i++;
	}
}
