#include "../includes/cub3d.h"

int		save_image(t_info *info)
{
	calc_back(info);
	calc_sprite(info);
	draw(info);
	return (1);
}