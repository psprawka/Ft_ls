/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:38:22 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/12 00:58:05 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* 	In fuction "ls" first I create a linked list with files and and directories
**	belonging to "char *path" path. Afterwards I sort list based on flags
**	given in arguments, then print list either recursively or as it goes
**	and free list in order to avoid memory leaks.
*/
// void	ft_ls(t_arg *all, char *path)
// {
	// *FILES = NULL;
	// *FILES = create_list(*FILES, ft_strdup(path), NULL, FLAGS);
	// merge_sort(FILES, FLAGS);
	// if (FLAGS & FLAG_r)
	// 	all->nb_args == 1 || *FILES == NULL ? print_path_r(*FILES, FLAGS, path)
	// 		: print_path_r(*FILES, FLAGS, NULL);
	// else
	// 	all->nb_args == 1 || *FILES == NULL ? print_path(*FILES, FLAGS, path)
	// 		: print_path(*FILES, FLAGS, NULL);
	// if (*FILES != NULL)
	// 	free(*FILES);
// }

static int	init_info(t_info info)
{
	info.file_context = NULL;
	info.path = NULL;
	info.args = NULL;
	info.flags = 0;
	info.nb_args = 0;
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	t_info	info;
	int		i;
	
	i = 1;
	if (init_info(info) == EXIT_FAILURE ||
		parse_args(info, av, ac) == EXIT_FAILURE ||
		sort_args(info, av, ac) == EXIT_FAILURE ||
		print_files(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	
	// info->nb_args = (ac - i > 0) ? ac - i : 1;
	
	// if (i == ac)
	// 	ft_ls(info, ".");
	// winfole (info->args)
	// {
	// 	ft_ls(info, info->args->name);
	// 	if (info->args->next)
	// 		ft_printf("\n");
	// 	info->args = info->args->next;
	// }
	return (0);
}


