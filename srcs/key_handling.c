/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:15:20 by sunhkim           #+#    #+#             */
/*   Updated: 2021/04/01 15:15:22 by sunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    move(t_info *info, int direction)
{
    int tmpX;
    int tmpY;

    tmpX = info->posX + direction * info->dirX * info->moveSpeed;
    tmpY = info->posY + direction * info->dirY * info->moveSpeed;
    if (direction == 1)
    {
        if (!info->map[tmpX][tmpY])
        {
            info->posX += info->dirX * info->moveSpeed;
            info->posY += info->dirY * info->moveSpeed;
        }
    }
    if (direction == -1)
    {
        if (!info->map[tmpX][tmpY])
        {
            info->posX -= info->dirX * info->moveSpeed;
            info->posY -= info->dirY * info->moveSpeed;
        }
    }
}

void    rotate(t_info *info, int direction)
{
    double  oldDirX;
    double  oldPlnX;
    double  tmpX;
    double  tmpY;

    oldDirX = info->dirX;
    tmpX = info->dirX * cos(direction * info->rotSpeed);
    tmpY = info->dirY * sin(direction * info->rotSpeed);
    info->dirX = tmpX - tmpY;
    tmpX = oldDirX * sin(direction * info->rotSpeed);
    tmpY = info->dirY * cos(direction * info->rotSpeed);
    info->dirY = tmpX + tmpY;
    oldPlnX = info->planeX;
    tmpX = info->planeX * cos(direction * info->rotSpeed);
    tmpY = info->planeY * sin(direction * info->rotSpeed);
    info->planeX = tmpX - tmpY;
    tmpX = oldPlnX * sin(direction * info->rotSpeed);
    tmpY = info->planeY * cos(direction * info->rotSpeed);
    info->planeY = tmpX + tmpY;
}

int     key_update(t_info *info)
{
    if (info->key.esc)
        exit(0);
    if (info->key.w)
        move(info, 1);
    if (info->key.s)
        move(info, -1);
    if (info->key.d)
        rotate(info, -1);
    if (info->key.a)
        rotate(info, 1);
    return (0);
}

int     key_press(int key, t_info *info)
{
    if (key == KEY_W || key == KEY_UP)
        info->key.w = 1;
    if (key == KEY_S || key == KEY_DOWN)
        info->key.a = 1;
    if (key == KEY_A || key == KEY_LEFT)
        info->key.s = 1;
    if (key == KEY_D || key == KEY_RIGHT)
        info->key.d = 1;
    if (key == KEY_ESC)
        exit(0);
    return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == KEY_UP)
		info->key.w = 0;
	else if (key == KEY_A || key == KEY_DOWN)
		info->key.a = 0;
	else if (key == KEY_S || key == KEY_LEFT)
		info->key.s = 0;
	else if (key == KEY_D || key == KEY_RIGHT)
		info->key.d = 0;
	return (0);
}