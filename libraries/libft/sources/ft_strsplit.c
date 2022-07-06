/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:24:14 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/07 16:38:44 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	ft_free_array(char ***array)
{
	int	i;

	i = 0;
	while (*array[i])
	{
		free(*array[i]);
		*array[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

static char	**ft_fill_alloc(char **new, char const *s, char c, int size)
{
	unsigned int	i;
	unsigned int	len;
	int				j;

	i = 0;
	j = 0;
	len = 0;
	while (size--)
	{
		while (s[i] == c)
			i++;
		len = i;
		while (s[len] != c && s[len])
			len++;
		new[j] = ft_strsub(s, i, (size_t)(len - i));
		if (!new[j])
		{
			ft_free_array(&new);
			return (NULL);
		}
		i = len;
		j++;
	}
	new[j] = NULL;
	return (new);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			len++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	new = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	new = ft_fill_alloc(new, s, c, (int)len);
	return (new);
}
