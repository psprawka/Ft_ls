/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:58:02 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/18 22:58:04 by psprawka         ###   ########.fr       */
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

void	sort_args(t_arg *hi, char **av, int ac, int i)
{
	t_list		*curr;
	struct stat	*info;
	
	curr = NULL;
	while (i < ac)
	{
		info = (struct stat *)malloc(sizeof(struct stat));
		curr = add_node(curr, ft_strdup(av[i]), ft_strdup(av[i]));
		lstat(av[i], info);
		curr->info = info;
		i++;
	}
	while (curr && curr->prev)
		curr = curr->prev;
	merge_sort(&curr, hi->flags);
	hi->args = curr;
}

void	parse(int *i, char **av, int *flags)
{
	int		j;
	while (av[*i] && av[*i][0] == '-')
	{
		j = 1;
		while (av[*i][j])
		{
			if (av[*i][j] == 'a')
				*flags |= FLAG_a;
			else if (av[*i][j] == 'l')
				*flags |= FLAG_l;
			else if (av[*i][j] == 'r')
				*flags |= FLAG_r;
			else if (av[*i][j] == 'R')
				*flags |= FLAG_R;
			else if (av[*i][j] == 't')
				*flags |= FLAG_t;
			else if (av[*i][j] == 'G')
				*flags |= FLAG_G;
			else if (av[*i][j] == 'i')
				*flags |= FLAG_i;
			else if (av[*i][j] == 'A')
				*flags |= FLAG_A;
			else
				ft_error(2, &(av[*i][j]));
			j++;
		}
		(*i)++;
	}
}
