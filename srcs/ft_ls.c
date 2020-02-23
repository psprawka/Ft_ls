/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:38:22 by psprawka          #+#    #+#             */
/*   Updated: 2020/02/23 16:25:55 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	init_info(t_info *info)
{
	info->path = NULL;
	info->args = NULL;
	info->flags = 0;
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	t_info	info;
	t_dnode	*tmp;
	t_data	*tmp_data;
	
	if (init_info(&info) == EXIT_FAILURE ||
		parse_args(&info, av, ac) == EXIT_FAILURE ||
		sort_args(&info, av, ac) == EXIT_FAILURE ||
		print_files(&info) == EXIT_FAILURE) 
		return (EXIT_FAILURE);
	
	tmp = info.args;
	while (tmp)
	{
		tmp_data = tmp->data;
		print_directories(&info, tmp_data->sub, tmp_data->path);
		tmp = tmp->next;
	}
	return (0);
}


