/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprelast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:35:20 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 13:51:14 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprelast(t_list **alst)
{
	t_list	*temp;
	t_list	*prev;

	if (alst && *alst && (*alst)->next)
	{
		temp = *alst;
		while (temp->next)
		{
			prev = temp;
			temp = temp->next;
		}
		temp->next = *alst;
		*alst = temp;
		prev->next = NULL;
	}
}		
