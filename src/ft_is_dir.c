/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:08:18 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 18:43:38 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_is_dir_wo_path(char *name)
{
	struct stat		res;

	lstat(name, &res);
	if (S_ISDIR(res.st_mode))
		return (1);
	return (0);
}

int		ft_is_dir(char *name, char *path)
{
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, name);
	lstat(new_path, &res);
	if (S_ISDIR(res.st_mode))
	{
		ft_strdel(&new_path);
		return (1);
	}
	ft_strdel(&new_path);
	return (0);
}
