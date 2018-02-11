/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:47:29 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 19:28:49 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_is_finav(t_list *names)
{
	t_list			*ptr;
	int				i;
	struct stat		res;

	ptr = names;
	i = 0;
	while (ptr)
	{
		lstat(ptr->content, &res);
		if (S_ISREG(res.st_mode))
			i++;
		ptr = ptr->next;
	}
	return (i);
}

int		ft_is_fav(char *path)
{
	struct stat		res;

	lstat(path, &res);
	if (S_ISREG(res.st_mode))
		return (1);
	return (0);
}

t_list		*ft_put_favtolst(t_list *ptr)
{
	t_list		*newlst;
	t_list		*to_free;

	newlst = NULL;
	to_free = NULL;
	while (ptr)
	{
		if (ft_is_fav((char*)ptr->content))
		{
			if (!newlst)
				newlst = ft_lstnew(ptr->content, \
						ft_strlen((char*)ptr->content));
			else
			{
				to_free = ft_lstnew(ptr->content, \
						ft_strlen((char*)ptr->content));
				ft_lstadd_atend(&newlst, to_free);
			}
		}
		ptr = ptr->next;
	}
	return (newlst);
}

void	ft_ls_deal_with_favs(t_list *favs)
{
	while (favs)
	{
		ft_printf("%s\n", favs->content);
		favs = favs->next;
	}
}

static void		ft_main_while(t_list *names, int ac, char **av, \
				t_flags *ls_flags)
{
	t_list		*ptr;
	t_list		*favs;
	int			dir;

	favs = NULL;
	ptr = names;
	dir = 0;
	if (ft_is_finav(names))
	{
		favs = ft_put_favtolst(names);
		ft_ls_deal_with_favs(favs);
		dir = 1;
	}
	while (ptr)
	{
		if (ft_is_dir((char*)ptr->content, ""))
		{
			if (dir)
				ft_printf("\n%s:\n", ptr->content);
			ft_ls_opn_dir(ptr->content, ls_flags);
			dir = 1;
		}
		ptr = ptr->next;
	}
	ft_lstdel(&favs, ft_lstdelfunc);
}

int				main(int ac, char **av)
{
	t_flags		ls_flags;
	t_list		*names;

	names = NULL;
	ft_put_zeroes_to_lsflags(&ls_flags);
	ft_parse_flags(ac, av, &ls_flags, &names);
	if (!names)
		ft_ls_opn_dir(NULL, &ls_flags);
	else
	{
		if (ls_flags.lit_f)
			;
		else if (ls_flags.lit_t && ls_flags.lit_r)
		{
			ft_lst_merge_sort_t(&names);
			ft_lstrev(&names);
		}
		else if (ls_flags.lit_t && !ls_flags.lit_r)
			ft_lst_merge_sort_t(&names);
		else if (ls_flags.lit_r && !ls_flags.lit_t)
			ft_lstrev(&names);
		ft_main_while(names, ac, av, &ls_flags);
	}
	ft_lstdel(&names, ft_lstdelfunc);
	return (0);
}
