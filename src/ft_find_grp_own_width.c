/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_grp_own_width.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:48:00 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 12:58:12 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_fow_len(char *file, char *path, unsigned int *ow)
{
	unsigned int	len;
	t_finfo			f_info;

	ft_fowner(file, path, &f_info);
	len = ft_strlen(f_info.fowner);
	if (len > *ow)
		*ow = len;
}

unsigned int	ft_find_own_width(t_list *ptr, char *path, t_flags *ls_flags)
{
	unsigned int	ow;

	ow = 0;
	while (ptr)
	{
		if (ls_flags->lit_a)
			ft_fow_len(ptr->content, path, &ow);
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
				&& ft_strcmp(ptr->content, ".."))
			ft_fow_len(ptr->content, path, &ow);
		else if (ft_strcmp(ptr->content, ".") && ft_strcmp(ptr->content, "..") \
				&& ((char*)ptr->content)[0] != '.')
			ft_fow_len(ptr->content, path, &ow);
		ptr = ptr->next;
	}
	return (ow);
}

static void		ft_fgrp_len(char *file, char *path, unsigned int *grp)
{
	unsigned int	len;
	t_finfo			f_info;

	ft_fgroup(file, path, &f_info);
	len = ft_strlen(f_info.fgroup);
	if (len > *grp)
		*grp = len;
}

unsigned int	ft_find_grp_width(t_list *ptr, char *path, t_flags *ls_flags)
{
	unsigned int	grp;

	grp = 0;
	while (ptr)
	{
		if (ls_flags->lit_a)
			ft_fgrp_len(ptr->content, path, &grp);
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
				&& ft_strcmp(ptr->content, ".."))
			ft_fgrp_len(ptr->content, path, &grp);
		else if (ft_strcmp(ptr->content, ".") && ft_strcmp(ptr->content, "..") \
				&& ((char*)ptr->content)[0] != '.')
			ft_fgrp_len(ptr->content, path, &grp);
		ptr = ptr->next;
	}
	return (grp);
}
