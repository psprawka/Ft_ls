/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:57:40 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/10 20:55:30 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Function print_files() is created to print only files, not directories,
**	that are given as parameters in the command line. This function takes
**	a list of names and checks, one by one, if any is a file. If so, function
**	prints its name and removes it from a list. This way, there are only dirs
**	left in list after a function.
**	Disclaimer: this function is dumb and not modular, I personally do not like
**	it, but ls has many exceptions that need to be handled somehow and that
**	is one of them.
*/
int		print_files(t_info *info)
{
	t_dnode	*tmp;
	t_data	*tmp_data;

	tmp = info->flags & FLAG_r ? ft_get_last_double_list(info->args) : info->args;
	//ft_print_double_list(info->args, NULL);
	while (tmp)
	{
		tmp_data = tmp->data;
		if (!S_ISDIR(tmp_data->stat->st_mode))
		{
			if (tmp_data->name[0] == '-')
				ft_error(1, tmp_data->name, '\0');
			else
				printf("%s\n", tmp_data->name);
			t_dnode *to_rm = tmp;
			//tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
			ft_remove_double_list(&(info->args), to_rm);
		}
		//else
			tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
	//ft_print_double_list(info->args, NULL);
	return (EXIT_SUCCESS);
}

/*
**	Function print_directories() prints the list of files and directories
**	starting in *head. After that, on every object that is a directory, it
**	calls print_directories() (itself) in order to print a subdirectory.
**	TODO: problem with first printf. It should be printed if the number of
**	arguments (given in command line) to process is more than one, but not
**	when its only one, thus the check "if (info->args_nb > 1)" would work,
**	but probems with recursive calls apprear, because then even when number
**	or args to process is one, it should be displayed for subdirectories.
**	Try out "ls Libft/", "ls -R Libft/" and "ls -t Libft/" to understand.
*/
int		print_directories(t_info *info, t_dnode *head, char *path)
{
	t_dnode	*tmp;
	t_data	*tmp_data;

	tmp = info->flags & FLAG_r ? ft_get_last_double_list(head) : head;
	//if (info->args_nb > 1 || FLAG_R & info->flags) //|| head != info->args)// <- play with this check
		//printf("\n%s:\n", path);
	while (tmp)
	{
		tmp_data = tmp->data;
		printf("%s\n", tmp_data->name);
		tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
	
	tmp = info->flags & FLAG_r ? ft_get_last_double_list(head) : head;
	while (info->flags & FLAG_R && tmp)
	{
		tmp_data = tmp->data;
		if (S_ISDIR(tmp_data->stat->st_mode))
		{
			printf("\n%s:\n", tmp_data->path);
			print_directories(info, tmp_data->sub, tmp_data->path);
		}
		tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
	return (EXIT_SUCCESS);
}

/*
** ========================== ALL TO FIX LATER ============================
*/

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
