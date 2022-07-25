/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:28:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/25 14:16:55 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	abs_val(int nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

static char	get_digit(double nbr, int i, size_t prec)
{
	int	n;
	int	j;

	j = 0;
	i -= (int)nbr_length(abs_val((int)nbr)) - 1;
	while (j < (int)prec)
	{
		nbr *= 10;
		j++;
	}
	n = (int)nbr;
	if (n < 0)
		n = n * -1;
	while ((int)prec - i > 0)
	{
		n = n / 10;
		prec--;
	}
	n = n % 10;
	n += 48;
	return ((char)n);
}

static void	edges(double *f, int *pre_intv, char *str, size_t prec)
{
	if (*f < 0)
	{
		str[0] = '-';
		*pre_intv += 1;
	}
	if ((int)*f == 0)
	{
		str[0 + *pre_intv] = '0';
		str[1 + *pre_intv] = '.';
		*pre_intv += 2;
		*f *= 10;
	}
	while ((int)*f == 0 && prec > (size_t)(*pre_intv))
	{
		str[*pre_intv] = '0';
		*pre_intv += 1;
		*f *= 10;
	}
}

char	*ft_ftoa(double f, size_t prec)
{
	char	*str;
	size_t	len;
	int		i;
	int		pre_intv;

	len = (nbr_length((int)f) + 1 + prec);
	if (f < 0 && f > -1)
		len++;
	str = ft_strnew(len);
	pre_intv = 0;
	edges(&f, &pre_intv, str, prec);
	i = 0;
	while (i < (int)len - pre_intv)
	{
		if ((int)nbr_length((int)f) == i + pre_intv)
		{
			str[i + pre_intv] = '.';
			pre_intv++;
		}
		str[i + pre_intv] = get_digit(f, i, prec);
		i++;
	}
	return (str);
}
