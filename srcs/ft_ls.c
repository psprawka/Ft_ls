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

void	ls(t_arg *all, char *path)
{
	*FILES = NULL;
	*FILES = create_list(*FILES, ft_strdup(path), NULL, FLAGS);
	merge_sort(FILES, FLAGS);
	if (FLAGS & FLAG_r)
		all->args == 1  || *FILES == NULL ? print_path_r(*FILES, FLAGS, path)
			: print_path_r(*FILES, FLAGS, NULL);
	else
		all->args == 1  || *FILES == NULL ? print_path(*FILES, FLAGS, path)
			: print_path(*FILES, FLAGS, NULL);
	if (*FILES != NULL)
		free(*FILES);
	
}


int		main(int ac, char **av)
{
	t_list		**all;
	t_arg		*hi;
	int			i;
	
	i = 1;
	hi = (t_arg *)malloc(sizeof(t_arg));
	hi->all = (t_list **)malloc(sizeof(t_list *));
	hi->flags = 0;
	if (ac > 1)
		parse(&i, av, &hi->flags);
	hi->args = ac - i;
	if (i == ac)
	{
		hi->args = 1;
		ls (hi, ".");
	}
	while (i < ac)
	{
		ls(hi, av[i]);
		i++;
		if (i < ac)
			ft_printf("\n");
	}

	return (0);
}


