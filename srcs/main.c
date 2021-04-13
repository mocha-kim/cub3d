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
	while (y < info->conf.req_height)
	{
		x = 0;
		while (x < info->conf.req_width)
		{
			info->img.data[y * info->conf.req_width + x] = info->buf[y][x];
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
	
	ptr_init(&info);
	has_save_opt = (argc >= 2 && !ft_strcmp(argv[1], "--save"));
	if (argc < (2 + has_save_opt))
		return (error_exit(NULL, "Error\n: no map argument.\n"));
	if (!parse_config(&info.conf, argv[1]))
		return (error_exit(&info, "Error\n: Invalid map.\n"));
	if (info_init(&info) == -1 || window_init(&info) == -1)
		return (error_exit(&info, "Error\n: memory allocation failed.\n"));
	load_texture(&info);
	// if (has_save_opt)
	// 	return (save_image(&info));
	printf("info : pos(%.2f, %.2f), dir(%.2f, %.2f), config map[%d][%d]\n", 
				info.posX, info.posY,info.dirX, info.dirY, info.conf.map_row, info.conf.map_col);
	for (int i = 0; i < info.conf.map_row; i++)
	{
		for (int j = 0; j < info.conf.map_col; j++)
			printf("%d", info.conf.map[i][j]);
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