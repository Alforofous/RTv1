/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:08:51 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 14:20:04 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappnew(t_list **alst, void *content, size_t content_size)
{
	t_list	*temp;

	if (alst && *alst)
	{
		temp = *alst;
		while (temp->next)
			temp = temp->next;
		temp->next = ft_lstnew(content, content_size);
	}
}		
