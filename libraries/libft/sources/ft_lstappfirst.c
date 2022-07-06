/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:12:50 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 14:19:50 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappfirst(t_list **alst)
{
	t_list	*temp;

	if (alst && *alst && (*alst)->next)
	{
		temp = *alst;
		while (temp->next)
			temp = temp->next;
		temp->next = *alst;
		*alst = (*alst)->next;
		temp->next->next = NULL;
	}
}		
