/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:03:29 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/28 11:02:45 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t			i;
	unsigned int	st;

	if (!s)
		return (NULL);
	st = 0;
	while ((s[st] == ' ' || s[st] == '\t' || s[st] == '\n') && s[st])
		st++;
	if (!s[st])
		return (ft_strsub(s, 0, 0));
	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	return (ft_strsub(s, st, i - st + 1));
}
