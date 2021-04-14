#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

# define TILE_SIZE 8

/*
** ui.c
*/

void	calc_ui(t_info *info);

/*
** minimap.c
*/

void	draw_rectangle(t_info *info, int x, int y, int color);
void	draw_rectangles(t_info *info);

# endif