#include "config_bonus.h"
#include <stdio.h>

int			parse_resolution(t_config *config, char *line)
{
	int		i;

	i = 1;
	config->set[C_R] = 1;
	if (line && line[0] == 'R')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (ft_strlen(line + i) == 0)
			return (0);
		if (ft_isdigit(line[i]))
			config->win_width = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		while (line[i] && line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
			config->win_height = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] != 0 || config->win_height < 0 || config->win_width < 0)
			return (0);
		return (1);
	}
	return (0);
}

int			parse_texture(t_config *config, int id, char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	config->set[id] = 1;
	while (line[i] == ' ')
		i++;
	line += i;
	if (ft_strlen(line) == 0)
		return (0);
	if (config->tex_path[id])
	{
		free(config->tex_path[id]);
		config->tex_path[id] = 0;
	}
	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	i = 0;
	while (i < len + 1)
		if (is_space(line[i++]))
			return (0);
	if (!(path = ft_substr(line, 0, len + 1)))
		return (-1);
	config->tex_path[id] = path;
	return (1);
}

static int	color_split(char *line)
{
	int i;
	int cnt;
	int	len;

	len = ft_strlen(line);
	cnt = 0;
	while (is_space(line[--len]))
		line[len] = 0;
	i = 0;
	while (i < len + 1)
	{
		if (line[i] == ',')
			cnt++;
		if (line[i] != ',' && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}

int			str_to_color(char *line)
{
	int rgb;
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	rgb = 0;
	if (!color_split(line))
		return (-1);
	while (line[i] && cnt <= 16)
	{
		while (!ft_strrchr(", ", line[i]))
			i++;
		line[i] = 0;
		if (ft_atoi(line) > 255 || ft_atoi(line) < 0)
			return (-1);
		rgb = rgb | (ft_atoi(line) << (16 - cnt));
		line += i + 1;
		i = 0;
		cnt += 8;
	}
	return (rgb);
}

int			parse_color(t_config *config, int id, char *line)
{
	int				i;
	unsigned int	color;

	i = 1;
	config->set[id] = 1;
	while (is_space(line[i]))
		i++;
	if (ft_strlen(line + i) == 0)
		return (0);
	if (!ft_isdigit(line[i]))
		return (parse_texture(config, id, line));
	if ((int)(color = str_to_color(line + i)) < 0)
		return (0);
	config->cf_color[id - T_CEILING] = color;
	return (1);
}
