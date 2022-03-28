/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:10:31 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/27 19:44:28 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static t_list	*add_at_export(t_data *data, t_list *lst)
{
	t_list	*prec;
	t_list	*cur;
	t_list	*cell;
	char	*sstr;
	char	*temp_str;

	prec = NULL;
	cur = NULL;
	cell = NULL;
	temp_str = NULL;
	sstr = ft_calloc(sizeof(char *), (ft_strlen(data->rstr) + 3));
	manager(sstr, 0);
	temp_str = cases_export(data, temp_str, sstr);
	prec = lst;
	cur = lst;
	cell = creat_cell2(temp_str);
	if (is_empty_list(lst))
		return (cell);
	if (lst->pos == 0)
	{
		cell->next = lst;
		return (cell);
	}
	add_at_export2(prec, cur, cell, *lst);
	return (lst);
}

static void	add_new_export(t_data *data, t_list **lst,
char *new_content, char *var_dest)
{
	t_list	*temp;

	if (verify_dquote(data->cmdline))
	{
		new_content = ft_strjoin("\"", new_content);
		new_content = ft_strjoin(new_content, "\"");
		manager(new_content, 0);
	}
	temp = *lst;
	while (temp != NULL)
	{
		if (ft_strstr_int(temp->content, var_dest) != 0)
		{
			temp->content = add_content_to_var(temp->content, new_content, 0);
			break ;
		}
		temp = temp->next;
	}
	if (temp == NULL)
	{
		*lst = add_at(*lst, var_dest, 0, 0);
		add_new_export(data, lst, getcwd(NULL, 0), var_dest);
	}
}

void	add_var_last_export(t_data *data, t_list **lst,
char *str, int export)
{
	char	**var;

	data->rstr = ft_strdup(str);
	manager(data->rstr, 0);
	var = ft_split(data->rstr, '=');
	manager(var, 0);
	if (check_if_arg_in_env(var[0], *lst) == 0 && export == 0)
	{
		free(data->rstr);
		ft_freestrarr(var);
		return ;
	}
	if (check_if_arg_in_env(data->rstr, *lst) != 0
		&& count_equals(data->rstr) > 0)
		add_new_export(data, lst, var[1], var[0]);
	else if (check_if_arg_in_env(data->rstr, *lst) == 0
		&& ft_strcmp(data->rstr, "export"))
	{
		(*lst)->a = 0;
		(*lst)->pos = len_list(*lst);
		add_at_export(data, *lst);
	}
}

int	check_export_args_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' || str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1 || str[i] == '_'
			|| (ft_isnum(str[i]) == 1 && i > 0))
			i++;
		else if ((str[i] == '=' && i > 0)
			|| (str[i] == '\0' && i > 0))
			return (0);
		else
			return (1);
	}
	return (0);
}

void	exec_export(t_data *data, int i)
{
	int	j;

	j = 1;
	if (!ft_strcmp(data->cmdline, "export"))
	{
		print_list(data->env, 1);
	}
	else
	{
		while (data->cmd->cmd[i])
		{
			exec_export2(data, i, j);
			i++;
		}
	}
}
