/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:45:32 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:56:33 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_parse_unit_elif(char c, t_flags *ls_flags)
{
	if (c == 'a')
		ls_flags->lit_a = 1;
	else if (c == 'A')
		ls_flags->big_a = 1;
	else if (c == 'l')
		ls_flags->lit_ell = 1;
	else if (c == 'f')
	{
		ls_flags->lit_f = 1;
		ls_flags->lit_a = 1;
	}
	else if (c == 'r')
		ls_flags->lit_r = 1;
	else if (c == 'R')
		ls_flags->big_r = 1;
	else if (c == 't')
		ls_flags->lit_t = 1;
	else if (c == '1' && ls_flags->lit_ell)
		ls_flags->lit_ell = 0;
}

static int		ft_pu_oth_flags(char c)
{
	if (c == 'B' || c == 'C' || c == 'F' || c == 'G' || c == 'H' || c == 'L' \
		|| c == 'O' || c == 'P' || c == 'S' || c == 'T' || c == 'U' || \
		c == 'W' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || \
		c == 'g' || c == 'h' || c == 'i' || c == 'k' || c == 'm' || c == 'n' \
		|| c == 'o' || c == 'p' || c == 'q' || c == 's' || c == 'u' || \
		c == 'w' || c == 'x' || c == '1')
		return (1);
	return (0);
}

static void		ft_parse_unit(char *av, t_flags *ls_flags, int *fffa)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i] == '-' && !av[i + 1])
		{
			*fffa = 42;
			break ;
		}
		else if (av[i] == 'a' || av[i] == 'A' || av[i] == 'l' || av[i] == 'f' \
			|| av[i] == 'r' || av[i] == 'R' || av[i] == 't' || av[i] == '1')
			ft_parse_unit_elif(av[i], ls_flags);
		else if (ft_pu_oth_flags(av[i]))
			;
		else
			ft_print_ls_usage(av[i]);
		i++;
	}
}

static void		ft_parse_flags_elif(char **av, int i, t_list **names)
{
	t_list		*newl;

	newl = NULL;
	newl = ft_lstnew(av[i], ft_strlen(av[i]));
	newl->content_size = ft_flmdate_i("", av[i]);
	ft_lstadd_atend(names, newl);
}

void			ft_parse_flags(int ac, char **av, t_flags *ls_flags, \
				t_list **names)
{
	int			i;
	int			flag_for_first_arg;

	i = 1;
	flag_for_first_arg = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] && !flag_for_first_arg)
			ft_parse_unit(av[i], ls_flags, &flag_for_first_arg);
		else if (!flag_for_first_arg || flag_for_first_arg == 42)
		{
			if (!ls_flags->lit_f)
				ft_sort_params(av, i, ac);
			ft_check_for_valid_arg(av, i, ac);
			*names = ft_lstnew(av[i], ft_strlen(av[i]));
			(*names)->content_size = ft_flmdate_i("", av[i]);
			flag_for_first_arg = 1;
		}
		else if (flag_for_first_arg)
			ft_parse_flags_elif(av, i, names);
		i++;
	}
}
