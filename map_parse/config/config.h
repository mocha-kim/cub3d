#ifndef CONFIG_H
# define CONFIG_H

# include "../gnl/get_next_line.h"
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdlib.h>

# define C_R    9
# define C_NO   0
# define C_SO   1
# define C_WE   2
# define C_EA   3
# define C_C    4
# define C_F    5
# define C_S    6
# define C_MAP  7

# define TEXTURES 9
# define T_NO 0
# define T_SO 1
# define T_WE 2
# define T_EA 3
# define T_SKY 4
# define T_FLOOR 5
# define T_SPRITE 6
# define T_SPRITE_UP 7
# define T_SPRITE_C 8

typedef struct	s_config
{
	int			req_height;
	int			req_width;
	char		*tex_path[TEXTURES];
	int			cf_color[2];
}				t_config;

int				identifier(char *line);
int				parse_line(t_config *config, char *line, t_list **map_buffer);
int				parse_config(t_config *config, char *conf_path);
void			config_init(t_config *config);
void			clear_config(t_config *config);

int				parse_resolution(t_config *config, char *line);
int				parse_texture(t_config *config, int id, char *line);
int				str_to_color(char *line);
int				parse_color(t_config *config, int id, char *line);

#endif