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


/* 	In fuction "ls" first I create a linked list with files and adn directories
**	belonging to "char *path" path. Afterwards I sort list based on flags
**	given in arguments, then print list either recursively or as it goes
**	and free list in order to avoid memory leaks.
*/

void	ft_ls(t_arg *all, char *path)
{
	*FILES = NULL;
	*FILES = create_list(*FILES, ft_strdup(path), NULL, FLAGS);
	merge_sort(FILES, FLAGS);
	if (FLAGS & FLAG_r)
		all->nb_args == 1 || *FILES == NULL ? print_path_r(*FILES, FLAGS, path)
			: print_path_r(*FILES, FLAGS, NULL);
	else
		all->nb_args == 1 || *FILES == NULL ? print_path(*FILES, FLAGS, path)
			: print_path(*FILES, FLAGS, NULL);
	if (*FILES != NULL)
		free(*FILES);
}

void	init_arg(t_arg **hi)
{
	*hi = (t_arg *)malloc(sizeof(t_arg));
	(*hi)->all = (t_list **)malloc(sizeof(t_list *));
	(*hi)->args = (t_list *)malloc(sizeof(t_list));
	(*hi)->flags = 0;
}


void	sort_args(t_arg *hi, char **av, int ac, int i)
{
	t_list	*curr;

	curr = NULL;
	while (i < ac)
	{
		curr = add_node(curr, av[i], av[i]);
		i++;
	}
	
	while (curr->prev)
		curr = curr->prev;
	merge_sort(&curr, hi->flags);
	hi->args = curr;
}

int		main(int ac, char **av)
{
	t_list		**all;
	t_arg		*hi;
	int			i;
	
	i = 1;
	init_arg(&hi);
	if (ac > 1)
		parse(&i, av, &hi->flags);
	sort_args(hi, av, ac, i);
	hi->nb_args = (ac - i > 0) ? ac - i : 1;
	if (i == ac)
		ft_ls(hi, ".");
	while (i < ac)
	{
		ft_ls(hi, hi->args->name);
		if (++i < ac)
			ft_printf("\n");
		hi->args = hi->args->next;
	}
	return (0);
}


