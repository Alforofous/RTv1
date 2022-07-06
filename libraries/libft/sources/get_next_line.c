/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:40:07 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/16 11:24:24 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_into_buffer(const int fd, char **line, char **buffer)
{
	char	*save;

	save = ft_strjoin(*line, *buffer);
	ft_strfree(&(*line));
	*line = save;
	ft_bzero(*buffer, BUFF_SIZE);
	return ((int)read(fd, *buffer, BUFF_SIZE));
}

static void	buffer_to_line(const int fd, char **line, char **buffer)
{	
	char	*help_buff;
	char	*save;
	char	*save2;
	size_t	new_line;

	help_buff = ft_strchr(*buffer, '\n');
	if (!help_buff)
	{
		if (read_into_buffer(fd, line, buffer))
			buffer_to_line(fd, line, buffer);
	}
	else
	{
		new_line = ft_strlen(help_buff);
		save = ft_strsub(*buffer, 0, ft_strlen(*buffer) - new_line);
		save2 = ft_strjoin(*line, save);
		ft_strfree(&(*line));
		*line = save2;
		ft_strfree(&save);
		ft_memcpy(*buffer, help_buff + 1, new_line);
		ft_bzero((*buffer) + new_line, (BUFF_SIZE - new_line));
	}
}

static int	prepare_line(const int fd, char **line, char **buffer)
{
	char	*temp_line;

	temp_line = ft_strnew(0);
	buffer_to_line(fd, &temp_line, buffer);
	if (temp_line == NULL)
		return (-1);
	*line = temp_line;
	temp_line = NULL;
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*buffer[FD_MAX];
	int			read_ret;

	if (fd < 0 || fd > FD_MAX || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (buffer[fd] && *(buffer[fd]))
		return (prepare_line(fd, line, &(buffer[fd])));
	else
	{
		if (!buffer[fd])
			buffer[fd] = ft_strnew(BUFF_SIZE);
		if (!buffer[fd])
			return (-1);
		read_ret = (int)read(fd, buffer[fd], BUFF_SIZE);
		if (read_ret > 0)
			return (prepare_line(fd, line, &(buffer[fd])));
		else
		{
			ft_memfree((void **)&(buffer[fd]), BUFF_SIZE);
			return (read_ret);
		}
	}
}
