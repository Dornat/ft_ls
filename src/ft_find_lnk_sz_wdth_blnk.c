/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_lnk_sz_wdth_blnk.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:50:15 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 13:52:33 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned int			ft_find_link_width(t_list *ptr, char *path, \
						t_flags *ls_flags)
{
	unsigned int	link_width;

	link_width = 0;
	while (ptr)
	{
		if (ls_flags->lit_a)
		{
			if (ft_count_dgts(ft_nlinks(ptr->content, path)) > link_width)
				link_width = ft_count_dgts(ft_nlinks(ptr->content, path));
		}
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
				&& ft_strcmp(ptr->content, ".."))
		{
			if (ft_count_dgts(ft_nlinks(ptr->content, path)) > link_width)
				link_width = ft_count_dgts(ft_nlinks(ptr->content, path));
		}
		else if (((char*)ptr->content)[0] != '.')
		{
			if (ft_count_dgts(ft_nlinks(ptr->content, path)) > link_width)
				link_width = ft_count_dgts(ft_nlinks(ptr->content, path));
		}
		ptr = ptr->next;
	}
	return (link_width);
}

unsigned int			ft_find_size_width(t_list *ptr, char *path, \
						t_flags *ls_flags)
{
	unsigned int	size_width;

	size_width = 0;
	while (ptr)
	{
		if (ls_flags->lit_a)
		{
			if (ft_count_dgts(ft_fsize(ptr->content, path)) > size_width)
				size_width = ft_count_dgts(ft_fsize(ptr->content, path));
		}
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
				&& ft_strcmp(ptr->content, ".."))
		{
			if (ft_count_dgts(ft_fsize(ptr->content, path)) > size_width)
				size_width = ft_count_dgts(ft_fsize(ptr->content, path));
		}
		else if (((char*)ptr->content)[0] != '.')
		{
			if (ft_count_dgts(ft_fsize(ptr->content, path)) > size_width)
				size_width = ft_count_dgts(ft_fsize(ptr->content, path));
		}
		ptr = ptr->next;
	}
	return (size_width);
}

static unsigned int		ft_fblkn(char *file, char *path)
{
	struct stat		res;
	unsigned int	num;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	if (lstat(new_path, &res) == -1)
	{
		ft_strdel(&new_path);
		return (0);
	}
	num = res.st_blocks;
	ft_strdel(&new_path);
	return (num);
}

unsigned int			ft_find_block_num(t_list *ptr, char *path, \
						t_flags *ls_flags)
{
	unsigned int	blk;

	blk = 0;
	while (ptr)
	{
		if (ls_flags->lit_a)
			blk = blk + ft_fblkn(ptr->content, path);
		else if (ls_flags->big_a && ft_strcmp(ptr->content, ".") \
				&& ft_strcmp(ptr->content, ".."))
			blk = blk + ft_fblkn(ptr->content, path);
		else if (((char*)ptr->content)[0] != '.')
			blk = blk + ft_fblkn(ptr->content, path);
		ptr = ptr->next;
	}
	return (blk);
}
