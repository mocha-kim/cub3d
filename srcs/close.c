#include "../includes/cub3d.h"

void	tex_free(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->texture[i]);
		i--;
	}
	free(info->texture);
}

int		error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(-1);
	return (-1);
}

void	clear_game(t_info *info)
{
	clear_config(&info->conf);
}