/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 00:11:13 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/28 18:36:35 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

 t_flags g_flags[] =
{
	{'a', FLAG_a},
	{'l', FLAG_l},
	{'r', FLAG_r},
	{'R', FLAG_R},
	{'t', FLAG_t},
	{'G', FLAG_G},
	{'i', FLAG_i},
	{'A', FLAG_A},
	{'\0', 0}
};

/*
**	Function set_flag() checks in a global table if a given flag 'x' exists.
**	If so, it sets the flag in info.flags and returns EXIT_SUCCESS, otherwise
**	EXIT_FAILURE is returned and program terminates.
*/
static int	set_flag(t_info *info, char x)
{
	int i;
	
	i = 0;
	while (g_flags[i].flag)
	{
		if (x == g_flags[i].flag)
		{
			info->flags |= g_flags[i].flag_value;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	ft_error(2, NULL, x);
	return (EXIT_FAILURE);
}

static int	create_recursive_list(t_info *info, t_dnode *node, t_data *curr_data)
{
	DIR 			*directory;
	struct dirent	*file;
	t_dnode			*new_node;
	t_data			*new_data;

	if ((directory = opendir(curr_data->path)) == NULL)
		return (EXIT_FAILURE);
		
	while ((file = readdir(directory)) != NULL)
	{
		if (if_process_file(info, file->d_name) == false)
			continue;
		new_data = alloc_data(file->d_name, path_builder(curr_data->path, file->d_name));
		new_node = ft_init_double_list(new_data, sizeof(t_data));
		ft_add_back_double_list(&(curr_data->sub), new_node);
		
		if (ft_strcmp(".", new_data->name) == 0 || ft_strcmp("..", new_data->name) == 0)
			continue;
		if ((info->flags & FLAG_R) && S_ISDIR(new_data->stat->st_mode))
			create_recursive_list(info, new_node, new_data);	
	}
	closedir(directory);
	return (EXIT_SUCCESS);
}

static int	create_list_args(t_info *info, char *arg_name)
{
	t_dnode	*new_node;
	t_data	*data;

	if (!(data = alloc_data(arg_name, arg_name)) ||
		!(new_node = ft_init_double_list(data, sizeof(t_data))) ||
		ft_add_back_double_list(&(info->args), new_node) == EXIT_FAILURE)
	{
		ft_error(1, arg_name, '\0');
		return (EXIT_FAILURE);
	}
		
	if (S_ISDIR(data->stat->st_mode) &&
		create_recursive_list(info, new_node, data))
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

/*
**	Function parse_args() goes through all of the parameters passed to
**	the program and finds all of the flags (indicated by '-') up to first
**	not flag parameter. For all found flags, they are one by one passed
**	to set_flag() which checks in a global table if a flag exists. If it
**	does not, EXIT_FAILURE is returned and program terminates. All forward
**	parameters (after first non-flag one) are added to 'info.args' (via 
**	create_list_args()), which holds all of the args to process later.
*/
int			parse_args(t_info *info, char **av, int ac)
{
	int		i;
	int		j;
	
	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (set_flag(info, av[i][j]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	info->args_nb = ac - i;
	info->left_args_nb = ac - i;
	if (i == ac)
		create_list_args(info, ".");
	while (i < ac)
		create_list_args(info, av[i++]);
	return (EXIT_SUCCESS);
}
