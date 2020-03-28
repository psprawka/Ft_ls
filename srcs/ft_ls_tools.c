/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:02 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/28 18:37:10 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  Ft_error() function is called anytime something goes wrong - it displays
**	error message based on 'error_nb'.
*/
void	ft_error(int nb, char *arg1, char arg2)
{
	if (nb == 1)
		printf("ft_ls: %s: No such file or directory\n", arg1);
	if (nb == 2)
	{
		printf("ft_ls: illegal option -- %c\n", arg2);
		printf("usage: ft_ls [-alrtR] [file ...]\n");
	}
}

/*
**	Path_builder() builds a new path by coping and concating given arguments,
**	which are old path and name of the file to concat.
*/
char	*path_builder(char *path, char *name)
{
	char *new_path;

	new_path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1);
	ft_strcpy(new_path, path);
	ft_strcat(new_path, "/");
	ft_strcat(new_path, name);
	return (new_path);
}

bool	if_process_file(t_info *info, char *filename)
{
	
	if (info->flags & FLAG_a)
		return (true);
	
	if (!ft_strcmp(filename, ".") || !ft_strcmp(filename, ".."))
		return (false);	

	if (!(info->flags & FLAG_A) && filename[0] == '.')
		return (false);
	
	return (true);
}


t_data *alloc_data(char *arg_name, char *path_name)
{
	struct stat	*stat;
	t_data		*new_data;
	
	if (!(stat = (struct stat *)malloc(sizeof(struct stat))) ||
		!(new_data = (t_data *)malloc(sizeof(t_data))) ||
		lstat(path_name, stat) == -1)
		return (NULL);
	
	new_data->stat = stat;
	new_data->name = ft_strdup(arg_name);
	new_data->path = ft_strdup(path_name);
	new_data->time = new_data->stat ? &stat->st_mtim : NULL;
	new_data->sub = NULL;
	return (new_data);
}
