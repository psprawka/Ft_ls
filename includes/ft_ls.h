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
**	-> S_ISREG		regular file
**	-> S_ISDIR		catalog
**	-> S_ISCHR		character device
**	-> S_ISBLK		block device
**	-> S_ISFIFO		FIFO
**	-> S_ISLNK		symbolic link
**	-> S_ISSOCK		socket
**
*/

typedef struct	s_list
{
	char	*path;
	char	*name;
	int		if_checked;
	struct	s_list	sub;
	struct	s_list	next;
}				t_list;


#endif

