/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:57:40 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/18 22:57:42 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_long(t_list *ptr)
{
	
	
}

void	print_path(t_list *all, int flags)
{
	t_list	*ptr;
	char *color;
	
	ptr = all;
	ft_printf("%s:\n", ptr->path);
	while (ptr->next != NULL)
	{
		if (!(flags & FLAG_l))
			ft_printf("[%s] -> ", ptr->name);
		else
			print_long(ptr);
		ptr = ptr->next;
	}
	ft_printf("[%s] -> NULL\n", ptr->name);
	ptr = all;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (ptr->sub != NULL)
			print_path(ptr->sub, flags);
		ptr = ptr->next;
	}
}
