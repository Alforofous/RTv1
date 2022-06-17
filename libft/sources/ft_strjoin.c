/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:53:20 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/07 12:22:06 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*n;

	i = 0;
	n = NULL;
	if (s1 && s2)
		n = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (n == NULL)
		return (NULL);
	while (s1[i])
	{
		n[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		n[i + (int)ft_strlen(s1)] = s2[i];
		i++;
	}
	n[i + (int)ft_strlen(s1)] = '\0';
	return (n);
}
