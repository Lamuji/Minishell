/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:54:54 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/29 15:32:15 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	exit_exe(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	not_found(t_data *data)
{
	printf("%s: command not found\n", data->cmd->cmd[0]);
}

void	cmd_builtins(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "pwd"))
		pwd();
}

int	is_builtins(t_data *data)
{
	if (!ft_strcmp(data->cmd->cmd[0], "pwd"))
		return (1);
	return (0);
}

int	pre_exec(t_data *data)
{
	if (data->cmd->next == NULL)
	{
		if (!ft_strcmp(data->cmd->cmd[0], "export"))
		{
			exec_export(data, 0);
			return (1);
		}	
		else if (!ft_strcmp(data->cmd->cmd[0], "env"))
		{
			exec_env(data);
			return (1);
		}	
		else if (!ft_strcmp(data->cmd->cmd[0], "unset"))
		{
			exec_unset(data);
			return (1);
		}
	}
	return (0);
}
