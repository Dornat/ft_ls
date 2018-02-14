/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fgda_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:17:23 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:47:12 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_fgroup(char *file, char *path, t_finfo *f_info)
{
	struct stat		res;
	struct group	*gr;
	char			*new_path;

	ft_memset(f_info->fgroup, '\0', 33);
	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return ;
	}
	gr = getgrgid(res.st_gid);
	ft_strcpy(f_info->fgroup, gr->gr_name);
	ft_strdel(&new_path);
}

char	*ft_flmdate_sif(char *ftime)
{
	char	*res_tofree;
	char	*res;
	char	*year;
	int		ylen;

	res_tofree = ft_strnew(7);
	ft_memmove(res_tofree, ftime + 4, 7);
	ylen = ft_strlen(ft_strrchr(ftime, ' '));
	year = ft_strdup(ft_strrchr(ftime, ' '));
	year[ylen - 1] = '\0';
	res = ft_strjoin(res_tofree, year);
	ft_strdel(&res_tofree);
	ft_strdel(&year);
	return (res);
}

char	*ft_flmdate_s(char *file, char *path)
{
	char			*ftime;
	struct stat		res;
	char			*new_path;
	char			*t_res;
	time_t			c_time;

	new_path = ft_strjoin(path, file);
	t_res = NULL;
	lstat(new_path, &res);
	c_time = time(NULL);
	ftime = ctime(&res.st_mtime);
	if (((int)c_time - res.st_mtime > 13046400) || \
		((int)c_time - res.st_mtime < 0))
		t_res = ft_flmdate_sif(ftime);
	else
	{
		t_res = ft_strnew(12);
		ft_memmove(t_res, ftime + 4, 12);
	}
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
