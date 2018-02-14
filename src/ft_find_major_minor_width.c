/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_major_minor_width.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:04:47 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/12 15:48:59 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned int	ft_find_maj_width(t_list *ptr, char *path, t_flags *ls_flags)
{
	unsigned int	maj_width;

	maj_width = 0;
	while (ptr)
	{
		if (ls_flags->lit_a && ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fmajor(ptr->content, path)) > maj_width)
				maj_width = ft_count_dgts(ft_fmajor(ptr->content, path));
		}
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
		&& ft_strcmp(ptr->content, "..") && ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fmajor(ptr->content, path)) > maj_width)
				maj_width = ft_count_dgts(ft_fmajor(ptr->content, path));
		}
		else if (((char*)ptr->content)[0] != '.' && \
				ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fmajor(ptr->content, path)) > maj_width)
				maj_width = ft_count_dgts(ft_fmajor(ptr->content, path));
		}
		ptr = ptr->next;
	}
	return (maj_width);
}

unsigned int	ft_find_min_width(t_list *ptr, char *path, t_flags *ls_flags)
{
	unsigned int	min_width;

	min_width = 0;
	while (ptr)
	{
		if (ls_flags->lit_a && ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fminor(ptr->content, path)) > min_width)
				min_width = ft_count_dgts(ft_fminor(ptr->content, path));
		}
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
		&& ft_strcmp(ptr->content, "..") && ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fminor(ptr->content, path)) > min_width)
				min_width = ft_count_dgts(ft_fminor(ptr->content, path));
		}
		else if (((char*)ptr->content)[0] != '.' && \
				ft_is_maj_min(ptr->content, path))
		{
			if (ft_count_dgts(ft_fminor(ptr->content, path)) > min_width)
				min_width = ft_count_dgts(ft_fminor(ptr->content, path));
		}
		ptr = ptr->next;
	}
	return (min_width < 3 && min_width ? min_width = 3 : min_width);
}
