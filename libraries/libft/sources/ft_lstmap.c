/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:54:10 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/08 12:52:37 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*read;

	new = NULL;
	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(lst->content, lst->content_size);
	if (!new)
		return (NULL);
	new = f(new);
	lst = lst->next;
	read = new;
	while (lst)
	{
		read->next = ft_lstnew(lst->content, lst->content_size);
		if (!read->next)
		{
			ft_lstdel(&new, &ft_bzero);
			return (NULL);
		}
		read->next = f(read->next);
		lst = lst->next;
		read = read->next;
	}
	return (new);
}
