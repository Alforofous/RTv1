/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:16:49 by dmalesev          #+#    #+#             */
/*   Updated: 2021/11/29 15:46:35 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (*p1 == *p2 && *p1 && *p2 && n > 1)
	{
		p1++;
		p2++;
		n--;
	}
	if (*p1 - *p2 < 0)
		return (-1);
	if (*p1 - *p2 > 0)
		return (1);
	return (0);
}
