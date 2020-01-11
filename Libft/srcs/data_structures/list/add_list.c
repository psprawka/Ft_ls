/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 03:35:23 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/11 02:29:07 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_add_back_list(t_node **list, t_node *node)
{
	t_node *tmp;

	if (!(*list))
	{
		*list = node;
		return (EXIT_SUCCESS);
	}
	
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
		
	tmp->next = node;
	return (EXIT_SUCCESS);
}

int		ft_add_front_list(t_node **list, t_node *node)
{
	if (!(*list))
	{
		*list = node;
		return (EXIT_SUCCESS);
	}
	
	node->next = *list;
	*list = node;
	return (EXIT_SUCCESS);
}