/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftplos_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:15:01 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/09 10:18:59 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char			*ft_ftype(char *file, char *path)
{
	char			*s;
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	s = ft_strnew(1);
	if (S_ISREG(res.st_mode))
		ft_strcpy(s, "-");
	else if (S_ISCHR(res.st_mode))
		ft_strcpy(s, "c");
	else if (S_ISDIR(res.st_mode))
		ft_strcpy(s, "d");
	else if (S_ISBLK(res.st_mode))
		ft_strcpy(s, "b");
	else if (S_ISLNK(res.st_mode))
		ft_strcpy(s, "l");
	else if (S_ISSOCK(res.st_mode))
		ft_strcpy(s, "s");
	else if (S_ISFIFO(res.st_mode))
		ft_strcpy(s, "p");
	ft_strdel(&new_path);
	return (s);
}

char			*ft_fpermissions(char *file, char *path)
{
	char			*s;
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	s = ft_strdup("---------\0");
	lstat(new_path, &res);
	s[0] = (res.st_mode & R_OWN) ? 'r' : '-';
	s[3] = (res.st_mode & R_GRP) ? 'r' : '-';
	s[6] = (res.st_mode & R_OTH) ? 'r' : '-';
	s[1] = (res.st_mode & W_OWN) ? 'w' : '-';
	s[4] = (res.st_mode & W_GRP) ? 'w' : '-';
	s[7] = (res.st_mode & W_OTH) ? 'w' : '-';
	s[2] = (res.st_mode & X_OWN) ? 'x' : '-';
	if (res.st_mode & S_ISUID)
		s[2] = (res.st_mode & S_IXUSR) ? 's' : 'S';
	s[5] = (res.st_mode & X_GRP) ? 'x' : '-';
	if (res.st_mode & S_ISGID)
		s[5] = (res.st_mode & S_IXGRP) ? 's' : 'l';
	s[8] = (res.st_mode & X_OTH) ? 'x' : '-';
	if (res.st_mode & S_ISVTX)
		s[8] = (res.st_mode & S_IXOTH) ? 't' : 'T';
	ft_strdel(&new_path);
	return (s);
}

unsigned int	ft_nlinks(char *file, char *path)
{
	struct stat		res;
	unsigned int	num;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	num = res.st_nlink;
	ft_strdel(&new_path);
	return (num);
}

char			*ft_fowner(char *file, char *path)
{
	struct stat		res;
	struct passwd	*pw;
	char			*owner_name;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	pw = getpwuid(res.st_uid);
	owner_name = ft_strdup(pw->pw_name);
	ft_strdel(&new_path);
	return (owner_name);
}

unsigned int	ft_fsize(char *file, char *path)
{
	struct stat		res;
	unsigned int	num;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	num = res.st_size;
	ft_strdel(&new_path);
	return (num);
}
