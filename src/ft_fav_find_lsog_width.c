/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fav_find_lsog_width.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:42:20 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:44:41 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned int	ft_fav_find_link_width(t_list *favs)
{
	unsigned int	lw;

	lw = 0;
	while (favs)
	{
		if (ft_count_dgts(ft_nlinks(favs->content, "")) > lw)
			lw = ft_count_dgts(ft_nlinks(favs->content, ""));
		favs = favs->next;
	}
	return (lw);
}

unsigned int	ft_fav_find_size_width(t_list *favs)
{
	unsigned int	sw;

	sw = 0;
	while (favs)
	{
		if (ft_count_dgts(ft_fsize(favs->content, "")) > sw)
			sw = ft_count_dgts(ft_fsize(favs->content, ""));
		favs = favs->next;
	}
	return (sw);
}

unsigned int	ft_fav_find_own_width(t_list *favs)
{
	unsigned int	ow;
	t_finfo			f_info;
	unsigned int	len;

	ow = 0;
	while (favs)
	{
		ft_fowner(favs->content, "", &f_info);
		len = ft_strlen(f_info.fowner);
		if (len > ow)
			ow = len;
		favs = favs->next;
	}
	return (ow);
}

unsigned int	ft_fav_find_grp_width(t_list *favs)
{
	unsigned int	gw;
	t_finfo			f_info;
	unsigned int	len;

	gw = 0;
	while (favs)
	{
		ft_fgroup(favs->content, "", &f_info);
		len = ft_strlen(f_info.fgroup);
		if (len > gw)
			gw = len;
		favs = favs->next;
	}
	return (gw);
}
