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
	if (info)
	{
		clear_config(&info->conf);
		if (info->buf)
			buf_free(info, info->conf.req_height - 1);
		if (info->texture)
			tex_free(info, TEXTURES - 1);
		if (info->zBuffer)
			free(info->zBuffer);
		if (info->sprite)
			free(info->sprite);
		clear_window(info);
	}
}