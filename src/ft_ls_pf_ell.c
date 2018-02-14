/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_pf_ell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 10:51:17 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 16:22:55 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_lnk_file(char *file, char *path)
{
	char			*buf;
	char			*new_path;

	new_path = NULL;
	buf = NULL;
	buf = ft_strnew(256);
	new_path = ft_strjoin(path, file);
	readlink(new_path, buf, 256);
	ft_printf(" -> %s\n", buf);
	ft_strdel(&new_path);
	ft_strdel(&buf);
}

int		ft_is_maj_min(char *file, char *path)
{
	char			*new_path;
	struct stat		res;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return (0);
	}
	if (S_ISCHR(res.st_mode) || S_ISBLK(res.st_mode))
	{
		ft_strdel(&new_path);
		return (1);
	}
	else
	{
		ft_strdel(&new_path);
		return (0);
	}
}

void	ft_ls_pf_norm_file(char *file, t_finfo *f_info, t_width *ls_width)
{
	ft_printf("%c%s%c %*d %-*s  %-*s  %*d %s %s", f_info->ftype, \
	f_info->fperms, f_info->attr, ls_width->link_width, f_info->fnlinks, \
	ls_width->own_width, f_info->fowner, ls_width->grp_width, f_info->fgroup, \
	ls_width->size_width, f_info->fsize, f_info->flmdate_s, file);
}

void	ft_ls_pf_mm_file(char *file, t_finfo *f_info, t_width *ls_width)
{
	ft_printf("%c%s%c %*d %-*s  %-*s   %*d, %*d %s %s", f_info->ftype, \
	f_info->fperms, f_info->attr, ls_width->link_width, f_info->fnlinks, \
	ls_width->own_width, f_info->fowner, ls_width->grp_width, f_info->fgroup, \
	ls_width->maj_width, f_info->major, ls_width->min_width, f_info->minor, \
	f_info->flmdate_s, file);
}

void	ft_ls_pf_ell(char *file, char *path, t_width *ls_width)
{
	t_finfo			f_info;
	int				flag;

	flag = 0;
	ft_ftype(file, path, &f_info);
	ft_fpermissions(file, path, &f_info);
	f_info.fnlinks = ft_nlinks(file, path);
	ft_fowner(file, path, &f_info);
	if (ft_is_maj_min(file, path))
	{
		f_info.major = ft_fmajor(file, path);
		f_info.minor = ft_fminor(file, path);
		flag = 1;
	}
	else
		f_info.fsize = ft_fsize(file, path);
	ft_fgroup(file, path, &f_info);
	f_info.flmdate_s = ft_flmdate_s(file, path);
	f_info.attr = ft_fattr(file, path);
	if (!flag)
		ft_ls_pf_norm_file(file, &f_info, ls_width);
	else
		ft_ls_pf_mm_file(file, &f_info, ls_width);
	ft_fislink(file, path) ? ft_print_lnk_file(file, path) : write(1, "\n", 1);
	ft_strdel(&f_info.flmdate_s);
}
