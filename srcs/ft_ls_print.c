/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:57:40 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/28 18:36:54 by psprawka         ###   ########.fr       */
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
	while (tmp)
	{
		tmp_data = tmp->data;
		if (!S_ISDIR(tmp_data->stat->st_mode))
		{
			if (info->flags & FLAG_i)
				printf("%d ", tmp_data->stat->st_ino);
			FLAG_l & info->flags ? print_long(info, tmp_data) : printf("%s\n", tmp_data->name);
			info->left_args_nb--;
			ft_remove_double_list(&(info->args), tmp);
		}
			tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
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

	info->left_args_nb--;
	tmp = info->flags & FLAG_r ? ft_get_last_double_list(head) : head;
	if (info->flags & FLAG_l)
		printf("total %d\n", calculate_total_size(tmp));
	while (tmp)
	{
		tmp_data = tmp->data;
		if (info->flags & FLAG_i)
			printf("%d ", tmp_data->stat->st_ino);
		FLAG_l & info->flags ? print_long(info, tmp_data) : printf("%s\n", tmp_data->name);
		tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
	tmp = info->flags & FLAG_r ? ft_get_last_double_list(head) : head;
	while (info->flags & FLAG_R && tmp)
	{
		tmp_data = tmp->data;
		if (S_ISDIR(tmp_data->stat->st_mode) && !((ft_strcmp(".", tmp_data->name) == 0 || ft_strcmp("..", tmp_data->name) == 0)))
		{
			printf("\n%s:\n", tmp_data->path);
			print_directories(info, tmp_data->sub, tmp_data->path);
		}
		tmp = info->flags & FLAG_r ? tmp->prev : tmp->next;
	}
	return (EXIT_SUCCESS);
}