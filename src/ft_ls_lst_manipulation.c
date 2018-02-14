/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lst_manipulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:04:57 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/13 15:33:16 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_sort_lst_ascii(t_list *list)
{
	t_list		*ptr;

	if (!list)
		return ;
	ptr = list;
	while (ptr->next)
	{
		if (ft_strcmp((char*)(ptr->content), (char*)(ptr->next->content)) > 0)
		{
			ft_swap_av((char**)&ptr->content, (char**)&ptr->next->content);
			ptr = list;
		}
		else
			ptr = ptr->next;
	}
}

int		ft_num_of_lst_nodes(t_list *lst)
{
	t_list		*ptr;
	int			i;

	i = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int		ft_index_of_cur_node(t_list *head, t_list *curr)
{
	t_list		*ptr;
	int			i;

	i = 0;
	ptr = head;
	while (ptr)
	{
		if (ptr == curr)
			return (i);
		ptr = ptr->next;
		i++;
	}
	return (i);
}

int		ft_count_lst_nodes(t_list *ptr)
{
	t_list	*p;
	int		i;

	p = ptr;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}
