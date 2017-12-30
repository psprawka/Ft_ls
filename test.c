/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:18:08 by psprawka          #+#    #+#             */
/*   Updated: 2017/12/29 14:18:11 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


typedef struct	s_list
{
	char	*path;
	char	*name;
	int		if_checked;
	struct	s_list	sub;
	struct	s_list	next;
}				t_list;

void	ft_ls(DIR directory)
{
	struct dirent	*file;
	struct stat		info;
	char			rodzaj;
	t_list			**general list
	t_list
	
	while ((file = readdir(directory)) != NULL)
	{
		if (lstat(file->d_name, &info) == 0)
		{
			if (S_ISDIR(info.st_mode))
				rodzaj='D';
			else if (S_ISREG(info.st_mode))
				rodzaj='R';
			else if (S_ISLNK(info.st_mode))
				rodzaj='L';
			else if (S_ISFIFO(info.st_mode))
				rodzaj='F';
			else
				rodzaj='?';
			printf("%c -> %s\n", rodzaj, file->d_name);
		}
	}
}


int main(int argc, char* argv[])
{
	DIR		*directory;

	directory = opendir(".");
	if (directory == NULL)
	{
		printf("Nie moge otworzyc %s\n", argv[1]);
		perror("Komunikat systemu");
		return 1;
	}
	ft_ls(directory);
	closedir(directory);
	return 0;
}

//#include <unistd.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <errno.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <dirent.h>
//#include <string.h>
//
//void PrzetwarzajKatalog(const char *katalog, int poziom)
//{
//	int		i;
//	DIR		*kat;
//	struct	dirent *pozycja;
//	struct	stat info;
//	
////	if (chdir(katalog) != 0)
////		return; /* nie mozna zmienic katalogu - wychodzimy */
//	kat = opendir(".");
//	if (kat == NULL)
//		return; /* nie mozna otworzyc katalogu - wychodzimy */
//	while ((pozycja = readdir(kat)) != NULL)
//	{
//		if  (strcmp(pozycja->d_name, ".") == 0 || strcmp(pozycja->d_name, "..") == 0) continue;
//		if (stat(pozycja->d_name, &info) != 0)
//			continue; /* nie udal sie stat - pomijamy te pozycje */
////		if (! S_ISDIR(info.st_mode))
////			continue; /* to nie katalog - pomijamy te pozycje */
//		for (i = 1; i <= poziom-1; i++)
//			printf("| ");
//		printf("+-%s\n", pozycja->d_name);
//		/* wiemy juz, ze to nie . i nie .. */
//		PrzetwarzajKatalog(pozycja->d_name, poziom+1);
//	}
//	closedir(kat);
//	chdir("..");
//}
//
//
//int main(int argc, char* argv[])
//{
//	if (argc < 2)
//	{
//		printf("Podaj sciezke jako parametr\n");
//		return 1;
//	}
//	printf("%s\n", argv[1]);
//	PrzetwarzajKatalog(argv[1], 1);
//	return 0;
//}
