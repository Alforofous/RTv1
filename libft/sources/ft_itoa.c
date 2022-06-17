/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:30:33 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/28 10:25:55 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_length(long n)
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

static int	get_digit(int n, size_t i)
{
	while (i < (n_length(n) - 1))
		n = n / 10;
	n = n % 10;
	if (n < 0)
		n = n * -1;
	return (n + 48);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	str = (char *)malloc(sizeof(char) * (n_length(n) + 1));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		i++;
	}
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	while (n && n_length(n) > i)
	{
		str[i] = (char)get_digit(n, i);
		i++;
	}
	str[i] = '\0';
	return (str);
}
