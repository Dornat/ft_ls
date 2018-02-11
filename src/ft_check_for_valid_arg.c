/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_for_valid_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 12:56:29 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 14:12:49 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_check_for_valid_arg(char **av, int i, int ac)
{
	struct stat		res;
	char			*s;
	char			*to_free;

	while (i < ac)
	{
		if (lstat(av[i], &res) == -1)
		{
			s = ft_strdup("ls: ");
			to_free = ft_strjoin(s, av[i]);
			perror(to_free);
			ft_strdel(&s);
			ft_strdel(&to_free);
		}
		i++;
	}
}
