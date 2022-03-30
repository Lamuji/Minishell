/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:18:43 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/29 19:03:04 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	addback_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!*cmd)
	{
		new->pos = 1;
		*cmd = new;
		return ;
	}
	last = get_last_cmd(*cmd);
	new->pos = last->pos + 1;
	new->prev = last;
	last->next = new;
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	manager(cmd, 0);
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	get_nb_args(t_token *token)
{
	int	nb;

	nb = 0;
	while (token && token->type != PIPE)
	{
		if (token && (token->type == WORD || token->type == VAR))
			nb++;
		if (token)
			token = token->next;
	}
	return (nb);
}

void	set_args(t_token **token, int nb_args, char ***args)
{
	int	i;

	i = 0;
	while ((*token) && (*token)->type != PIPE && i < nb_args)
	{
		if ((*token) && ((*token)->type == WORD || (*token)->type == VAR))
		{
			(*args)[i] = malloc(sizeof(char)
					* (ft_strlen((*token)->token) + 1));
			manager((*args)[i], 0);
			(*args)[i] = (*token)->token;
			if (!(*args)[i])
				return ;
			i++;
		}
		(*token) = (*token)->next;
	}
}

char	**get_args(t_token *token)
{
	char	**args;
	int		nb_args;
	int		i;

	i = 0;
	nb_args = get_nb_args(token);
	args = NULL;
	args = ft_calloc(sizeof(*args), (nb_args + 1));
	if (!args)
		perror("malloc error");
	manager(args, 0);
	while (token && token->type != PIPE)
	{
		if ((token->type == WORD || token->type == VAR) && i < nb_args)
		{
			args[i] = ft_calloc(sizeof(char *), (ft_strlen(token->token + 1)));
			manager(args[i], 0);
			args[i] = token->token;
			i++;
		}
		token = token->next;
	}
	return (args);
}
