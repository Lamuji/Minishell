/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:27:04 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/25 18:40:47 by rfkaier          ###   ########.fr       */
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

void	lstclear_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		ft_freestrarr((*cmd)->cmd);
		free(*cmd);
		(*cmd) = tmp;
	}
}

void	free_line(t_data *data)
{
	if (data->cmdline)
		free(data->cmdline);
	if (data->token)
		lstclear_tk(&data->token);
	if (data->cmd)
		lstclear_cmd(&data->cmd);
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
