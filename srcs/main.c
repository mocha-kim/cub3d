#include "../includes/cub3d.h"

int		main_loop(t_info *info)
{
	calc_back(info);
	calc_sprite(info);
	draw(info);
	key_update(info);
	return (0);
}

int		main_close(t_info *info)
{
	printf("> exit game\n");
	clear_game(info);
	exit(0);
}

void	draw(t_info *info)
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

int		main(int argc, char **argv)
{
	t_info		info;
	int			has_save_opt;
	
	has_save_opt = (argc >= 2 && (!ft_strcmp(argv[1], "--save")));
	if (argc < 2 || (has_save_opt && argc < 3))
		return (error_exit("Error: no map argument.\n"));
	if (!parse_config(&(info.conf), argv[1]))
		return (error_exit("Error: Invalid map.\n"));
	printf("========== game init start ==========\n");
	info_init(&info);
	key_init(&info);
	if (window_init(&info) == -1 || tex_init(&info) == -1)
		return (error_exit("Error: memory allocation failed."));
	load_texture(&info);
	info.img.img_ptr = mlx_new_image(info.mlx, WIN_WIDTH, WIN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp,
			&info.img.size_l, &info.img.endian);
	// if (has_save_opt)
	// 	return (save_image(&info));
	printf("========== game init complete ==========\n");
	printf("info : pos(%.2f, %.2f), dir(%.2f, %.2f), config map[%d][%d]\n", 
				info.posX, info.posY,info.dirX, info.dirY, info.conf.map_row, info.conf.map_col);
	for (int i = 0; i < info.conf.map_row; i++)
	{
		for (int j = 0; j < info.conf.map_col; j++)
			printf("%d ", info.conf.map[i][j]);
		printf("\n");
	}
	printf("> game start...\n");
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, EVENT_KEY_EXIT, 0, &main_close, &info);
	if (!has_save_opt)
		mlx_loop(info.mlx);
}