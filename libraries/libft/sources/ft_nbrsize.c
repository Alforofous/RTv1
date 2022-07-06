/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:33:57 by dmalesev          #+#    #+#             */
/*   Updated: 2022/06/10 13:56:23 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nbr_length(long n)
{
	size_t	result;

	result = 0;
	if (n < 0)
	{
		n = n * -1;
		result++;
	}
	if (n == 0)
		result++;
	while (n)
	{
		n = n / 10;
		result++;
	}
	return (result);
}
