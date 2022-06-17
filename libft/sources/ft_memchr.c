/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:57:19 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/29 12:30:45 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t len)
{
	unsigned char	*new;
	unsigned char	chr;
	size_t			i;

	new = (unsigned char *)str;
	chr = (unsigned char)c;
	i = 0;
	while (i < len)
	{	
		if (new[i] == chr)
			return ((void *)(new + i));
		i++;
	}
	return (NULL);
}
