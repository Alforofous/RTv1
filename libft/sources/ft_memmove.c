/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:43:00 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/22 11:03:14 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	i = 0;
	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (!ptr && !ptr2)
		return (NULL);
	if (ptr > ptr2)
		while (len--)
			ptr[len] = ptr2[len];
	else
	{
		while (len > i)
		{
			ptr[i] = ptr2[i];
			i++;
		}
	}
	return (dest);
}
