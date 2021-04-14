#include "../includes/cub3d.h"

static int	write_bmp_data(int fd, t_info *info)
{
	// const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = -1;
	while (++i < info->conf.req_width)
	{
		j = -1;
		while (++j < info->conf.req_height)
		{
			color = info->buf[j][i];
			if ((write(fd, &color, 3) < 0))
				return (0);
			// if (write(fd, zero, 3))
		}
	}
	return (1);
}

int			save_image(t_info *info)
{
	int		file;
	int		filesize;

	calc_back(info);
	calc_sprite(info);
	draw(info);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		return (0);
	filesize = 54 + (info->conf.req_width * info->conf.req_width);
	if (!(write_bmp_header(file, filesize, info)))
		return (0);
	if (!write_bmp_data(file, info))
		return (0);
	return (1);
}

static void	set_int_in_char(unsigned char *arr, int val)
{
	arr[0] = (unsigned char)val;
	arr[1] = (unsigned char)(val >> 8);
	arr[2] = (unsigned char)(val >> 16);
	arr[3] = (unsigned char)(val >> 24);
}

int			write_bmp_header(int fd, int filesize, t_info *info)
{
	int				i;
	unsigned char	file_header[54];

	i = -1;
	while (++i < 54)
		file_header[i] = (unsigned char)(0);
	file_header[0] = (unsigned char)'B';
	file_header[1] = (unsigned char)'M';
	set_int_in_char(file_header + 2, filesize);
	file_header[10] = (unsigned char)(54);
	file_header[14] = (unsigned char)(40);
	i = info->conf.req_width;
	set_int_in_char(file_header + 18, i);
	i = info->conf.req_height;
	set_int_in_char(file_header + 22, i);
	file_header[27] = (unsigned char)1;
	file_header[29] = (unsigned char)24;
	return (!(write(fd, file_header, 54) < 0));
}