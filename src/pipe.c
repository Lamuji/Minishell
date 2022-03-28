/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:41:09 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/16 16:59:22 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	open_pipes(t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
		{
			perror("minishell: pipe");
			return (0);
		}
	}
	return (1);
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->next)
		close(cmd->pipe[1]);
	if (cmd->prev)
		close(cmd->prev->pipe[0]);
}

void	handle_pipes(t_cmd *cmd)
{
	dup2(cmd->out, STDOUT_FILENO);
	dup2(cmd->in, STDIN_FILENO);
	if (cmd->next)
	{
		close(cmd->pipe[0]);
		dup2(cmd->pipe[1], cmd->out);
		close(cmd->pipe[1]);
	}
	if (cmd->prev)
	{
		dup2(cmd->prev->pipe[0], cmd->in);
		close(cmd->prev->pipe[0]);
	}
}

int	ft_envsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
