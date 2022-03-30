/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:21:18 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:23:30 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_list	*creat_cell2(char *str)
{
	t_list	*cell;

	cell = ft_calloc(sizeof(t_list), 1);
	manager(cell, 0);
	if (!cell)
		return (NULL);
	cell->content = ft_strdup(str);
	manager(cell->content, 0);
	cell->next = NULL;
	return (cell);
}

int	check_if_arg_in_env(char *var_name, t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (ft_ch_int(lst->content, var_name) != 0)
			return (i);
		lst = lst->next;
		i++;
	}
	return (0);
}

int	len_list(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

int	verify_squote(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	exec_export2(t_data *data, int i, int j)
{
	if (check_export_args_str(data->cmd->cmd[i]) == 1)
	{
		printf("export: `%s': not a valid identifier\n",
			data->cmd->cmd[i]);
	}
	else
	{
		if (count_equals(data->cmd->cmd[i])
			|| !(count_equals(data->cmd->cmd[i])
				&& !(check_if_arg_in_env(data->cmd->cmd[i],
						data->env))))
			add_var_last_export(data, &data->env, data->cmd->cmd[i], j);
	}
}
