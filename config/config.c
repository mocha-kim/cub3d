#include "config.h"

int		identifier(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else
		return (C_MAP);
}

int		parse_line(t_config *config, char *line, t_list **map_buffer)
{
	static int	empty_map = 0;
	// static int	after_empty = 0;
	int			id;
	int			len;

	len = ft_strlen(line);
	if (len == 0 && config->set[C_MAP])
		empty_map = 1;
	// if (empty_map && after_empty)
	// 	return (0);
	if (len == 0)
		return (1);
	id = identifier(line);
	if (id != C_MAP && id != C_S && (config->set[C_MAP] || config->set[id]))
		return (0);
	if (id == C_R)
		return (parse_resolution(config, line));
	else if ((id >= C_NO && id <= C_EA) || id == C_S)
		return (parse_texture(config, id, line));
	else if (id == C_F || id == C_C)
		return (parse_color(config, id, line));
	config->set[id] = 1;
	if (empty_map || !element_check(config->set))
		return (0);
	return (!!lst_add_back(map_buffer, ft_strdup(line)));
}

void	config_init(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = 0;
	config->map = NULL;
	i = 0;
	while (i < 9)
		config->set[i++] = 0;
	config->pos_x = 0;
	config->pos_y = 0;
}

int		parse_config(t_config *config, char *path)
{
	int		fd;
	char	*line;
	t_list	*map_buffer;
	int		r;

	if (!ft_endcmp(path, ".cub"))
		return (0);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	config_init(config);
	map_buffer = 0;
	r = 1;
	while (get_next_line(fd, &line))
	{
		r = (r && parse_line(config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = (r && parse_line(config, line, &map_buffer));
	free(line);
	close(fd);
	if (!r || !parse_map(config, map_buffer))
		return (lst_clear(&map_buffer));
	lst_clear(&map_buffer);
	return (1);
}

void	clear_config(t_config *config)
{
	int i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		i++;
	}
}
