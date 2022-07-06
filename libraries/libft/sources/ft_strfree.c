/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:33:29 by dmalesev          #+#    #+#             */
/*   Updated: 2021/12/21 13:54:52 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfree(char **array)
{
	ft_bzero(*array, ft_strlen(*array));
	free(*array);
	*array = NULL;
	array = NULL;
}
