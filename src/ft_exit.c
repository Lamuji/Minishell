/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:31:21 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:26:50 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_freestrarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	exit_shell(void)
{
	write(1, "\n", 1);
	exit(0);
}

void	print_error_execve(int num, char *cmd)
{
	if (num == 127)
		printf("%s: command not found\n", cmd);
	else if (num == 126)
		printf("%s: argument found but not executable\n", cmd);
	else if (num == 1)
		printf("%s: No such file or directory\n", cmd);
}

void	exec_cmd(t_data *data, char **env)
{
	int	exec;

	if (is_builtins(data))
	{
		cmd_builtins(data);
		exit(0);
	}
	else
	{
		exec = execve(data->cmd->cmd[0], data->cmd->cmd, env);
		if (exec == -1)
		{
			ft_freestrarr(env);
			if (errno == EACCES)
				data->cmd->status = 126;
			if (errno == ENOENT)
				data->cmd->status = 127;
			print_error_execve(data->cmd->status, data->cmd->cmd[0]);
			exit(1);
		}
	}
}
