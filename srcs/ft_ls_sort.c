/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:04:51 by psprawka          #+#    #+#             */
/*   Updated: 2020/02/23 23:45:27 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
**	----------------------ENTIRE FILE TO FIX ----------------------------------
*/

/*	ft_strcmp function compares two strings based on ascii order, therefore:
**		-> if s1 > s2 in ascii returned number will be negative,
**		-> if s1 < s2 in ascii returned number will be positive,
 **		-> if s1 == s2 (strings have the same length), function wil return 0;
*/

int		ftt_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] && s2[i])
		return (s2[i] * -1);
	if (!s2[i] && s1[i])
		return (s1[i]);
	return (0);
}

int			sort_time(t_dnode *a, t_dnode *b)
{
	long diff;
	long ndiff;
    
    t_data *a_data, *b_data;

    a_data = a->data;
    b_data = b->data;
	diff = a_data->time->tv_sec - b_data->time->tv_sec;
	if (!diff)
	{
		ndiff = a_data->time->tv_nsec - b_data->time->tv_nsec;
		if (!ndiff)
			return (ft_strcmp(a_data->name, b_data->name) <= 0 ? 1 : 0);
		return (ndiff >= 0 ? 1: 0);
	}
	return (diff >= 0 ? 1 : 0);
}


void	split_list(t_dnode *head, t_dnode **a, t_dnode **b)
{
	t_dnode *slow;
	t_dnode *fast;

	slow = head;
	fast = head->next;
	
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

t_dnode	*sorted_merge(t_dnode *a, t_dnode *b, int flags)
{
	t_dnode *res;

	res = NULL;
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);

	if ((flags & FLAG_t && sort_time(a, b))
		|| (!(flags & FLAG_t) && ftt_strcmp(((t_data *)(a->data))->name, ((t_data *)(b->data))->name) <= 0))
	{
		res = a;
		res->next = sorted_merge(a->next, b, flags);
	}
	else
	{
		res = b;
		res->next = sorted_merge(a, b->next, flags);
	}
	res->next->prev = res;
	res->prev = NULL;
	return (res);
}

int		merge_sort_ls(t_dnode **head, int flags)
{
	t_dnode *ptr;
	t_dnode *a = NULL;
	t_dnode *b = NULL;

	ptr = *head;
	if (ptr && ptr->next)
	{
		split_list(ptr, &a, &b);
		merge_sort_ls(&a, flags);
		merge_sort_ls(&b, flags);
		*head = sorted_merge(a, b, flags);
	}
	
	ptr = *head;
	//printf("hm?\n");
	while (ptr != NULL)
	{
        t_data *data;
        
        data = ptr->data;
		if (data->sub != NULL)
			merge_sort_ls(&(data->sub), flags);
		ptr = ptr->next;
	}
    return EXIT_SUCCESS;
}

int		sort_args(t_info *info, char **av, int ac)
{	
	merge_sort_ls(&(info->args), info->flags);
	return (EXIT_SUCCESS);
}
