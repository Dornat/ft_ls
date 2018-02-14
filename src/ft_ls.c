/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:47:29 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:45:11 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_main_while_if(char *pcont, int *cnt, int *dir, \
				t_flags *ls_flags)
{
	if (*dir)
	{
		ft_printf("\n%s:\n", pcont);
		*cnt = 0;
	}
	if (*cnt > 1)
	{
		ft_printf("%s:\n", pcont);
		*cnt = 0;
	}
	ft_ls_opn_dir(pcont, ls_flags);
	*dir = 1;
}

static void		ft_main_while(t_list *names, t_flags *ls_flags)
{
	t_list		*ptr;
	t_list		*favs;
	int			dir;
	int			cnt;

	favs = NULL;
	ptr = names;
	dir = 0;
	cnt = ft_count_lst_nodes(ptr);
	if (ft_is_finav(names, ls_flags))
	{
		favs = ft_put_favtolst(names, ls_flags);
		ft_ls_deal_with_favs(favs, ls_flags);
		dir = 1;
	}
	while (ptr)
	{
		if (ft_is_dir_av((char*)ptr->content, "", ls_flags))
			ft_main_while_if(ptr->content, &cnt, &dir, ls_flags);
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
		ft_main_while(names, &ls_flags);
	}
	ft_lstdel(&names, ft_lstdelfunc);
	return (0);
}
