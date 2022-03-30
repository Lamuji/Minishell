/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:54:54 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/30 17:52:44 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	exit_exe(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	cmd_builtins(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(data->cmd->cmd[0], "export"))
		exec_export(data, 1);
	else if (!ft_strcmp(data->cmd->cmd[0], "cd"))
		exec_cd(data, data->cmd->cmd[1]);
	else if (!ft_strcmp(data->cmd->cmd[0], "unset"))
		exec_unset(data);
	else if (!ft_strcmp(data->cmd->cmd[0], "echo")
		|| !ft_strcmp(data->cmd->cmd[0], "Echo"))
		ft_echo(data, 1);
	else if (!ft_strcmp(data->cmd->cmd[0], "env"))
		exec_env(data);
}

int	is_builtins(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "pwd")
		|| !ft_strcmp(data->cmd->cmd[0], "export")
		|| !ft_strcmp(data->cmd->cmd[0], "cd")
		|| !ft_strcmp(data->cmd->cmd[0], "unset")
		|| !ft_strcmp(data->cmd->cmd[0], "echo")
		|| !ft_strcmp(data->cmd->cmd[0], "Echo")
		|| !ft_strcmp(data->cmd->cmd[0], "env"))
		return (1);
	return (0);
}
