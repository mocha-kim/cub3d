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

// void	calc_sprite_vars(t_sprite_line *sprite, int *order, t_info *info, int i)
// {
// 	double	sprite_x;
// 	double	sprite_y;
// 	double	inv_det;

// 	sprite_x = info->sprite[order[i]].x - info->posX;
// 	sprite_y = info->sprite[order[i]].y - info->posY;
// 	sprite->spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + sprite->transformX / sprite->transformY));
// 	sprite->vMoveScreen = (int)(V_MOVE / sprite->transformY);
// 	sprite->spriteHeight = (int)fabs((WIN_HEIGHT / sprite->transformY) / V_DIV);
// 	sprite->drawStartY = -sprite->spriteHeight / 2 + WIN_HEIGHT / 2 + sprite->vMoveScreen;
// 	if (sprite->drawStartY < 0)
// 		sprite->drawStartY = 0;
// 	sprite->drawEndY = sprite->spriteHeight / 2 + WIN_HEIGHT / 2 + sprite->vMoveScreen;
// 	if (sprite->drawEndY >= WIN_HEIGHT)
// 		sprite->drawEndY = WIN_HEIGHT - 1;
// 	sprite->spriteWidth = (int)fabs((WIN_HEIGHT / sprite->transformY) / U_DIV);
// 	sprite->drawStartX = -sprite->spriteWidth / 2 + sprite->spriteScreenX;
// 	if (sprite->drawStartX < 0)
// 		sprite->drawStartX = 0;
// 	sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
// 	if (sprite->drawEndX >= WIN_WIDTH)
// 		sprite->drawEndX = WIN_WIDTH - 1;
// }

// void	coord_sprite_texture(t_info *info, int *order, t_sprite_line *sprite, int i)
// {
// 	int	stripe;
// 	int	tex_x;
// 	int	tex_y;
// 	int	y;
// 	int	d;

// 	stripe = sprite->drawStartX;
// 	while (stripe < sprite->drawEndX)
// 	{
// 		tex_x = (int)((256 * (stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX)) * TEX_WIDTH / sprite->spriteWidth) / 256);
// 		if (sprite->transformY > 0 && stripe > 0 && stripe < WIN_HEIGHT && sprite->transformY < info->zBuffer[stripe])
// 		{
// 			y = sprite->drawStartY;
// 			while (y < sprite->drawEndY)
// 			{
// 				d = (y - sprite->vMoveScreen) * 256 - WIN_HEIGHT * 128 + sprite->spriteHeight * 128;
// 				tex_y = ((d * TEX_HEIGHT) / sprite->spriteHeight) / 256;
// 				sprite->color = info->texture[info->sprite[order[i]].texture][TEX_WIDTH * tex_y + tex_x];
// 				if ((sprite->color & 0x00FFFFFF) != 0)
// 					info->buf[y][stripe] = sprite->color;
// 				y++;
// 			}
// 		}
// 		stripe++;
// 	}
// }

// void	calc_sprite(t_info *info)
// {
// 	int				i;
// 	int				sprite_order[NUM_SPRITES];
// 	double			sprite_dist[NUM_SPRITES];
// 	t_sprite_line	sprite;

// 	i = 0;
// 	while (i < NUM_SPRITES)
// 	{
// 		sprite_order[i] = i;
// 		sprite_dist[i] = ((info->posX - info->sprite[i].x) * (info->posX - info->sprite[i].x) + (info->posY - info->sprite[i].y) * (info->posY - info->sprite[i].y));
// 		i++;
// 	}
// 	sort_sprites(sprite_order, sprite_dist, NUM_SPRITES);
// 	i = 0;
// 	while (i < NUM_SPRITES)
// 	{
// 		calc_sprite_vars(&sprite, sprite_order, info, i);
// 		coord_sprite_texture(info, sprite_order, &sprite, i);
// 		i++;
// 	}
// }

void calc_sprite(t_info *game)
{
	int		spriteOrder[NUM_SPRITES];
	double	spriteDistance[NUM_SPRITES];

	for (int i = 0;i < NUM_SPRITES;i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((game->posX - game->sprite[i].x) * (game->posX - game->sprite[i].x) + (game->posY - game->sprite[i].y) * (game->posY - game->sprite[i].y));
	}
	sort_sprites(spriteOrder, spriteDistance, NUM_SPRITES);
	for (int i = 0;i < NUM_SPRITES;i++)
	{
		// translate sprite position to relative to camera
		double spriteX = game->sprite[spriteOrder[i]].x - game->posX;
		double spriteY = game->sprite[spriteOrder[i]].y - game->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);

		double transformX = invDet * (game->dirY * spriteX - game->dirX * spriteY);
		double transformY = invDet * (-game->planeY * spriteX + game->planeX * spriteY);

		int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));

		// sprite 크기 조절 변수 가로 / 세로
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		// 스크린 위의 물체의 높이 계산
		int spriteHeight = (int)fabs((WIN_HEIGHT / transformY) / vDiv); // 실제 거리 대신에 transformY 를 사용해서 어안렌즈 효과 방지
		// 현재 줄의 아래 위 위치 계산
		int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
		if (drawEndY >= WIN_HEIGHT)
			drawEndY = WIN_HEIGHT - 1;

		// calculate width of the sprite
		int spriteWidth = (int)fabs((WIN_HEIGHT / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= WIN_WIDTH)
			drawEndX = WIN_WIDTH - 1;

		// loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX;stripe < drawEndX;stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
			if (transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < game->zBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY;y++)
				{
					int d = (y - vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128;
					int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
					int color = game->texture[game->sprite[spriteOrder[i]].texture][TEX_WIDTH * texY + texX];
					if ((color & 0x00FFFFFF) != 0) game->buf[y][stripe] = color;
				}
			}
		}
	}
}