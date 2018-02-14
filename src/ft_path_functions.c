/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:02:48 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 13:22:47 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*ft_put_slash(char *path)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (path[i])
		i++;
	i--;
	if (i || path[i] == '.' || path[i])
	{
		if (!ft_strcmp(path, "/"))
			res = ft_strdup("/");
		else
			res = ft_strjoin(path, "/");
		if (!ft_strcmp(path, "."))
			ft_strdel(&path);
	}
	else
		res = ft_strdup("/");
	return (res);
}

char	*ft_append_to_path(char *path, char *name)
{
	char	*to_free;

	to_free = path;
	path = ft_strjoin(path, name);
	ft_strdel(&to_free);
	return (path);
}

void	ft_trim_path(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	while (path[i] != '/' && i >= 0)
	{
		path[i] = '\0';
		i--;
	}
}
