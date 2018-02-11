/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge_sort_r.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:06:38 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/07 17:13:49 by dpolosuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		ft_lst_front_back_split(t_list *source, t_list **front_ref, \
				t_list **back_ref)
{
	t_list		*fast;
	t_list		*slow;

	if (source == NULL || source->next == NULL)
	{
		*front_ref = source;
		*back_ref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_ref = source;
		*back_ref = slow->next;
		slow->next = NULL;
	}
}

static t_list	*ft_lst_sort_merge(t_list *a, t_list *b)
{
	t_list	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp((char*)a->content, (char*)b->content) < 0)
	{
		result = b;
		result->next = ft_lst_sort_merge(b->next, a);
	}
	else
	{
		result = a;
		result->next = ft_lst_sort_merge(b, a->next);
	}
	return (result);
}

void			ft_lst_merge_sort_r(t_list **head_ref)
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_lst_front_back_split(head, &a, &b);
	ft_lst_merge_sort_r(&a);
	ft_lst_merge_sort_r(&b);
	*head_ref = ft_lst_sort_merge(a, b);
}
