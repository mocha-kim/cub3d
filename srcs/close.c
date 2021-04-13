#include "../includes/cub3d.h"

int		error_exit(t_info *info, char *message)
{
	write(2, message, ft_strlen(message));
	clear_game(info);
	exit(-1);
	return (-1);
}

void	buf_free(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->buf[i]);
		i--;
	}
	free(info->buf);
}

void	clear_game(t_info *info)
{
	if (info && clear_config(&info->conf))
	{
		printf("clear_config\n");
		if (info->buf)
			buf_free(info, info->conf.req_height - 1);
		printf("buf_free\n");
		if (info->texture)
			tex_free(info, TEXTURES - 1);
		printf("tex_free\n");
		if (info->zBuffer)
			free(info->zBuffer);
		printf("free\n");
		clear_window(info);
		printf("clear_window\n");
	}
}