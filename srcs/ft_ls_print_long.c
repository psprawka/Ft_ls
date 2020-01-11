/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:32:01 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/11 01:21:00 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define MODE_PERM	INFO->st_mode

char	*get_permission(t_list *ptr)
{
	char	*perm;

	perm = ft_strnew(1);
	perm = MODE_PERM & S_IRUSR ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IWUSR ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IXUSR ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IRGRP ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IWGRP ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IXGRP ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IROTH ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IWOTH ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = MODE_PERM & S_IXOTH ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	return (perm);
}

char	filetype(t_list *ptr)
{
	if (S_ISREG(ptr->info->st_mode))
		return ('-');
	if (S_ISDIR(ptr->info->st_mode))
		return ('d');
	if (S_ISCHR(ptr->info->st_mode))
		return ('c');
	if (S_ISBLK(ptr->info->st_mode))
		return ('b');
	if (S_ISFIFO(ptr->info->st_mode))
		return ('p');
	if (S_ISLNK(ptr->info->st_mode))
		return ('l');
	if (S_ISSOCK(ptr->info->st_mode))
		return ('s');
	return ('\0');
}

char	*get_time(t_list *ptr)
{
	char *res;
	char *time;
	
	res = ft_strnew(32);
	time = ctime(&(ptr->time.tv_sec));
	res = ft_strncat(res, time + 4, 12);
	return (res);
}

int		get_total(t_list *head, int size, int *spaces)
{
	t_list	*ptr;
	int		i;

	i = 1;
	*spaces = 0;
	ptr = head;
	if (ptr == NULL)
		return (size);
	*spaces = ptr->info->st_size;
	while (ptr)
	{
		size += ptr->info->st_blocks;
		if (*spaces < ptr->info->st_size)
			*spaces = ptr->info->st_size;
		ptr = ptr->next;
	}
	while (*spaces != 0 && i++)
		*spaces /= 10;
	*spaces = i < 2 ? 2 : i;
	return (size);
}

void	print_long(t_list *ptr, int spaces)
{
	char			*tmp;
	struct group	*grp;
	struct passwd	*pwd;

	grp = getgrgid(INFO->st_gid);
	pwd = getpwuid(INFO->st_uid);
	tmp = get_permission(ptr);
	ft_printf("%c%s", filetype(ptr), tmp);
	//	free(tmp);
	
	tmp = ft_strnew(1024);
	listxattr(bulid_path(ptr->path, ptr->name), tmp, 1024, XATTR_NOFOLLOW) ?
	ft_printf("@") : ft_printf(" ");
	//	free(tmp);
	
	tmp = get_time(ptr);
	ft_printf(" %d %s  %s %*lld %s %s\n", INFO->st_nlink, pwd->pw_name,
			  grp->gr_name, spaces, INFO->st_size, tmp, ptr->name);
	//	free(tmp);
}
