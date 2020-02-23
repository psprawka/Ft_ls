/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:57:40 by psprawka          #+#    #+#             */
/*   Updated: 2020/02/23 16:22:32 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_files(t_info *info)
{
	t_dnode	*tmp;
	t_data	*tmp_data;

	tmp = info->args;
	while (tmp)
	{
		tmp_data = tmp->data;
		if (!S_ISDIR(tmp_data->stat->st_mode))
		{
			ft_printf("%s\n", tmp_data->name);
			ft_remove_double_list(&(info->args), tmp);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int		print_directories(t_info *info, t_dnode *head, char *path)
{
	t_dnode	*tmp;
	t_data	*tmp_data;

	
	tmp = head;
	ft_printf("\n%s:\n", path);
	while (tmp)
	{
		tmp_data = tmp->data;
		ft_printf("%s\n", tmp_data->name);
		tmp = tmp->next;
	}
	
	tmp = head;
	while (info->flags & FLAG_R && tmp)
	{
		tmp_data = tmp->data;
		if (S_ISDIR(tmp_data->stat->st_mode))
			print_directories(info, tmp_data->sub, tmp_data->path);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

// void	print_path_r(t_list *all, int flags, char *path)
// {
// 	t_list	*ptr;
// 	int 	spaces;
	
// 	ptr = all;
// 	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
// 		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
// 	if (flags & FLAG_l && ptr)
// 		ft_printf("total %d\n", get_total(ptr, 0, &spaces));
// 	while (ptr && ptr->next)
// 		ptr = ptr->next;
// 	while (ptr && ptr->prev != NULL)
// 	{
// 		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
// 		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
// 		ptr = ptr->prev;
// 	}
// 	if (ptr)
// 	{
// 		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
// 		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
// 	}
// 	ptr = all;
// 	while (ptr && ptr->next)
// 		ptr = ptr->next;
// 	while (flags & FLAG_R && ptr != NULL)
// 	{

// 		if (S_ISDIR(ptr->info->st_mode) && ft_strncmp(ptr->name, ".", 1) && ft_printf("\n"))
// 			ptr->sub ? print_path_r(ptr->sub, flags, path) :
// 			print_path_r(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
// 		ptr = ptr->prev;
// 	}
// }

// void	print_path(t_list *all, int flags, char *path)
// {
// 	t_list	*ptr;
// 	int		spaces;

// 	ptr = all;
// 	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
// 		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
// 	if (flags & FLAG_l && ptr)
// 		ft_printf("total %d\n", get_total(ptr, 0, &spaces));
// 	while (ptr && ptr->next != NULL)
// 	{
// 		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
// 		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
// 		ptr = ptr->next;
// 	}
// 	if (ptr)
// 	{
// 		flags & FLAG_i ? ft_printf("%d ", ptr->info->st_ino) : spaces;
// 		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr, spaces);
// 	}
// 	ptr = all;
// 	while (flags & FLAG_R && ptr != NULL)
// 	{
// 		if (S_ISDIR(ptr->info->st_mode) && ft_strncmp(ptr->name, ".", 1) && ft_printf("\n"))
// 			ptr->sub ? print_path(ptr->sub, flags, path) :
// 			print_path(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
// 		ptr = ptr->next;
// 	}
// }
