/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:29:42 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/25 14:59:56 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

int	nb_pipes(t_token *tk)
{
	int	nb;

	nb = 0;
	while (tk)
	{
		if (tk->type == PIPE)
			nb++;
		tk = tk->next;
	}
	return (nb);
}

void	set_cmd(t_token *tk, t_cmd **cmd, int pipes)
{
	t_cmd	*tmp;

	tmp = NULL;
	tmp = init_cmd();
	tmp->cmd = get_args(tk);
	tmp->nb_args = get_nb_args(tk);
	tmp->nb_cmd = pipes + 1;
	tmp->in = STDIN_FILENO;
	tmp->out = STDOUT_FILENO;
	addback_cmd(cmd, tmp);
}

t_cmd	*get_cmds(t_token **tk)
{
	t_cmd	*cmd;
	int		pipes;
	int		i;

	cmd = NULL;
	pipes = nb_pipes((*tk));
	i = 0;
	while (i <= pipes)
	{
		while ((*tk) && ((*tk)->type == BLANK || (*tk)->type == PIPE))
			(*tk) = (*tk)->next;
		if (!(*tk))
			return (NULL);
		set_cmd((*tk), &cmd, pipes);
		while ((*tk) && (*tk)->type != PIPE)
			(*tk) = (*tk)->next;
		i++;
	}
	return (cmd);
}
