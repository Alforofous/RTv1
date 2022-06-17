/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:01:55 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/16 11:18:38 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t b_count)
{
	unsigned char	*cast;
	unsigned char	val;

	cast = (unsigned char *)ptr;
	val = (unsigned char)value;
	while (b_count > 0)
	{
		*cast = val;
		cast++;
		b_count--;
	}
	return (ptr);
}
