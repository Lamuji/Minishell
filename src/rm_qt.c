/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_qt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:27:57 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/24 15:31:16 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	change_default_to_quote(t_token **tk_node, int *i)
{
	if ((*tk_node)->token[*i] == '\'')
		(*tk_node)->state = SIMPLE;
	if ((*tk_node)->token[*i] == '\"')
		(*tk_node)->state = DOUBLE;
	(*i)++;
}

static int	if_quotes_and_default(t_token **tk_node, int i)
{
	if (((*tk_node)->token[i] == '\'' || (*tk_node)->token[i] == '\"')
		&& (*tk_node)->state == DEFAULT)
		return (1);
	else
		return (0);
}

static int	change_back_to_default(t_token **tk_node, int *i)
{
	if (((*tk_node)->token[*i] == '\'' && (*tk_node)->state == SIMPLE)
		|| ((*tk_node)->token[*i] == '\"' && (*tk_node)->state == DOUBLE))
	{
		(*tk_node)->state = DEFAULT;
		(*i)++;
		return (1);
	}
	else
		return (0);
}

int	remove_quotes(t_token **tk_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_length((*tk_node)->token, i, i));
	manager(new_line, 0);
	if (!new_line)
		return (FAILURE);
	while ((*tk_node)->token[i])
	{
		if (if_quotes_and_default(tk_node, i) == 1)
		{
			change_default_to_quote(tk_node, &i);
			continue ;
		}
		else if (change_back_to_default(tk_node, &i) == 1)
			continue ;
		new_line[j++] = (*tk_node)->token[i++];
	}
	new_line[j] = '\0';
	(*tk_node)->token = new_line;
	return (SUCCESS);
}
