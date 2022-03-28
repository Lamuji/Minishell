/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:19:16 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/28 15:45:34 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
