/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fgda_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:17:23 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 12:09:21 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*ft_fgroup(char *file, char *path)
{
	struct stat		res;
	struct group	*gr;
	char			*group_name;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	gr = getgrgid(res.st_gid);
	group_name = ft_strdup(gr->gr_name);
	ft_strdel(&new_path);
	return (group_name);
}

char	*ft_flmdate_s(char *file, char *path)
{
	char			*ftime;
	struct stat		res;
	char			*new_path;
	char			*t_res;
	time_t			c_time;

	new_path = ft_strjoin(path, file);
	t_res = ft_strnew(12);
	lstat(new_path, &res);
	c_time = time(NULL);
	ftime = ctime(&res.st_mtime);
	if (((int)c_time - res.st_mtime > 13046400) || \
		((int)c_time - res.st_mtime < 0))
	{
		ft_memmove(t_res, ftime + 4, 7);
		ft_strncpy(t_res + 7, ftime + 19, 5);
	}
	else
		ft_memmove(t_res, ftime + 4, 12);
	ft_strdel(&new_path);
	return (t_res);
}

char	ft_fattr(char *file, char *path)
{
	char		at;
	ssize_t		xattr;
	char		*new_path;

	new_path = ft_strjoin(path, file);
	xattr = listxattr(new_path, NULL, 0, XATTR_NOFOLLOW);
	at = xattr > 0 ? '@' : ' ';
	ft_strdel(&new_path);
	return (at);
}

unsigned int	ft_fmajor(char *file, char *path)
{
	struct stat		res;
	unsigned int	maj;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	maj = major(res.st_rdev);
	ft_strdel(&new_path);
	return (maj);
}

unsigned int	ft_fminor(char *file, char *path)
{
	struct stat		res;
	unsigned int	min;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	min = minor(res.st_rdev);
	ft_strdel(&new_path);
	return (min);
}
