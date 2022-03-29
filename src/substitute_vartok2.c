/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_vartok2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:41:10 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/26 12:41:16 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	erase_and_replace(t_token **tk_node, char *str, char *var_value, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str)
				- count_len_var(str + index) + ft_strlen(var_value)));
	manager(new_str, 0);
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
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

char	*identify_variable(char *str)
{
	char	*var;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}	
		i++;
	}
	len = count_len_var(str);
	var = ft_substr(str, start, len);
	manager(var, 0);
	if (!var)
		return (NULL);
	var = ft_strjoin(var, "=");
	manager(var, 0);
	return (var);
}

void	state_update(t_token **tk, char c)
{
	if (c == '\'' && (*tk)->state == DEFAULT)
		(*tk)->state = SIMPLE;
	else if (c == '\"' && (*tk)->state == DEFAULT)
		(*tk)->state = DOUBLE;
	else if (c == '\'' && (*tk)->state == SIMPLE)
		(*tk)->state = DEFAULT;
	else if (c == '\"' && (*tk)->state == DOUBLE)
		(*tk)->state = DEFAULT;
}

char	*grep_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
			break ;
		i++;
	}
	str = ft_strdup(data->envp[i] + len);
	manager(str, 0);
	return (str);
}
