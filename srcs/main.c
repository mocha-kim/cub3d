/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:59:46 by sunhkim           #+#    #+#             */
/*   Updated: 2021/03/27 15:59:48 by sunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		main_loop(t_info *info)
{
	calc_back(info);
	clac_sprite(info);
	draw(info);
	key_update(info);
	return (0);
}

int		main_close(t_info *info)
{
	int	x;

	printf("> exit game\n");
	x = (int)info->posX;
	exit(0);
}

void	error_exit(char *message)
{
	printf("Error:%s.", message);
	exit(-1);
}

void    draw(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			info->img.data[y * WIN_WIDTH + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img_ptr, 0, 0);
}

int		main(void)
{
	t_info	info;

	printf("========== game init start ==========\n");
    printf("> init variables\n");
	info_init(&info);
	game_init(&info);
	if (window_init(&info) == -1)
		return (-1);
    if (tex_init(&info) == -1)
        return (-1);
	printf(">> variables init complete\n");
    printf("> load texture\n");
	load_texture(&info);
	printf(">> texture loading complete\n");
    printf("> set image info\n");
	info.img.img_ptr = mlx_new_image(info.mlx, WIN_WIDTH, WIN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.size_l, &info.img.endian);
	printf(">> image info setting complete\n");
	printf("========== game init complete ==========\n");
    printf("> game start...\n");
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, EVENT_KEY_EXIT, 0, &main_close, &info);
	mlx_loop(info.mlx);
}