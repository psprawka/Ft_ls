/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:21 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/18 22:58:24 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*add_node(t_list *prev, char *name, char *path)
{
	t_list	*new;
	
	new = (t_list *)malloc(sizeof(t_list));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	new->next = NULL;
	new->prev = NULL;
	new->sub = NULL;
	if (prev == NULL)
		prev = new;
	else
	{
		new->prev = prev;
		prev->next = new;
	}
	return (new);
}

t_list	*create_list(t_list *curr, char *path, char *name, int flags)
{
	DIR 			*directory;
	struct dirent	*file;
	struct stat		*info;

	if ((directory = opendir(path)) == NULL)
		ft_error(1, path);
	while ((file = readdir(directory)) != NULL)
	{
		info = (struct stat *)malloc(sizeof(struct stat));
		if (file->d_name[0] == '.' && !(flags & FLAG_a))
			continue;
		name = bulid_path(ft_strdup(path), file->d_name);
		curr = add_node(curr, file->d_name, path);
		lstat(name, info);
		curr->info = info;
		curr->time = info->st_mtimespec;
		if (ft_strncmp(file->d_name, ".", 1)
			&& S_ISDIR(info->st_mode) && flags & FLAG_R)
			curr->sub = create_list(curr->sub, name, NULL, flags);
		else
			curr->sub = NULL;
		free(name);
	}
	closedir(directory);
	while (curr && curr->prev != NULL)
		curr = curr->prev;
	return (curr);
}
