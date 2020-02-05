/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:12:43 by psprawka          #+#    #+#             */
/*   Updated: 2020/01/11 23:48:42 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// int		file_exists(char *path)
// {
// 	struct stat		info;
	
// 	lstat(path, &info);
	
// 	if (S_ISREG(info.st_mode) || S_ISDIR(info.st_mode) ||
// 		S_ISCHR(info.st_mode) || S_ISBLK(info.st_mode) ||
// 		S_ISFIFO(info.st_mode) || S_ISLNK(info.st_mode) ||
// 		S_ISSOCK(info.st_mode))
// 		return (EXIT_SUCCESS);
// 	ft_error(1, path);
// 	return (EXIT_FAILURE)
// }
