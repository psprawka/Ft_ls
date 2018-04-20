/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:38:22 by psprawka          #+#    #+#             */
/*   Updated: 2017/12/29 13:38:24 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


//void	add_node(t_list *list, char *name, char *path)
//{
//	t_list	*new;
//
//	new = ft_memalloc(1);
//	new->name = name;
//	new->path = path;
//	new->next = NULL;
//	new->prev = NULL;
//	while (list && list->next != NULL)
//		list = list->next;
//
//	if (list == NULL)
//		list = new;
//	else
//	{
//		new->prev = list;
//		list->next = new;
//	}
//}



char	*convert_binary(unsigned long int nb)
{
	char	*print;
	int		i;
	
	i = 0;
	print = ft_memalloc(33);
	if (nb == 0)
		print[i] = '0';
	while (nb != 0)
	{
		print[i++] = (nb % 2) + 48;
		nb /= 2;
	}
	return (ft_strrev(print));
}





int		main(int ac, char **av)
{
	t_list		**all;
	int			i;
	int			flags;
	int			args;
	
	i = 1;
	flags = 0;
	all = (t_list **)malloc(sizeof(t_list *));
	if (ac > 1)
		parse(&i, av, &flags);
	args = ac - i;
	while (i < ac)
	{
		*all = NULL;
		*all = create_list(*all, ft_strdup(av[i]), NULL, flags);
		merge_sort(all, flags);
		args == 1  || *all == NULL ? print_path(*all, flags, av[i])
			: print_path(*all, flags, NULL);
		if (*all != NULL)
			free(*all);
		i++;
		if (i < ac)
			ft_printf("\n");
	}

	return (0);
}


