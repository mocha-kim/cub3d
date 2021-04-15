#include "utils.h"
#include <stdio.h>

int		is_space(char ch)
{
	if (ch == '\n' || ch == '\v' || ch == '\f'
			|| ch == '\r' || ch == '\t' || ch == ' ')
		return (1);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_swap(int *n1, int *n2)
{
	int	tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

void	screen_size(void *mlx, int *height, int *width)
{
	int 	sizex;
	int		sizey;

	mlx_get_screen_size(mlx, &sizex, &sizey);
	printf("sizex: %d\nsizey: %d\n", sizex, sizey);
	printf("screen x: %d, y: %d\n", *width, *height);
}