/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:27:04 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/31 00:42:25 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	lstclear_tk(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->token);
		free(*token);
		(*token) = tmp;
	}
}

t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = insert;
	else if (tmp == to_del)
	{
		*head = insert;
		insert->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = insert;
	}
	else
	{
		while (tmp != to_del)
			tmp = tmp->next;
		insert->prev = tmp->prev;
		tmp->prev->next = insert;
		while (insert->next)
			insert = insert->next;
		tmp->next->prev = insert;
		insert->next = tmp->next;
	}
	return (insert);
}
