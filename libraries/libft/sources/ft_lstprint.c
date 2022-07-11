/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:09:36 by dmalesev          #+#    #+#             */
/*   Updated: 2022/07/11 13:19:19 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, void (*f)(t_list *))
{
	int	i;

	i = 1;
	while (lst)
	{
		write(1, "Node[", 5);
		ft_putnbr(i);
		write(1, "]:\t", 4);
		f(lst);
		write(1, "\n", 2);
		lst = lst->next;
		i++;
	}
}
