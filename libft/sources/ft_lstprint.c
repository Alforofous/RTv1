/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:09:36 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 13:13:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	char	c;

	c = '1';
	while (lst)
	{
		write(1, "Node[", 5);
		write(1, &c, 1);
		write(1, "]:\t<", 4);
		write(1, lst->content, lst->content_size);
		write(1, ">\n", 2);
		lst = lst->next;
		c++;
	}
}
