#include "../includes/cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	printf(">> load_image : %s\n", path);
	img->img_ptr = mlx_xpm_file_to_image(info->mlx, path,
			&img->width, &img->height);
	if (!(img->img_ptr))
		error_exit("Error: texture loading failed");
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_l, &img->endian);
	if (!(img->data))
		error_exit("Error: texture loading failed");
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img_ptr);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[T_NO], info->conf.tex_path[T_NO], &img);
	load_image(info, info->texture[T_SO], info->conf.tex_path[T_SO], &img);
	load_image(info, info->texture[T_WE], info->conf.tex_path[T_WE], &img);
	load_image(info, info->texture[T_EA], info->conf.tex_path[T_EA], &img);
	load_image(info, info->texture[T_SPRITE], info->conf.tex_path[T_SPRITE], &img);
}