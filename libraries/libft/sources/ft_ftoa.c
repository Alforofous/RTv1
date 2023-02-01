/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:28:36 by dmalesev          #+#    #+#             */
/*   Updated: 2023/02/01 20:18:20 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	abs_val(long long int nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

static char	get_digit(double nbr, long long int i, size_t prec)
{
	long long int	n;
	long long int	j;

	j = 0;
	i -= (long long int)nbr_length(abs_val((long long int)nbr)) - 1;
	while (j < (long long int)prec)
	{
		nbr *= 10;
		j++;
	}
	n = (long long int)nbr;
	if (n < 0)
		n = n * -1;
	while ((long long int)prec - i > 0)
	{
		n = n / 10;
		prec--;
	}
	n = n % 10;
	n += 48;
	return ((char)n);
}

static void	edges(double *f, long long int *pre, char *str, size_t prec)
{
	*pre = 0;
	if (*f < 0)
	{
		str[0] = '-';
		*pre += 1;
	}
	if ((long long int)*f == 0)
	{
		str[0 + *pre] = '0';
		str[1 + *pre] = '.';
		*pre += 2;
		*f *= 10;
	}
	while ((long long int)*f == 0 && prec > (size_t)(*pre))
	{
		str[*pre] = '0';
		*pre += 1;
		*f *= 10;
	}
}

char	*ft_ftoa(double f, size_t prec)
{
	char			*str;
	size_t			len;
	long long int	i;
	long long int	pre;

	len = (nbr_length((long long int)f) + 1 + (size_t)ft_max((int)prec, 0));
	if (f < 0 && f > -1)
		len++;
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	edges(&f, &pre, str, prec);
	i = 0;
	while (i < (long long int)len - pre)
	{
		if ((long long int)nbr_length((long long int)f) == i + pre)
		{
			str[i + pre] = '.';
			pre++;
		}
		str[i + pre] = get_digit(f, i, prec);
		i++;
	}
	return (str);
}
