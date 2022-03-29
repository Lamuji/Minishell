/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:31:21 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/23 11:35:55 by rfkaier          ###   ########.fr       */
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

int	ft_strendswith(char *s1, char *s2)
{
	int		i;

	i = -1;
	while (s1[++i])
		if (s1[i] == s2[0])
			if (ft_strcmp(s1 + i, s2) == 0)
				return (1);
	return (0);
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
	if (is_builtins(data))
	{
		cmd_builtins(data);
		exit(0);
	}
	else
	{
		if (execve(data->cmd->cmd[0], data->cmd->cmd, env) == -1)
		{
			ft_freestrarr(env);
			if (errno == EACCES)
				data->cmd->status = 126;
			if (errno == ENOENT)
				data->cmd->status = 127;
			print_error_execve(data->cmd->status, data->cmd->cmd[0]);
			exit(data->cmd->status);
		}
	}
	exit(0);
}
