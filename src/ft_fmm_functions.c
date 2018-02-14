/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmm_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:47:04 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:47:23 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
