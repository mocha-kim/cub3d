#include "../includes/cub3d.h"

void    calc_line(t_line *line, t_vector *vec, t_info *info)
{
    if (vec->side == EW)
    {
        vec->perpWallDist = (vec->mapX - info->posX + (1 - vec->stepX) / 2);
        vec->perpWallDist /= vec->rayDirX;
    }
    else
    {
        vec->perpWallDist = (vec->mapY - info->posY + (1 - vec->stepY) / 2);
        vec->perpWallDist /= vec->rayDirY;
    }
    line->lineHeight = (int)(WIN_HEIGHT / vec->perpWallDist);
    line->drawStart = -(line->lineHeight) / 2 + WIN_HEIGHT / 2;
    if (line->drawStart < 0)
        line->drawStart = 0;
    line->drawEnd = line->lineHeight / 2 + WIN_HEIGHT / 2;
    if (line->drawEnd >= WIN_HEIGHT)
        line->drawEnd = WIN_HEIGHT - 1;
}

void    calc_wall(t_line *line, t_vector *vec, t_info *info)
{
    line->texNum = info->map[vec->mapX][vec->mapY] - 1;
    if (vec->side == 0)
        line->wallX = info->posY + vec->perpWallDist * vec->rayDirY;
    else
        line->wallX = info->posX + vec->perpWallDist * vec->rayDirX;
    line->wallX -= floor(line->wallX);
    line->texX = (int)(line->wallX * (double)TEX_WIDTH);
    if (vec->side == 0 && vec->rayDirX > 0)
        line->texX = TEX_WIDTH - line->texX - 1;
    if (vec->side == 1 && vec->rayDirY < 0)
        line->texX = TEX_WIDTH - line->texX - 1;
}

void    coord_wall_texture(int x, t_line *line, t_vector *vec, t_info *info)
{
    double  step;
    double  texPos;
    int     y;

    step = 1.0 * TEX_HEIGHT / line->lineHeight;
    texPos = (line->drawStart - WIN_HEIGHT / 2 + line->lineHeight / 2) * step;
    y = line->drawStart;
    while (y < line->drawEnd)
    {
        line->texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        line->color = info->texture[line->texNum][TEX_WIDTH * line->texY + line->texX];
        if (vec->side == NS)
            line->color = (line->color >> 1) & 8355711;
        info->buf[y][x] = line->color;
        y++;
    }
}