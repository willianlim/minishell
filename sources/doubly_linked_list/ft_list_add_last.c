/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prafael- <prafael-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:00:46 by prafael-          #+#    #+#             */
/*   Updated: 2022/04/20 16:27:58 by prafael-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_list_add_last(t_doubly *l, char *val)
{
	t_node	*new;

	new = ft_node_create(val);
	new->prev = l->end;
	if(ft_list_is_empty(l))
		l->begin = new;
	else
		l->end->next = new;
	l->end = new;
	l->size++;
}
