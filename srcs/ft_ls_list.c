/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:21 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/11 23:45:01 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// t_list	*create_list(t_list *curr, char *path, char *name, int flags)
// {
	// DIR 			*directory;
	// struct dirent	*file;
	// struct stat		*info;

	// file_exists(path);
	// if ((directory = opendir(path)) == NULL)
	// 	return (NULL);
		
	// while ((file = readdir(directory)) != NULL)
	// {
	// 	info = (struct stat *)malloc(sizeof(struct stat));
	// 	if (file->d_name[0] == '.' && !(flags & FLAG_a))
	// 		continue;
	// 	name = bulid_path(ft_strdup(path), file->d_name);
	// 	curr = add_node(curr, file->d_name, path);
	// 	lstat(name, info);
	// 	curr->info = info;
	// 	curr->time = info->st_mtimespec;
	// 	if (ft_strncmp(file->d_name, ".", 1)
	// 		&& S_ISDIR(info->st_mode) && flags & FLAG_R)
	// 		curr->sub = create_list(curr->sub, name, NULL, flags);
	// 	else
	// 		curr->sub = NULL;
	// 	free(name);
	// }
	// closedir(directory);
	// while (curr && curr->prev != NULL)
	// 	curr = curr->prev;
	// return (curr);
// }
