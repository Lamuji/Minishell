/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:01:31 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/27 15:51:27 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	which_state(int state, char *line, int i)
{
	if (line[i] == '\'' && state == DEFAULT)
		state = SIMPLE;
	else if (line[i] == '\"' && state == DEFAULT)
		state = DOUBLE;
	else if (line[i] == '\'' && state == SIMPLE)
		state = DEFAULT;
	else if (line[i] == '\"' && state == DOUBLE)
		state = DEFAULT;
	return (state);
}

static int	is_sep(char *line, int i)
{
	if (((line[i] > 8 && line[i] < 14) || line[i] == 32))
		return (BLANK);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (DLESSER);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (DGREATER);
	else if (line[i] == '<')
		return (LESSER);
	else if (line[i] == '>')
		return (GREATER);
	else if (line[i] == '\0')
		return (END);
	else
		return (0);
}

static int	stock_word(t_token **tk_list, char *line, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (index - start + 1));
	manager(word, 0);
	if (!word)
		return (FAILURE);
	while (start < index)
	{
		word[i] = line[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_tk(tk_list, lstnew_tk(word, WORD, DEFAULT));
	return (SUCCESS);
}

static int	stock_sep(t_token **tk_list, char *line, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == DGREATER || type == DLESSER)
	{
		sep = (char *)malloc(sizeof(char) * 3);
		manager(sep, 0);
		if (!sep)
			return (FAILURE);
		while (i < 2)
			sep[i++] = line[index++];
		sep[i] = '\0';
		lst_add_back_tk(tk_list, lstnew_tk(sep, type, DEFAULT));
	}
	else
	{
		if (stock_sep2(tk_list, line, index, type) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	tokenizer2(t_data *data, char *cmdline, int i, int end)
{
	while (i <= end)
	{
		data->t_state = which_state(data->t_state, cmdline, i);
		if (data->t_state == DEFAULT)
		{
			data->t_type = is_sep(cmdline, i);
			if (data->t_type)
			{
				if (i != 0 && is_sep(cmdline, i - 1) == 0)
					stock_word(&data->token, cmdline, i, data->t_start);
				if (data->t_type == DGREATER || data->t_type == DLESSER
					|| data->t_type == PIPE || data->t_type == LESSER
					|| data->t_type == GREATER || data->t_type == END)
				{
					stock_sep(&data->token, cmdline, i, data->t_type);
					if (data->t_type == DGREATER || data->t_type == DLESSER)
						i++;
				}
				data->t_start = i + 1;
			}
		}
		i++;
	}
	return (data->t_state);
}
