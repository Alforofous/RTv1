/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:18:32 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/23 13:03:18 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*start;
	const char	*found;

	if (*needle == '\0')
		return ((char *)haystack);
	start = needle;
	found = haystack;
	while (*haystack)
	{
		if (*haystack == *needle)
			found = haystack;
		while (*haystack == *needle)
		{
			haystack++;
			needle++;
			if (*needle == '\0')
				return ((char *)found);
		}
		haystack = found;
		needle = start;
		haystack++;
		found++;
	}
	return (NULL);
}
