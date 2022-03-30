/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:03:31 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/31 00:26:17 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	hound(t_cmd **cmd)
{
	char	**sp_path;
	char	*path;
	char	*bin;
	int		i;

	i = 0;
	bin = NULL;
	path = getenv("PATH");
	if (access((*cmd)->cmd[0], F_OK) == 0)
		return ;
	else if ((*cmd)->cmd[0][0] != '/' && ft_strncmp((*cmd)->cmd[0], "./", 2))
	{
		sp_path = ft_split(path, ':');
		manager(sp_path, 0);
		while (sp_path[i])
		{
			bin = ft_arrange_bin(bin, sp_path, i, (*cmd));
			if (access(bin, F_OK) == 0)
			{
				(*cmd)->cmd[0] = bin;
				return ;
			}
			i++;
		}
	}
}

int	child_process(t_data *data)
{
	int		status;
	int		i;

	i = -1;
	check_path(data);
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("minishell: fork");
		return (0);
	}
	if (data->pid == 0)
	{
		handle_pipes(data->cmd);
		exec_cmd(data, data->envp);
	}
	waitpid(data->pid, &status, 0);
	return (1);
}

int	launch_exec(t_data *data)
{
	signal(SIGINT, handler_exec);
	signal(SIGQUIT, handler_exec);
	if (nb_cmd(*data) == 1 && is_builtins(data))
		cmd_builtins(data);
	else
	{
		while (data->cmd)
		{
			open_pipes(data->cmd);
			if (!child_process(data))
				return (0);
			close_pipes(data->cmd);
			data->cmd = data->cmd->next;
		}
	}
	return (1);
}

int	execution(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "exit"))
		exit_exe();
	if (!launch_exec(data))
		return (0);
	return (1);
}
