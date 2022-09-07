/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sel_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:10:28 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/07 13:00:34 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_lstcnct(t_list **from, t_list **to)
{
	if (*from)
		(*from)->next = *to;
}

static void	del_object(void *content, size_t content_size)
{
	t_object	*object;

	object = (t_object *)content;
	ft_bzero(content, content_size);
	free(object->content);
	free(object);
}

void	delete_sel_object(t_utils *utils, t_list **objects)
{
	t_list		*temp;
	t_list		*prev;
	t_object	*object;

	temp = *objects;
	prev = NULL;
	while (*objects != NULL)
	{
		object = (t_object *)(*objects)->content;
		if (object == utils->sel_object)
		{
			if (prev == NULL)
				temp = (*objects)->next;
			else
				ft_lstcnct(&prev, &(*objects)->next);
			ft_lstdelone(objects, &del_object);
		}
		prev = *objects;
		if (*objects != NULL)
			*objects = (*objects)->next;
	}
	*objects = temp;
	utils->sel_object = NULL;
	utils->closest_object = NULL;
	render_screen(utils);
}
