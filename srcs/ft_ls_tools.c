/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:02 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/11 02:09:22 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(int nb, char *name)
{
	if (nb == 1)
		ft_printf("ft_ls: %s: No such file or directory\n", name);
	if (nb == 2)
	{
		ft_printf("ft_ls: illegal option -- %c\n", name[0]);
		ft_printf("usage: ft_ls [-alrtR] [file ...]\n");
	}
	exit(0);
}

char	*bulid_path(char *s1, char *s2)
{
	char	*path;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	path = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[i])
	{
		path[i] = s1[i];
		i++;
	}
	path[i++] = '/';
	while (s2[j])
		path[i++] = s2[j++];
	path[i] = '\0';
//	free(s1);
	return (path);
}

int		sort_args(t_arg *info, char **av, int ac)
{
	t_data	*curr;
	
	curr = NULL;
	i = info.nb_args;
	
	while (i < ac)
	{
		curr = add_node(curr, ft_strdup(av[i]), ft_strdup(av[i]));
		lstat(av[i], &(curr.info));
		i++;
	}
	while (curr && curr->prev)
		curr = curr->prev;
	merge_sort(&curr, hi->flags);
	hi->args = curr;
}

static t_flags g_flags[] =
{
	{'a', FLAG_a},
	{'l', FLAG_l},
	{'r', FLAG_r},
	{'R', FLAG_R},
	{'t', FLAG_t},
	{'G', FLAG_G},
	{'i', FLAG_i},
	{'A', FLAG_A},
	{'\0', NULL}
};

static int	set_flag(t_arg info, char x)
{
	int i;
	
	i = 0;
	while (g_flags[i])
	{
		if (x == g_flags[i].flag)
		{
			info.flags |= g_flags[i].flag_value;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	ft_error(2, arg);
	return (EXIT_FAILURE);
}

int			parse_args(t_arg info, char **av, int ac)
{
	int		i;
	int		j;
	
	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		j = 0;
		while (av[i][j])
		{
			if (set_flag(info, av[i][j]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	info.nb_args = i - 1;
	return (EXIT_SUCCESS);
}
