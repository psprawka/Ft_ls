/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:02 by psprawka          #+#    #+#             */
/*   Updated: 2020/02/23 15:40:09 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(int nb, char *arg1, char arg2)
{
	if (nb == 1)
		ft_printf("ft_ls: %s: No such file or directory\n", arg1);
	if (nb == 2)
	{
		ft_printf("ft_ls: illegal option -- %c\n", arg2);
		ft_printf("usage: ft_ls [-alrtR] [file ...]\n");
	}
}

char	*path_builder(char *path, char *name)
{
	char *new_path;
	
	new_path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1);
	ft_strcpy(new_path, path);
	ft_strcat(new_path, "/");
	ft_strcat(new_path, name);
	return (new_path);
}

t_data *alloc_data(char *arg_name, char *path_name)
{
	struct stat	*stat;
	t_data		*new_data;
	
	if (!(stat = (struct stat *)malloc(sizeof(struct stat))) ||
		!(new_data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	
	if (lstat(path_name, stat) == -1)
	{
		free(stat);
		new_data->stat = NULL;
	}
	else 
		new_data->stat = stat;
	new_data->name = ft_strdup(arg_name);
	new_data->path = ft_strdup(path_name);
	new_data->time = new_data->stat ? &stat->st_mtimespec : NULL;
	new_data->sub = NULL;
	
	
	return (new_data);
}


int		sort_args(t_info *info, char **av, int ac)
{
	if (merge_sort_ls(&(info->args), info->flags) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


