/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:37:13 by psprawka          #+#    #+#             */
/*   Updated: 2017/12/29 13:37:17 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"

# define FLAG_a 1
# define FLAG_l 10
# define FLAG_r 11
# define FLAG_R 100
# define FLAG_t 101

typedef struct	s_list
{
	char			*path;
	char			*name;
	struct stat		info;
	struct	s_list	*sub;
	struct	s_list	*next;
	struct	s_list	*prev;
}				t_list;



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
**
**
**
**
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

#endif

