/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fav_find_maj_min_width.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:43:24 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:43:37 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned int	ft_fav_find_maj_width(t_list *favs)
{
	unsigned int	mw;

	mw = 0;
	while (favs)
	{
		if (ft_count_dgts(ft_fmajor(favs->content, "")) > mw)
			mw = ft_count_dgts(ft_fmajor(favs->content, ""));
		favs = favs->next;
	}
	return (mw);
}

unsigned int	ft_fav_find_min_width(t_list *favs)
{
	unsigned int	miw;

	miw = 0;
	while (favs)
	{
		if (ft_is_maj_min(favs->content, ""))
		{
			if (ft_count_dgts(ft_fminor(favs->content, "")) > miw)
				miw = ft_count_dgts(ft_fminor(favs->content, ""));
		}
		favs = favs->next;
	}
	return (miw < 3 && miw ? miw = 3 : miw);
}
