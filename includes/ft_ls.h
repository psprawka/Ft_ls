/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:37:13 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/28 18:39:39 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <stdbool.h>
# include "libft.h"

# define FLAG_a 1	//00000001
# define FLAG_l 2	//00000010
# define FLAG_r 4	//00000100
# define FLAG_R 8	//00001000
# define FLAG_t 16	//00010000
# define FLAG_A 32	//00100000
# define FLAG_i 64	//01000000
# define FLAG_G 128	//10000000

typedef struct	s_data
{
	char			*path;
	char			*name;
	struct stat		*stat;
	struct timespec	*time;
	t_dnode			*sub;
}				t_data;

typedef struct	s_info
{
	int				flags;
	char			*path;
	t_dnode			*args;
	int				args_nb;
	int				left_args_nb;
}				t_info;

typedef struct	s_flags
{
	char	flag;
	int		flag_value;
}				t_flags;


/*
**	ft_ls_print.c
*/
int		print_files(t_info *info);
int		print_directories(t_info *info, t_dnode *head, char *path);

/*
**	ft_ls_parse.c
*/
int		parse_args(t_info *info, char **av, int ac);

/*
**	ft_ls_sort.c
*/
int		merge_sort_ls(t_dnode **head, int flags);


/*
**	ft_ls_tools.c
*/
t_data	*alloc_data(char *arg_name, char *path_name);
bool	if_process_file(t_info *info, char *filename);
void	ft_error(int nb, char *arg1, char arg2);
char	*path_builder(char *path, char *name);
int		sort_args(t_info *info, char **av, int ac);

/*
 **	ft_ls_print_long.c
 */
int		print_long(t_info *info, t_data *f_data);
int		calculate_total_size(t_dnode *head);

#endif

