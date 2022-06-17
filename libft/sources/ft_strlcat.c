/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:11:13 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/29 16:15:43 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	d;
	size_t	s;

	i = 0;
	d = ft_strlen(dest);
	s = ft_strlen(src);
	if (len <= d)
		return (len + s);
	while (*dest)
		dest++;
	while (src[i] && (i < len - d - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (d + s);
}
