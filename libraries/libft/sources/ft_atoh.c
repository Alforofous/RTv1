/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 09:16:49 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/21 09:38:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	alpha_distance(char c, char	*closeup)
{
	if (c >= 'A' && c <= 'F')
		*closeup = 7;
	else if (c >= 'a' && c <= 'f')
		*closeup = 39;
	else
		*closeup = 0;
}

int	ft_atoh(const char *str)
{
	long	res;
	char	closeup;

	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '0' && *(str + 1) == 'x')
		str += 2;
	while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')
		|| (*str >= 'a' && *str <= 'f'))
	{
		alpha_distance(*str, &closeup);
		res = res * 16 + (*str - '0' - closeup);
		str++;
	}
	return ((int)res);
}
