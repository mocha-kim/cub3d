/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:20:43 by sunhkim           #+#    #+#             */
/*   Updated: 2021/04/01 15:20:47 by sunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    calc_vars(int x, t_vector *vec, t_info *info)
{
    double      cameraX;

    cameraX = 2 * x / (double)WIN_WIDTH - 1;
    vec->rayDirX = info->dirX + info->planeX * cameraX;
    vec->rayDirY = info->dirY + info->planeY * cameraX;
    vec->mapX = (int)info->posX;
    vec->mapY = (int)info->posY;
    vec->deltaDistX = fabs(1 / vec->rayDirX);
    vec->deltaDistY = fabs(1 / vec->rayDirY);
}

void    calc_dists(t_vector *vec, t_info *info)
{
    if (vec->rayDirX < 0)
    {
        vec->stepX = -1;
        vec->sideDistX = (info->posX - vec->mapX) * vec->deltaDistX;
    }
    else
    {
        vec->stepX = 1;
        vec->sideDistX = (vec->mapX + 1.0 - info->posX) * vec->deltaDistX;
    }
    if (vec->rayDirY < 0)
    {
        vec->stepY = -1;
        vec->sideDistY = (info->posY - vec->mapY) * vec->deltaDistY;
    }
    else
    {
        vec->stepY = 1;
        vec->sideDistY = (vec->mapY + 1.0 - info->posY) * vec->deltaDistY;
    }
}

void    ray_cast(t_vector *vec, t_info *info)
{
    int         hit;

    hit = 0;
    while (hit == 0)
    {
        if (vec->sideDistX < vec->sideDistY)
        {
            vec->sideDistX += vec->deltaDistX;
            vec->mapX += vec->stepX;
            vec->side = EW;
        }
        else
        {
            vec->sideDistY += vec->deltaDistY;
            vec->mapY += vec->stepY;
            vec->side = NS;
        }
        if (info->map[vec->mapX][vec->mapY] > 0)
            hit = 1;
    }
}

void	calc_back(t_info *info)
{
    t_vector    vec;
    t_line      line;
    int         x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        /*
        ** casting wall
        */
        // printf("> casting wall\n");
        calc_vars(x, &vec, info);
        // printf(">> calc_vars\n");
        calc_dists(&vec, info);
        // printf(">> calc_dists\n");
        ray_cast(&vec, info);
        // printf(">> ray_cast\n");
        calc_line(&line, &vec, info);
        // printf(">> calc_line\n");
		calc_wall(&line, &vec, info);
        // printf(">> calc_wall\n");
		coord_wall_texture(x, &line, &vec, info);
        // printf(">> coord_wall_texture\n");
        /*
        ** casting floor & celing
        */
        // printf("> casting floor & celing\n");
        calc_floor(&line, &vec);
        // printf(">> calc_floor\n");
        coord_floor_texture(x, &line, &vec, info);
        // printf(">> coord_floor_texture\n");
		info->zBuffer[x] = vec.perpWallDist;
        x++;
    }
}
