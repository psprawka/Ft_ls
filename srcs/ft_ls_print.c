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


void	print_path_r(t_list *all, int flags, char *path)
{
	t_list	*ptr;
	
	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (ptr && ptr->prev != NULL)
	{
		if (!(flags & FLAG_l))
			ft_printf("%s\n", ptr->name);
		else
			print_long(ptr);
		ptr = ptr->prev;
	}
	ptr ? ft_printf("%s\n", ptr->name) : ft_printf("");
	ptr = all;
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (ptr->sub != NULL && ft_printf("\n"))
			print_path(ptr->sub, flags, path);
		ptr = ptr->prev;
	}
}


void	print_path(t_list *all, int flags, char *path)
{
	t_list	*ptr;

	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	while (ptr && ptr->next != NULL)
	{
		if (!(flags & FLAG_l))
			ft_printf("%s\n", ptr->name);
		else
			print_long(ptr);
		ptr = ptr->next;
	}
	ptr ? ft_printf("%s\n", ptr->name) : ft_printf("");
	ptr = all;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (ptr->sub != NULL && ft_printf("\n"))
			print_path(ptr->sub, flags, path);
		ptr = ptr->next;
	}
}
