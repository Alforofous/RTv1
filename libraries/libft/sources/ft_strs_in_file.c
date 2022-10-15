/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_in_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:32:58 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/15 10:37:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

size_t	ft_strs_in_file(char *path, char *str)
{
	int		fd;
	int		ret;
	char	*line;
	size_t	count;

	count = 0;
	ret = 1;
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (ret > 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		if (line && ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
			count += 1;
		if (line != NULL)
			free(line);
	}
	close(fd);
	return (count);
}
