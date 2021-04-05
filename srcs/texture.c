/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:21:31 by sunhkim           #+#    #+#             */
/*   Updated: 2021/04/02 16:21:33 by sunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
    printf(">> load_image : %s\n", path);
	img->img_ptr = mlx_xpm_file_to_image(info->mlx, path, &img->width, &img->height);
    if (!(img->img_ptr))
        error_exit("image loading failed");
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
    if (!(img->data))
        error_exit("image loading failed");
    for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img_ptr);\
}

void    load_texture(t_info *info)
{
    t_img   img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
	load_image(info, info->texture[8], "textures/barrel.xpm", &img);
	load_image(info, info->texture[9], "textures/pillar.xpm", &img);
	load_image(info, info->texture[10], "textures/greenlight.xpm", &img);
}
