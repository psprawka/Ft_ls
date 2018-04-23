/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:57:40 by psprawka          #+#    #+#             */
/*   Updated: 2018/04/18 22:57:42 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_permission(t_list *ptr)
{
	char	*perm;
	
	perm = ft_strnew(1);
	perm = INFO->st_mode & S_IRUSR ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IWUSR ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IXUSR ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IRGRP ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IWGRP ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IXGRP ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IROTH ? ft_strjoin(perm, "r") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IWOTH ? ft_strjoin(perm, "w") : ft_strjoin(perm, "-");
	perm = INFO->st_mode & S_IXOTH ? ft_strjoin(perm, "x") : ft_strjoin(perm, "-");
	
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

void	print_long(t_list *ptr)
{
	char			*perm;
	char			*time;
	struct group	*grp;
	struct passwd	*pwd;
	char			buf[1024];
	
	perm = get_permission(ptr);
	time = get_time(ptr);
	grp = getgrgid(INFO->st_gid);
	pwd = getpwuid(INFO->st_uid);
	ft_printf("%c%s", filetype(ptr), perm);
	listxattr(bulid_path(ptr->path, ptr->name), buf, 1024, XATTR_NOFOLLOW) ?
		ft_printf("@") : ft_printf(" ");
	
	
	ft_printf(" %d %s  %s  %lld %s %s\n", INFO->st_nlink, pwd->pw_name, grp->gr_name, INFO->st_size, time, ptr->name);
//	free(time);
//	free(perm);
}


void	print_path_r(t_list *all, int flags, char *path)
{
	t_list	*ptr;
	
	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (ptr && ptr->prev != NULL)
	{
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr);
		ptr = ptr->prev;
	}
	if (ptr)
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr);
	ptr = all;
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (flags & FLAG_R && ptr != NULL)
	{

		if (S_ISDIR(ptr->info->st_mode) && ft_printf("\n"))
			ptr->sub ? print_path_r(ptr->sub, flags, path) :
			print_path_r(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
		ptr = ptr->prev;
	}
}

int		get_total(char *path)
{
	struct stat info;
	printf("path %s\n", path);
	stat(path, &info);
	return (info.st_blocks);
}


void	print_path(t_list *all, int flags, char *path)
{
	t_list	*ptr;

	ptr = all;
	if (path == NULL || !ptr || (ptr && ft_strcmp(ptr->path, path)))
		!ptr ? ft_printf("%s:\n", path) : ft_printf("%s:\n", ptr->path);
	if (flags & FLAG_l)
		ft_printf("total %d\n", get_total(path));
	while (ptr && ptr->next != NULL)
	{
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr);
		ptr = ptr->next;
	}
	if (ptr)
		!(flags & FLAG_l) ? ft_printf("%s\n", ptr->name) : print_long(ptr);
	ptr = all;
	while (flags & FLAG_R && ptr != NULL)
	{
		if (S_ISDIR(ptr->info->st_mode) && ft_printf("\n"))
			ptr->sub ? print_path(ptr->sub, flags, path) :
			print_path(ptr->sub, flags, bulid_path(ptr->path, ptr->name));
		ptr = ptr->next;
	}
}
