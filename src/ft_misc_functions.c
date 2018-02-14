/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:21:41 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 16:49:29 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			ft_put_zeroes_to_lsflags(t_flags *ls_flags)
{
	ls_flags->lit_a = 0;
	ls_flags->big_a = 0;
	ls_flags->lit_ell = 0;
	ls_flags->lit_f = 0;
	ls_flags->lit_r = 0;
	ls_flags->big_r = 0;
	ls_flags->lit_t = 0;
}

void			ft_print_ls_usage(char c)
{
	write(2, "ls: illegal option -- ", 22);
	write(2, &c, 1);
	write(2, "\n", 1);
	write(2, "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]", \
			61);
	write(2, "\n", 1);
	exit(1);
}

unsigned int	ft_count_dgts(unsigned int num)
{
	unsigned int	i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

int				ft_fislink(char *file, char *path)
{
	struct stat		res;
	char			*new_path;

	new_path = ft_strjoin(path, file);
	lstat(new_path, &res);
	if (S_ISLNK(res.st_mode))
	{
		ft_strdel(&new_path);
		return (1);
	}
	ft_strdel(&new_path);
	return (0);
}

void			ft_print_error(char *s)
{
	char		*to_free;
	char		*ls;

	ls = ft_strdup("ls: ");
	to_free = ft_strjoin(ls, s);
	perror(to_free);
	ft_strdel(&ls);
	ft_strdel(&to_free);
}
