/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_favtolst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:38:40 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:49:22 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				ft_is_finav(t_list *names, t_flags *ls_flags)
{
	t_list			*ptr;
	int				i;
	struct stat		res;

	ptr = names;
	i = 0;
	while (ptr)
	{
		if (lstat(ptr->content, &res) != -1)
		{
			if (S_ISLNK(res.st_mode))
			{
				if (ft_chk_lnk_ptr_to_dir(ptr->content, ls_flags))
					;
				else
					i++;
			}
			else if (S_ISREG(res.st_mode) || S_ISCHR(res.st_mode) || \
				S_ISBLK(res.st_mode) || S_ISSOCK(res.st_mode) || \
				S_ISFIFO(res.st_mode))
				i++;
		}
		ptr = ptr->next;
	}
	return (i);
}

int				ft_chk_lnk_ptr_to_dir(char *path, t_flags *ls_flags)
{
	char			*buf;
	struct stat		res;
	int				len;

	buf = ft_strnew(256);
	readlink(path, buf, 256);
	len = ft_strlen(path) - 1;
	if (lstat(buf, &res) != -1)
	{
		if (S_ISDIR(res.st_mode) && (path[len] == '/' || !ls_flags->lit_ell))
		{
			ft_strdel(&buf);
			return (1);
		}
	}
	ft_strdel(&buf);
	return (0);
}

static int		ft_is_fav(char *path, t_flags *ls_flags)
{
	struct stat		res;
	char			*new_path;

	new_path = ft_strdup(path);
	if (lstat(new_path, &res) != -1)
	{
		if (S_ISREG(res.st_mode) || S_ISCHR(res.st_mode) || \
			S_ISBLK(res.st_mode) || S_ISLNK(res.st_mode) || \
			S_ISSOCK(res.st_mode) || S_ISFIFO(res.st_mode))
		{
			if (S_ISLNK(res.st_mode))
			{
				if (ft_chk_lnk_ptr_to_dir(path, ls_flags))
				{
					ft_strdel(&new_path);
					return (0);
				}
			}
			ft_strdel(&new_path);
			return (1);
		}
	}
	ft_strdel(&new_path);
	return (0);
}

t_list			*ft_put_favtolst(t_list *ptr, t_flags *ls_flags)
{
	t_list		*newlst;
	t_list		*to_free;

	newlst = NULL;
	to_free = NULL;
	while (ptr)
	{
		if (ft_is_fav((char*)ptr->content, ls_flags))
		{
			if (!newlst)
				newlst = ft_lstnew(ptr->content, \
						ft_strlen((char*)ptr->content));
			else
			{
				to_free = ft_lstnew(ptr->content, \
						ft_strlen((char*)ptr->content));
				ft_lstadd_atend(&newlst, to_free);
			}
		}
		ptr = ptr->next;
	}
	return (newlst);
}
