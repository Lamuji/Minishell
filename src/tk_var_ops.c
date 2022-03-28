/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_var_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:06:08 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/28 15:42:58 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	redir_de_hajimeta(t_token *tk)
{
	if (tk->prev == NULL)
	{
		if (tk->type >= 4)
			return (1);
	}
	return (0);
}

static int	check_consecutive_ops(t_token *tk_node)
{
	if (tk_node->next)
	{
		if (tk_node->type == GREATER && tk_node->next->type == PIPE)
			return (0);
		if ((tk_node->type >= 4 && tk_node->next->type == PIPE)
			&& tk_node->next->type != END)
			return (1);
	}
	return (0);
}

int	check_ops_rule(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		while (tmp->prev == NULL && tmp->next == NULL)
		{
			if (tmp->type == END)
				return (FAILURE);
		}
		if (check_consecutive_ops(tmp) || redir_de_hajimeta(tmp))
		{
			while (tmp->token)
			{
				tmp = tmp->next;
				printf("Syntax error near unexpected token `%s'\n", tmp->token);
				return (FAILURE);
			}
		}
		if (redir_dekita(tmp))
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	check_var_type(t_token **tk)
{
	int	i;

	i = 0;
	while ((*tk)->token[i])
	{
		if ((*tk)->token[i] == '$')
		{
			(*tk)->type = VAR;
			return ;
		}
		i++;
	}
}

int	exception(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		check_var_type(&tmp);
		if (check_ops_rule(&tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
