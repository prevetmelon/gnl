/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chandsom <chandsom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:54:34 by chandsom          #+#    #+#             */
/*   Updated: 2021/01/19 01:58:51 by chandsom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		rewrite_save(char **save, int i)
{
	char *tmp;
	char *tmp2;

	if (*(*save + i) == '\0')
	{
		printf("rewrite_save 1");
		free(*save);
		*save = NULL;
		return ;
	}
	printf("rewrite_save 2, i = %d\n", (size_t)i);
	tmp2 = (*save) + i + 1;
	printf("rewrite_save 3, tmp = %s\n", tmp2);
	tmp = ft_strdup(tmp2);
	printf("rewrite_save 4, i = %s\n", tmp2);
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
	*save = tmp;
}

int			find_lb_in_save(char **save, char **line)
{
	int		i;
	int		j;
	// char	*line;
	i = ft_strlen_lb(*save);
	if (i != -1)
	{
		if (i == 0)
			*line = ft_strdup("");
		else
		{
			j = ft_strlen_lb((*save) + i + 1);
			*line = ft_substr((*save), i + 1, j);
		}
	printf("222");
		rewrite_save(save, i);
		return (1);
	}
	return (0); // non-void warning silenced
}

int			gnl_read(int fd, char **line, char **save)
{
	int			read_val;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;

	read_val = 0;
	tmp = *line;
	if (BUFFER_SIZE <= 0)
		return (-1);
	while ((read_val = read(fd, buf, BUFFER_SIZE)))
	{
		printf("gnl_read\n");
		if (read_val < 0)
			return (-1);
		buf[read_val] = '\0';
		if (*save)
		{
			printf("2\n");
			*line = ft_strjoin(*save, buf);
			free(*save);
			*save = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			*save = ft_strdup(buf);
		}
		if (ft_strchr(buf, '\n'))
			return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*save = NULL;
	int			i;
	int			read_res;

	if (fd < 0 || !line)
		return (-1);
	printf("2nd%s\n", save);
	if (!save && ((read_res = gnl_read(fd, line, &save)) <= 0))
	{
		if (!save)
		{
		// *line = ft_strdup("");
			return (0);
		}
		return (read_res);
	}
	find_lb_in_save(&save, line);
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
	return (1); // non-void warning silenced
}
