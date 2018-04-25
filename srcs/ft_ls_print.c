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

void	print_files(t_arg *all)
{
	t_list	*ptr;
	int		spaces;
	int		printed;

	ptr = all->args;
	printed = 0;
	get_total(ptr, 0, &spaces);
	while (ptr)
	{
		if (!S_ISDIR(ptr->info->st_mode))
		{
			printed++;
			all->flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
			!(all->flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
			ptr = delete_node(ptr);
			all->args = ptr;
		}
		else
			ptr = ptr->next;
	}
	while (all->args && all->args->prev)
		all->args = all->args->prev;
	if (printed && all->args)
		ft_printf("\n");
}

void	print_path_r(t_list *all, int flags, char *path)
{
	t_list	*ptr;
	int 	spaces;
	
	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	if (flags & FLAG_l && ptr)
		ft_printf("total %d\n", get_total(ptr, 0, &spaces));
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (ptr && ptr->prev != NULL)
	{
		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
		ptr = ptr->prev;
	}
	if (ptr)
	{
		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
	}
	ptr = all;
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (flags & FLAG_R && ptr != NULL)
	{

		if (S_ISDIR(ptr->info->st_mode) && ft_strncmp(ptr->name, ".", 1) && ft_printf("\n"))
			ptr->sub ? print_path_r(ptr->sub, flags, path) :
			print_path_r(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
		ptr = ptr->prev;
	}
}

void	print_path(t_list *all, int flags, char *path)
{
	t_list	*ptr;
	int		spaces;

	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	if (flags & FLAG_l && ptr)
		ft_printf("total %d\n", get_total(ptr, 0, &spaces));
	while (ptr && ptr->next != NULL)
	{
		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
		ptr = ptr->next;
	}
	if (ptr)
	{
		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
	}
	ptr = all;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (S_ISDIR(ptr->info->st_mode) && ft_strncmp(ptr->name, ".", 1) && ft_printf("\n"))
			ptr->sub ? print_path(ptr->sub, flags, path) :
			print_path(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
		ptr = ptr->next;
	}
}
