#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

/*
** score.c
*/

void	draw_score(t_info *info);

/*
** minimap.c
*/

void	draw_rectangle(t_info *info, int x, int y, int color);
void	calc_minimap(t_info *info);

# endif