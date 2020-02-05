/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:02 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/12 00:30:25 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(int nb, char *arg)
{
	if (nb == 1)
		ft_printf("ft_ls: %s: No such file or directory\n", arg);
	if (nb == 2)
	{
		ft_printf("ft_ls: illegal option -- %c\n", arg[0]);
		ft_printf("usage: ft_ls [-alrtR] [file ...]\n");
	}
}

// char	*bulid_path(char *s1, char *s2)
// {
// 	char	*path;
// 	int		i;
// 	int		j;
	
// 	i = 0;
// 	j = 0;
// 	path = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
// 	while (s1[i])
// 	{
// 		path[i] = s1[i];
// 		i++;
// 	}
// 	path[i++] = '/';
// 	while (s2[j])
// 		path[i++] = s2[j++];
// 	path[i] = '\0';
// //	free(s1);
// 	return (path);
// }

int		sort_args(t_info info, char **av, int ac)
{
	t_dnode	*arg;
	t_data	*data;
	
	i = info.nb_args;
	while (i < ac)
	{
		if (!(arg = ft_init_double_list(NULL, sizeof(t_data))) || 
			!(data = alloc_data(ft_strdup(av[i]), ft_strdup(av[i]))) ||  
			ft_add_back_double_list(info.args, arg) == EXIT_FAILURE || 
			lstat(av[i], &(arg.data.stat)) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	// if (merge_sort_ls(info.args, info.flags) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


