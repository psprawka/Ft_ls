/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:32:01 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/22 10:28:36 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** SIZE_BUFF = file type + permissions + time  + ...
*/
#define SIZE_BUFF 1 + 9 + 12 + 1024

static void get_permission(t_data *f_data, char *str)
{
    ft_strcat(str, f_data->stat->st_mode & S_IRUSR ? "r" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IWUSR ? "w" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IXUSR ? "x" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IRGRP ? "r" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IWGRP ? "w" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IXGRP ? "x" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IROTH ? "r" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IWOTH ? "w" : "-");
    ft_strcat(str, f_data->stat->st_mode & S_IXOTH ? "x" : "-");
}

static void get_filetype(t_data *f_data, char *str)
{
    char *type;
    
	if (S_ISREG(f_data->stat->st_mode))
		type = "-";
	else if (S_ISDIR(f_data->stat->st_mode))
		type = "d";
	else if (S_ISCHR(f_data->stat->st_mode))
		type = "c";
	else if (S_ISBLK(f_data->stat->st_mode))
		type = "b";
	else if (S_ISFIFO(f_data->stat->st_mode))
		type = "p";
	else if (S_ISLNK(f_data->stat->st_mode))
		type = "l";
	else if (S_ISSOCK(f_data->stat->st_mode))
		type = "s";
    
    ft_bzero(str, SIZE_BUFF);
    ft_strcpy(str, type);
}

static void get_time(t_data *f_data, char *str)
{
	char *time;
	
	time = ctime(&(f_data->time->tv_sec));
    time[4 + 12] = '\0';
    ft_strcat(str, time + 4);
}

int         calculate_total_size(t_dnode *head)
{
    t_data	*tmp_data;
    int     total_size;
   
	total_size = 0;
	while (head)
	{
        tmp_data = head->data;
		total_size += tmp_data->stat->st_blocks;
		head = head->next;
	}
	return (total_size);
}

int         print_long(t_info *info, t_data *f_data)
{
    struct group	*grp;
	struct passwd	*pwd;
    char			tmp[SIZE_BUFF];

    grp = getgrgid(f_data->stat->st_gid);
	pwd = getpwuid(f_data->stat->st_uid);
    
    get_filetype(f_data, tmp);
    get_permission(f_data, tmp);
    ft_strcat(tmp, " ");
    ft_strcat(tmp, ft_itoa(f_data->stat->st_nlink));
    ft_strcat(tmp, " ");
    ft_strcat(tmp, pwd->pw_name);
    ft_strcat(tmp, " ");
    ft_strcat(tmp, grp->gr_name);
    ft_strcat(tmp, " "); //may be "  " on labs comp
    ft_strcat(tmp, ft_itoa(f_data->stat->st_size));
    ft_strcat(tmp, " ");
    get_time(f_data, tmp);
    ft_strcat(tmp, " ");
    ft_strcat(tmp, f_data->name);
    printf("%s\n", tmp);
    
    return (EXIT_SUCCESS);
}