/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_in_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:32:58 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/28 12:38:03 by dmalesev         ###   ########.fr       */
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
		return (0);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (0);
		if (line && ft_strnequ(ft_strstr(line, str), str, ft_strlen(str)))
			count += 1;
		if (line != NULL)
			free(line);
		line = NULL;
	}
	close(fd);
	return (count);
}
