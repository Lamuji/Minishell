/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:20:09 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/28 15:25:40 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	ft_var_and_token(t_data *data)
{
	substitute_var(data, &data->token);
	handle_quotes(data);
	tokenize_var(data);
}

void	ft_begining(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	stock_sep2(t_token **tk_list, char *line, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	sep = (char *)malloc(sizeof(char) * 2);
	manager(sep, 0);
	if (!sep)
		return (FAILURE);
	while (i < 1)
		sep[i++] = line[index++];
	sep[i] = '\0';
	lst_add_back_tk(tk_list, lstnew_tk(sep, type, DEFAULT));
	return (SUCCESS);
}

int	tokenizer(t_data *data, char *cmdline)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(cmdline);
	data->t_state = DEFAULT;
	data->t_start = 0;
	data->t_state = tokenizer2(data, cmdline, i, end);
	if (data->t_state != DEFAULT)
	{
		printf("Error : Unclose quotes\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
