/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:37:13 by psprawka          #+#    #+#             */
/*   Updated: 2020/03/22 16:38:42 by psprawka         ###   ########.fr       */
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

//maybe move them to struct to parse?
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
	struct stat		*stat; //former info
	struct timespec	*time;
	t_dnode			*sub;
}				t_data;

typedef struct	s_info
{
	int				flags;
	char			*path;
	t_dnode			*args;
	int				args_nb; //number of args without flags
	int				left_args_nb; //number of args without flags
}				t_info;

typedef struct	s_flags
{
	char	flag;
	int		flag_value;
}				t_flags;


/* 	------------------------- FUNCTIONS I USE IN FT_LS -------------------------
**
**	int lstat(const char *pathname, struct stat *statbuf):
**		- this function returns information about a file, in the buffer
**			pointed to by statbuf. Gets information about the file and if
**			pathname is a symbolic link, then it returns information about
**			the link itself, not the file that it refers to. On success,
**			zero is returned and on error -1 is returned.
**
**	DIR *opendir(const char *dirname):
**		- shall open a directory stream named in arguments, returns a pointer
**			to an object of type DIR or a null pointer in case of error.
**			This funtion seems to be like open() for files, besides it returns
**			pointer to an object instead of fd. DIR type represents a directory
**			stream.
**
**	struct dirent *readdir(DIR *dirp):
**		- this function returns a pointer to a structure representing
**			the directory entry at the current position in DIR *dirp and
**			positions the directory stream at the next entry. It returns
**			a null pointer at the end of DIR *dirp.
**
**	int closedir(DIR *dirp):
**		- the closedir() function shall close the directory stream referred
** 			to by the argument dirp.
*/
 
/*
**	------------------- EVERYTHING WHAT'S INSIDE STAT STRUCT -------------------
**
**	struct stat
**	{
**		dev_t     st_dev;		ID urządzenia zawierającego plik
**		ino_t     st_ino;		numer i-węzła (inode)
**		umode_t   st_mode;		ochrona
**		nlink_t   st_nlink;		liczba dowiązań stałych (hardlinks)
**		uid_t     st_uid;		ID użytkownika właściciela
**		gid_t     st_gid;		ID grupy właściciela
**		dev_t     st_rdev;		ID urządzenia (jeśli plik specjalny)
**		off_t     st_size;		całkowity rozmiar w bajtach
**		blksize_t st_blksize;	wielkość bloku dla I/O systemu plików
**		blkcnt_t  st_blocks;	liczba zaalokowanych bloków 512-bajtowych
**		time_t    st_atime;		czas ostatniego dostępu
**		time_t    st_mtime;		czas ostatniej modyfikacji
**		time_t    st_ctime;		czas ostatniej zmiany
**	};
**
**	Defined macros for st_mode:
**	-> S_IFREG		regular file
**	-> S_IFDIR		catalog
**	-> S_IFCHR		character device
**	-> S_IFBLK		block device
**	-> S_IFIFO		FIFO
**	-> S_IFLNK		symbolic link
**	-> S_IFSOCK		socket
**
*/


/*
**	----------------- EVERYTHING WHAT'S INSIDE DIRENT STRUCT -------------------
**
** struct dirent {
**      ino_t			d_ino;       	Inode number
**      off_t			d_off;       	Not an offset; see below
**      unsigned short	d_reclen;    	Length of this record
**      unsigned char 	d_type;      	Type of file
**		char			d_name[256]; 	Null-terminated filename
};
*/

/*
**	ft_ls_list.c
*/
// t_list	*create_list(t_list *curr, char *path, char *name, int flags);


/*
**	ft_ls_print.c
*/
int		print_files(t_info *info);
int		print_directories(t_info *info, t_dnode *head, char *path);

// void	print_path(t_list *all, int flags, char *path);
// void	print_path_r(t_list *all, int flags, char *path);


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

/*
 **	ft_ls_help.c
 */
// void	file_exists(char *path);

#endif

