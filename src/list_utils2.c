/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:18:11 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/26 13:18:16 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*lstnew_tk(char *str, int type, int state)
{
	t_token	*new_block;

	new_block = (t_token *)malloc(sizeof(t_token));
	manager(new_block, 0);
	if (!(new_block))
		return (NULL);
	new_block->token = str;
	new_block->type = type;
	new_block->state = state;
	new_block->prev = NULL;
	new_block->next = NULL;
	return (new_block);
}

void	lst_add_back_tk(t_token **alst, t_token *new_node)
{
	t_token	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	lstdelone_tk(t_token *lst, void (*del)(void *))
{
	if (del && lst)
		(*del)(lst->token);
	free(lst);
}

void	lstdelone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (del && lst)
		(*del)(lst->cmd);
	free(lst);
}

void	lstclear_env(t_data *data)
{
	t_list	*tmp;

	while (data->env)
	{
		tmp = data->env->next;
		free(data->env);
		data->env = tmp;
	}
}
