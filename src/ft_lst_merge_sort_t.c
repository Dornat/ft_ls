/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge_sort_t.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpolosuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:38:46 by dpolosuk          #+#    #+#             */
/*   Updated: 2018/02/11 14:57:28 by dpolosuk         ###   ########.fr       */
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

static void		ft_lst_sort_merge_t_if(t_list **result, t_list *a, t_list *b)
{
	if (ft_strcmp((char*)a->content, (char*)b->content) > 0)
	{
		*result = b;
		(*result)->next = ft_lst_sort_merge_t(b->next, a);
	}
	else
	{
		*result = a;
		(*result)->next = ft_lst_sort_merge_t(b, a->next);
	}
}

t_list			*ft_lst_sort_merge_t(t_list *a, t_list *b)
{
	t_list	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->content_size == b->content_size)
		ft_lst_sort_merge_t_if(&result, a, b);
	else if (a->content_size <= b->content_size)
	{
		result = b;
		result->next = ft_lst_sort_merge_t(b->next, a);
	}
	else
	{
		result = a;
		result->next = ft_lst_sort_merge_t(b, a->next);
	}
	return (result);
}

void			ft_lst_merge_sort_t(t_list **head_ref)
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_lst_front_back_split(head, &a, &b);
	ft_lst_merge_sort_t(&a);
	ft_lst_merge_sort_t(&b);
	*head_ref = ft_lst_sort_merge_t(a, b);
}
