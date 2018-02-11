/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_files_in_dir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:20:47 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 16:29:42 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#define MAJ_MIN_OFFSET 3

static int		ft_count_files_in_dir(t_list *ptr, t_flags *ls_flags)
{
	int		i;

	i = 0;
	while (ptr)
	{
		if (ls_flags->big_a)
		{
			if (!ft_strcmp(ptr->content, ".") || \
				!ft_strcmp(ptr->content, ".."))
				;
			else
				i++;
		}
		else
		{
			if (((char*)ptr->content)[0] == '.')
				;
			else
				i++;
		}
		ptr = ptr->next;
	}
	return (i);
}

static void		ft_print_total(t_list *ptr, t_flags *ls_flags, \
				t_width *ls_width)
{
	if (ls_flags->lit_a)
		ft_printf("total %lu\n", ls_width->block_num);
	else if (ft_count_files_in_dir(ptr, ls_flags))
		ft_printf("total %lu\n", ls_width->block_num);
}

static void		ft_print_files_in_dir_ell(t_list *ptr, t_flags *ls_flags, \
				char *path, t_width *ls_width)
{
	ft_print_total(ptr, ls_flags, ls_width);
	while (ptr)
	{
		if (ls_flags->lit_a)
			ft_ls_pf_ell(ptr->content, path, ls_width);
		else if (ls_flags->big_a)
		{
			if (!ft_strcmp(ptr->content, ".") || \
				!ft_strcmp(ptr->content, ".."))
				;
			else
				ft_ls_pf_ell(ptr->content, path, ls_width);
		}
		else
		{
			if (((char*)ptr->content)[0] == '.')
				;
			else
				ft_ls_pf_ell(ptr->content, path, ls_width);
		}
		ptr = ptr->next;
	}
}

static void		ft_print_files_in_dir_raw(t_list *ptr, t_flags *ls_flags)
{
	while (ptr)
	{
		if (ls_flags->lit_a)
			ft_printf("%s\n", ptr->content);
		else if (ls_flags->big_a)
		{
			if (!ft_strcmp(ptr->content, ".") || \
				!ft_strcmp(ptr->content, ".."))
				;
			else
				ft_printf("%s\n", ptr->content);
		}
		else
		{
			if (((char*)ptr->content)[0] == '.')
				;
			else
				ft_printf("%s\n", ptr->content);
		}
		ptr = ptr->next;
	}
}

void			ft_print_files_in_dir(t_list *ptr, t_flags *ls_flags, \
				char *path)
{
	t_width		ls_width;

	ls_width.link_width = ft_find_link_width(ptr, path, ls_flags);
	ls_width.size_width = ft_find_size_width(ptr, path, ls_flags);
	ls_width.block_num = ft_find_block_num(ptr, path, ls_flags);
	ls_width.own_width = ft_find_own_width(ptr, path, ls_flags);
	ls_width.grp_width = ft_find_grp_width(ptr, path, ls_flags);
	ls_width.maj_width = ft_find_maj_width(ptr, path, ls_flags);
	ls_width.min_width = ft_find_min_width(ptr, path, ls_flags);
	if (ls_width.maj_width + ls_width.min_width > ls_width.size_width)
		ls_width.size_width = ls_width.maj_width + ls_width.min_width + \
																MAJ_MIN_OFFSET;
	if (ls_flags->lit_ell)
		ft_print_files_in_dir_ell(ptr, ls_flags, path, &ls_width);
	else
		ft_print_files_in_dir_raw(ptr, ls_flags);
}
