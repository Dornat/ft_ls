/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_files_in_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:49:12 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/07 20:56:12 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_sort_files_in_dir(t_list **files, t_flags *ls_flags)
{
	if (ls_flags->lit_f)
		return ;
	else if (ls_flags->lit_t && ls_flags->lit_r)
	{
		ft_lst_merge_sort_t(files);
		ft_lstrev(files);
	}
	else if (ls_flags->lit_t)
		ft_lst_merge_sort_t(files);
	else if (ls_flags->lit_r)
		ft_lst_merge_sort_r(files);
	else
		ft_lst_merge_sort(files);
}
