/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:04:51 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/19 13:04:56 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*	ft_strcmp function compares two strings based on ascii order, therefore:
**		-> if s1 > s2 in ascii returned number will be negative,
**		-> if s1 < s2 in ascii returned number will be posotive,
 **		-> if s1 == s2 (strings have the same length), function wil return 0;
*/

int		ftt_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (!s1[i] && s2[i])
		return (s2[i] * -1);
	if (!s2[i] && s1[i])
		return (s1[i]);
	return (0);
}

int			sort_time(t_list *a, t_list *b)
{
	long diff;
	long ndiff;

	diff = a->time.tv_sec - b->time.tv_sec;
	if (!diff)
	{
		ndiff = a->time.tv_nsec - b->time.tv_nsec;
		if (!ndiff)
			return (1);
		return (ndiff >= 0 ? 1: 0);
	}
	return (diff >= 0 ? 1 : 0);
}


void	split_list(t_list *head, t_list **front, t_list **end)
{
	t_list *slow;
	t_list *fast;

	slow = head;
	fast = slow->next;
	
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = head;
	*end = slow->next;
	slow->next = NULL;
}

t_list	*sorted_merge(t_list *a, t_list *b, int flags)
{
	t_list *res;

	res = NULL;
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	
	if ((flags & FLAG_t && sort_time(a, b))
		|| (!(flags & FLAG_t) && ftt_strcmp(a->name, b->name) <= 0))
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

void	merge_sort(t_list **head, int flags)
{
	t_list *ptr;
	t_list *a;
	t_list *b;

	ptr = *head;
	if (ptr == NULL || ptr->next == NULL)
		return ;
	split_list(ptr, &a, &b);
	merge_sort(&a, flags);
	merge_sort(&b, flags);
	*head = sorted_merge(a, b, flags);
	
	ptr = *head;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (ptr->sub != NULL)
			merge_sort(&(ptr->sub), flags);
		ptr = ptr->next;
	}
}

