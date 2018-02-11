/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:47:16 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 17:57:27 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t			ft_flmdate_i(char *file, char *path)
{
	size_t			time;
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	time = res.st_mtime;
	ft_strdel(&new_path);
	return (time);
}

void			ft_put_file_t(char *name, t_list **files, char *path)
{
	t_list		*tmp;

	tmp = NULL;
	if (!*files)
	{
		*files = ft_lstnew(name, ft_strlen(name));
		(*files)->content_size = ft_flmdate_i(name, path);
	}
	else
	{
		tmp = ft_lstnew(name, ft_strlen(name));
		tmp->content_size = ft_flmdate_i(name, path);
		ft_lstadd_atend(files, tmp);
	}
}

void			ft_put_file(char *name, t_list **files)
{
	t_list		*tmp;

	tmp = NULL;
	if (!*files)
		*files = ft_lstnew(name, ft_strlen(name));
	else
	{
		tmp = ft_lstnew(name, ft_strlen(name));
		ft_lstadd_atend(files, tmp);
	}
}
