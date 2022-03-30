/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:19:16 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/30 17:49:18 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_strlenarr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	nb_cmd(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd)
	{
		i++;
		data.cmd = data.cmd->next;
	}
	return (i);
}

void	var_cmd(t_data *data)
{
	ft_var_and_token(data);
	data->cmd = get_cmds(&data->token);
}

void	norme(t_data *data, int ac, char **av, char **env)
{
	ft_begining(ac, av);
	ft_env(data, env);
}

int	redir_dekita(t_token *tk)
{
	if (tk->type == END)
	{
		if (tk->prev->type >= 4)
		{
			printf("syntax error\n");
			return (1);
		}
	}
	return (0);
}
