/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chandsom <chandsom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:54:34 by chandsom          #+#    #+#             */
/*   Updated: 2021/01/19 00:19:59 by chandsom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		rewrite_save(char **save, int i)
{
	char *tmp;

	if (*(*save + i + 1) == 0)
	{
		free(*save);
		*save = NULL;
		return ;
	}
	tmp = ft_strdup(*save + (size_t)i + 1);
	free(*save);
	*save = tmp;
}

int			find_lb_in_save(char *save, char **line)
{
	int		i;
	// char	*line;
	i = ft_strlen_lb(save);
	if (i != -1)
	{
		if (i == 0)
			*line = ft_strdup("");
		else
			*line = ft_substr(save, 0, i);
		rewrite_save(&save, i);
		return (1);
	}
	return (0); // non-void warning silenced
}

int			get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buf;
	int			read_val;
	int			i;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	tmp = *line;
	while ((read_val = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_val < 0)
			return (-1);
		buf[read_val] = '\0';
		if (save)
		{
			*line = ft_strjoin(save, buf);
			free(save);
			save = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			save = ft_strdup(buf);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!save && read_val == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	find_lb_in_save(save, line);
	i = ft_strlen_lb(save);
	if (i != -1)
	{
		if (i == 0)
			*line = ft_strdup("");
		else
			*line = ft_substr(save, 0, i);
		rewrite_save(&save, i);
		return (1);
	}
	return (0); // non-void warning silenced
}
