/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_vartok3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:47:56 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/26 12:47:57 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	replacement(t_token **tk_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(tk_node, (*tk_node)->token, index) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (erase_and_replace(tk_node, (*tk_node)
				->token, var_value, index) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	is_var_compliant(char c)
{
	if (c == ' ' || c == '$' || c == '\0' || c == '\'' || c == '\"'
		|| (c >= '\t' && c <= '\r')
		|| c == '=' || c == '[' || c == ']' || c == '{' || c == '}')
		return (0);
	else
		return (1);
}

int	count_len_var(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if (str[i] >= '0' && str[i] <= '9')
		return (count + 1);
	while (str[i])
	{
		if (is_var_compliant(str[i]) == 0)
			break ;
		count++;
		i++;
	}
	return (count);
}

int	erase_var(t_token **tk_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_len_var(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	manager(new_str, 0);
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + count_len_var(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	(*tk_node)->token = new_str;
	return (SUCCESS);
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}
