/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:03:31 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/29 15:07:39 by edalmis          ###   ########.fr       */
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
	pid_t	pid;
	int		status;

	hound(&data->cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (0);
	}
	if (pid == 0)
	{
		handle_pipes(data->cmd);
		exec_cmd(data, data->envp);
	}
	wait(&status);
	return (1);
}

static int	line_echo(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "echo"))
	{
		ft_echo(data, 1);
		return (1);
	}
	return (0);
}

int	launch_exec(t_data *data)
{
	signal(SIGINT, handler_exec);
	signal(SIGQUIT, handler_exec);
	while (data->cmd)
	{		
		if (!ft_strcmp(data->cmd->cmd[0], "cd"))
			exec_cd(data, data->cmd->cmd[1]);
		if (!ft_strcmp(data->cmd->cmd[0], "exit")
			&& data->cmd->next == NULL && data->cmd->prev == NULL)
		{
			exit_exe();
			return (1);
		}
		if (!pre_exec(data))
		{	
			if (!line_echo(data))
			{
				open_pipes(data->cmd);
				if (!child_process(data))
					return (0);
				close_pipes(data->cmd);
			}
		}
		data->cmd = data->cmd->next;
	}
	return (1);
}

int	execution(t_data *data)
{
	if (!launch_exec(data))
		return (0);
	return (1);
}
