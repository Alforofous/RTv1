/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:22:03 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/19 14:04:49 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;
	unsigned char	chr;

	i = 0;
	chr = (unsigned char)c;
	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (len > i)
	{
		ptr[i] = ptr2[i];
		if (ptr2[i] == chr)
			return (ptr + i + 1);
		i++;
	}
	return (NULL);
}
