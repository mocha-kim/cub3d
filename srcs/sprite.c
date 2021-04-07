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
		}
		
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
	double	spriteX;
	double	spriteY;
	double	invDet;

	spriteX = info->sprite[order[i]].x - info->posX;
	spriteY = info->sprite[order[i]].y - info->posY;
	invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
	sprite->transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
	sprite->transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY);
	sprite->spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + sprite->transformX / sprite->transformY));
	sprite->vMoveScreen = (int)(V_MOVE / sprite->transformY);
	sprite->spriteHeight = (int)fabs((WIN_HEIGHT / sprite->transformY) / V_DIV);
	sprite->drawStartY = -sprite->spriteHeight / 2 + WIN_HEIGHT / 2 + sprite->vMoveScreen;
	if (sprite->drawStartY < 0)
		sprite->drawStartY = 0;
	sprite->drawEndY = sprite->spriteHeight / 2 + WIN_HEIGHT / 2 + sprite->vMoveScreen;
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
	for (int stripe = sprite->drawStartX; stripe < sprite->drawEndX; stripe++)
	{
		int texX = (int)((256 * (stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX)) * texWidth / spriteWidth) / 256);
		if (sprite->transformY > 0 && stripe > 0 && stripe < WIN_HEIGHT && sprite->transformY < game->zBuffer[stripe])
		{
			for (int y = sprite->drawStartY; y < sprite->drawEndY;y++)
			{
				int d = (y - sprite->vMoveScreen) * 256 - WIN_HEIGHT * 128 + sprite->spriteHeight * 128;
				int texY = ((d * TEX_HEIGHT) / sprite->spriteHeight) / 256;
				int color = game->texture[sprite[order[i]].texture][texWidth * texY + texX];
				if ((color & 0x00FFFFFF) != 0) game->buf[y][stripe] = color;
			}
		}
	}
}

void	calc_sprite(t_info *info)
{
	int				i;
	int				stripe;
	int				sprite_order[NUM_SPRITES];
	double			sprite_dist[NUM_SPRITES];
	t_sprite_line	sprite;

	i = 0;
	while (i < NUM_SPRITES)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((info->posX - info->sprite[i].x) * (info->posX - info->sprite[i].x) + (info->posY - info->sprite[i].y)* (info->posY - info->sprite[i].y));
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