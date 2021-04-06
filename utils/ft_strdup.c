#include "utils.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(s1);
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (0);
	i = 0;
	while (i < size)
		str[i++] = *s1++;
	str[i] = 0;
	return (str);
}
