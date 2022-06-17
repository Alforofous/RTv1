/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:33:41 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 13:16:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *alst;
	if (alst && *alst && del)
	{
		while (temp)
		{
			temp2 = temp->next;
			ft_lstdelone(&temp, del);
			temp = temp2;
		}
		*alst = NULL;
	}
}
