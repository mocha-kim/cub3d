/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahnys <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:28:37 by ahnys             #+#    #+#             */
/*   Updated: 2021/04/07 16:06:04 by ahnys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(char *s);
int					ft_endcmp(char *str, char *s);
int					lst_add_back(t_list **list, char *line);
int					is_space(char ch);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strrchr(char *s, int c);

#endif
