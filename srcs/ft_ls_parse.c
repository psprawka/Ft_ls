/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 00:11:13 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/12 00:15:00 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int			parse_args(t_info info, char **av, int ac)
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