/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_deal_with_favs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:34:26 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:59:35 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_ls_pf_favs_l(char *fav, t_width *ls_width)
{
	t_finfo			f_info;
	int				flag;

	flag = 0;
	ft_ftype(fav, "", &f_info);
	ft_fpermissions(fav, "", &f_info);
	f_info.fnlinks = ft_nlinks(fav, "");
	ft_fowner(fav, "", &f_info);
	if (ft_is_maj_min(fav, ""))
	{
		f_info.major = ft_fmajor(fav, "");
		f_info.minor = ft_fminor(fav, "");
		flag = 1;
	}
	else
		f_info.fsize = ft_fsize(fav, "");
	ft_fgroup(fav, "", &f_info);
	f_info.flmdate_s = ft_flmdate_s(fav, "");
	f_info.attr = ft_fattr(fav, "");
	if (!flag)
		ft_ls_pf_norm_file(fav, &f_info, ls_width);
	else
		ft_ls_pf_mm_file(fav, &f_info, ls_width);
	ft_fislink(fav, "") ? ft_print_lnk_file(fav, "") : write(1, "\n", 1);
	ft_strdel(&f_info.flmdate_s);
}

static void		ft_print_favs_l(t_list *favs, t_width *ls_width)
{
	while (favs)
	{
		ft_ls_pf_favs_l(favs->content, ls_width);
		favs = favs->next;
	}
}

static void		ft_ls_dwfavs_l(t_list *favs)
{
	t_width		ls_width;

	ls_width.link_width = ft_fav_find_link_width(favs);
	ls_width.size_width = ft_fav_find_size_width(favs);
	ls_width.own_width = ft_fav_find_own_width(favs);
	ls_width.grp_width = ft_fav_find_grp_width(favs);
	ls_width.maj_width = ft_fav_find_maj_width(favs);
	ls_width.min_width = ft_fav_find_min_width(favs);
	if (ls_width.maj_width + ls_width.min_width > ls_width.size_width)
		ls_width.size_width = ls_width.maj_width + ls_width.min_width + \
																MAJ_MIN_OFFSET;
	ft_print_favs_l(favs, &ls_width);
}

void			ft_ls_deal_with_favs(t_list *favs, t_flags *ls_flags)
{
	if (ls_flags->lit_ell)
		ft_ls_dwfavs_l(favs);
	else
	{
		while (favs)
		{
			ft_printf("%s\n", favs->content);
			favs = favs->next;
		}
	}
}
