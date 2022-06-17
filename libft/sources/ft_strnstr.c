/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:18:32 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/07 10:19:41 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*start;
	const char	*found;
	size_t		i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	start = needle;
	found = haystack;
	while (*haystack && len > i)
	{
		if (*haystack == *needle)
			found = haystack;
		while (*haystack == *needle && len > i + (size_t)(haystack - found))
		{
			haystack++;
			needle++;
			if (*needle == '\0')
				return ((char *)found);
		}
		needle = start;
		i++;
		haystack = found + i;
	}
	return (NULL);
}
