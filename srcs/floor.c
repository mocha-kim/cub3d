#include "../includes/cub3d.h"

void    calc_floor(t_line *line, t_vector *vec)
{
    if (vec->side == EW && vec->rayDirX > 0)
    {
        line->floorXWall = vec->mapX;
        line->floorYWall = vec->mapY + line->wallX;
    }
    else if (vec->side == EW && vec->rayDirX < 0)
    {
        line->floorXWall = vec->mapX + 1.0;
        line->floorYWall = vec->mapY + line->wallX;
    }
    else if (vec->side == NS && vec->rayDirY > 0)
    {
        line->floorXWall = vec->mapX + line->wallX;
        line->floorYWall = vec->mapY;
    }
    else
    {
        line->floorXWall = vec->mapX + line->wallX;
        line->floorYWall = vec->mapY + 1.0;
    }
}

int     calc_pattern(double weight, t_line *line, t_info *info)
{
    double  currentFloorX;
    double  currentFloorY;
    int     checkerBoardPattern;

    currentFloorX = weight * line->floorXWall + (1.0 - weight) * info->posX;
    currentFloorY = weight * line->floorYWall + (1.0 - weight) * info->posY;
    line->floorTexX = (int)(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
    line->floorTexY = (int)(currentFloorY * TEX_HEIGHT) % TEX_HEIGHT;
    checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
    return (checkerBoardPattern);
}

void    coord_floor_texture(int x, t_line *line, t_vector *vec, t_info *info)
{
    double  weight;
    int     y;
    int     checkerBoardPattern;
    int     floorTexture;

    if (line->drawEnd < 0)
        line->drawEnd = WIN_HEIGHT;
    y = line->drawEnd + 1;
    while (y < WIN_HEIGHT)
    {
        weight = (WIN_HEIGHT / (2.0 * y - WIN_HEIGHT)) / vec->perpWallDist;
        checkerBoardPattern = calc_pattern(weight, line, info);
        if (checkerBoardPattern == 0)
            floorTexture = 3;
        else
            floorTexture = 4;
        info->buf[y][x] = (info->texture[floorTexture][TEX_WIDTH * line->floorTexY + line->floorTexX] >> 1) & 8355711;
        info->buf[WIN_HEIGHT - y][x] = info->texture[6][TEX_WIDTH * line->floorTexY + line->floorTexX];
        y++;
    }
}