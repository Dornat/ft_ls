/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftplos_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:15:01 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 14:22:35 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			ft_ftype(char *file, char *path, t_finfo *f_info)
{
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) != -1)
	{
		if (S_ISREG(res.st_mode))
			f_info->ftype = '-';
		else if (S_ISCHR(res.st_mode))
			f_info->ftype = 'c';
		else if (S_ISDIR(res.st_mode))
			f_info->ftype = 'd';
		else if (S_ISBLK(res.st_mode))
			f_info->ftype = 'b';
		else if (S_ISLNK(res.st_mode))
			f_info->ftype = 'l';
		else if (S_ISSOCK(res.st_mode))
			f_info->ftype = 's';
		else if (S_ISFIFO(res.st_mode))
			f_info->ftype = 'p';
	}
	else
		f_info->ftype = '\0';
	ft_strdel(&new_path);
}

void			ft_fpermissions(char *file, char *path, t_finfo *f_info)
{
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) != -1)
	{
		f_info->fperms[0] = (res.st_mode & R_OWN) ? 'r' : '-';
		f_info->fperms[3] = (res.st_mode & R_GRP) ? 'r' : '-';
		f_info->fperms[6] = (res.st_mode & R_OTH) ? 'r' : '-';
		f_info->fperms[1] = (res.st_mode & W_OWN) ? 'w' : '-';
		f_info->fperms[4] = (res.st_mode & W_GRP) ? 'w' : '-';
		f_info->fperms[7] = (res.st_mode & W_OTH) ? 'w' : '-';
		f_info->fperms[2] = (res.st_mode & X_OWN) ? 'x' : '-';
		if (res.st_mode & S_ISUID)
			f_info->fperms[2] = (res.st_mode & S_IXUSR) ? 's' : 'S';
		f_info->fperms[5] = (res.st_mode & X_GRP) ? 'x' : '-';
		if (res.st_mode & S_ISGID)
			f_info->fperms[5] = (res.st_mode & S_IXGRP) ? 's' : 'S';
		f_info->fperms[8] = (res.st_mode & X_OTH) ? 'x' : '-';
		if (res.st_mode & S_ISVTX)
			f_info->fperms[8] = (res.st_mode & S_IXOTH) ? 't' : 'T';
		f_info->fperms[9] = '\0';
	}
	ft_strdel(&new_path);
}

unsigned int	ft_nlinks(char *file, char *path)
{
	struct stat		res;
	unsigned int	num;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return (0);
	}
	num = res.st_nlink;
	ft_strdel(&new_path);
	return (num);
}

void			ft_fowner(char *file, char *path, t_finfo *f_info)
{
	struct stat		res;
	struct passwd	*pw;
	char			*new_path;

	ft_memset(f_info->fowner, '\0', 33);
	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return ;
	}
	pw = getpwuid(res.st_uid);
	ft_strcpy(f_info->fowner, pw->pw_name);
	ft_strdel(&new_path);
}

unsigned int	ft_fsize(char *file, char *path)
{
	struct stat		res;
	unsigned int	num;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return (0);
	}
	num = res.st_size;
	ft_strdel(&new_path);
	return (num);
}
