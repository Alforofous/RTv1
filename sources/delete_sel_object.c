/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sel_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:10:28 by dmalesev          #+#    #+#             */
/*   Updated: 2022/10/13 15:55:10 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_lstcnct(t_list **from, t_list **to)
{
	if (*from)
		(*from)->next = *to;
}

void	del_object(void *content, size_t content_size)
{
	t_object	*object;

	object = (t_object *)content;
	ft_bzero(content, content_size);
	free(object);
}

void	delete_sel_object(t_utils *utils, t_list **scene)
{
	t_list		*temp;
	t_list		*prev;
	t_object	*object;

	temp = *scene;
	prev = NULL;
	while (*scene != NULL)
	{
		object = (t_object *)(*scene)->content;
		if (object == utils->sel_object)
		{
			if (prev == NULL)
				temp = (*scene)->next;
			else
				ft_lstcnct(&prev, &(*scene)->next);
			ft_lstdelone(scene, &del_object);
		}
		prev = *scene;
		if (*scene != NULL)
			*scene = (*scene)->next;
	}
	*scene = temp;
	utils->sel_object = NULL;
}
