/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_qt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzi <ramzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:29:47 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/21 10:57:27 by ramzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	count_length(char *str, int count, int i)
{
	int	state;

	state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && state == DEFAULT)
		{
			if (str[i] == '\'')
				state = SIMPLE;
			if (str[i] == '\"')
				state = DOUBLE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && state == SIMPLE)
			|| (str[i] == '\"' && state == DOUBLE))
		{
			state = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

int	if_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	handle_quotes(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (if_quotes(tmp->token) == 1)
			remove_quotes(&tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
