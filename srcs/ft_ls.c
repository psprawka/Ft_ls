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
#include <stdio.h>


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

void	ft_error(int nb, char *name)
{
	if (nb == 1)
		ft_printf("ft_ls: %s: No such file or directory", name);
	exit(0);
}

t_list	*add_node(t_list *prev, char *name, char *path)
{
	t_list	*new;

//	if (prev) printf("prev %s || name %s\n", prev->name, name);
	new = (t_list *)malloc(sizeof(t_list));
	new->name = name;
	new->path = path;
	new->next = NULL;
	new->prev = NULL;
	new->sub = NULL;
	if (prev == NULL)
		prev = new;
	else
	{
		new->prev = prev;
		prev->next = new;
	}
	return (new);
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
	free(s1);
	return (path);
}

t_list	*create_list(t_list *curr, char *path)
{
	DIR 			*directory;
	struct dirent	*file;
	struct stat		info;
	char			*name;
	
	name = NULL;
	if ((directory = opendir(path)) == NULL)
		ft_error(1, path);
//	printf("%sNEW DIRECTORY: %s%s\n", PINK, path, NORMAL);
	while ((file = readdir(directory)) != NULL)
	{
		name = ft_strdup(path);
//		printf("here3\n");
		name = bulid_path(name, file->d_name);
//		printf("here1\n");
		curr = add_node(curr, file->d_name, name);
//		printf("here2\n");
//
//		printf("here4\n");
		lstat(name, &info);
//		printf("here5\n");
//		ft_printf("name [%s] IS_DIR: %d\n", name, S_ISDIR(info.st_mode));
		
		if (ft_strcmp(file->d_name, "..") && ft_strcmp(file->d_name, ".")
			&& S_ISDIR(info.st_mode))
//		{
			
			curr->sub = create_list(curr->sub, name);
//			printf("SUBDIR %p %s\n", &curr->sub, curr->sub->name);
//		}
		else
			curr->sub = NULL;
//		printf("here6\n");
		free(name);
	}
//	printf("leaving\n");
		closedir(directory);
	while (curr->prev != NULL)
		curr = curr->prev;
	return (curr);
//	printf("yo\n");
}

void	print_path(t_list *all)
{
	printf("%s -> NULL\n\n\n%sT:\n", all->name, YELLOW);
	while (all->next != NULL)
	{
		printf("%s -> ", all->name);
		all = all->next;
	}
	printf("%s -> NULL\n\n%s", all->name, NORMAL);
	
}

int		main(int ac, char **av)
{
	t_list		*all;
	int			i;
	int			flags;
	
	i = 1;
	all = NULL;
//	while (i < ac)
//	{
	
		all = create_list(all, ft_strdup(av[i]));
//		i++;
//	}
	print_path();
	return 0;
}


