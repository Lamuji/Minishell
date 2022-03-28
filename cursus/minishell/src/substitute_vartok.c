/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_vartok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:13:39 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/24 15:30:30 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (1);
	else
		return (0);
}

static int	var_surrounded_by_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (1);
		else
			return (0);
	}
	return (0);
}

static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*retrieve_val(char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_variable(str);
	if (var && var_exists(data, var) == SUCCESS)
		value = grep_env_var(data, var);
	else
		value = NULL;
	return (value);
}

int	substitute_var(t_data *data, t_token **tk)
{
	t_token	*tmp;
	int		i;

	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			i = 0;
			while (tmp->token[i])
			{
				state_update(&tmp, tmp->token[i]);
				if (tmp->token[i] == '$'
					&& is_next_char_a_sep(tmp->token[i + 1]) == 0
					&& var_surrounded_by_quotes(tmp->token, i) == 0
					&& (tmp->state == DEFAULT || tmp->state == DOUBLE))
					replacement(&tmp, retrieve_val(tmp->token + i, data), i);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
