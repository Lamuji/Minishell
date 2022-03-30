/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:35:08 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:23:30 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_list	*free_at(t_list **lst, int pos, int i)
{
	t_list	*prec;
	t_list	*cur;

	cur = *lst;
	prec = *lst;
	if (is_empty_list(*lst))
		return (NULL);
	if (pos == 0)
	{
		lst = &(*lst)->next;
		free(cur->content);
		free(cur);
		return (*(lst));
	}
	while (i < pos)
	{
		prec = cur;
		cur = cur->next;
		i++;
	}
	prec->next = cur->next;
	return (*(lst));
}

int	exec_unset(t_data *data)
{
	t_list	*temp_lst;

	data->i = 1;
	if (ft_strlen(data->cmdline) > 1)
	{
		while (data->cmd->cmd[data->i])
		{
			data->j = 0;
			temp_lst = data->env;
			while (temp_lst)
			{
				if (ft_ch_int(temp_lst->content, data->cmd->cmd[data->i]))
				{
					data->env = free_at(&data->env, data->j, 0);
					if (ft_ch_int(data->envp[data->j], data->cmd->cmd[data->i]))
						g_gb = 1;
					break ;
				}
				data->j++;
				temp_lst = temp_lst->next;
			}
			data->i++;
		}
	}
	return (0);
}

void	print_list(t_list *lst, int d)
{
	if (d)
	{
		while (lst)
		{
			if (ft_ch_int(lst->content, "_=") == 1)
				lst = lst->next;
			if (lst == NULL)
				break ;
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(lst->content, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
			lst = lst->next;
		}
	}
	else
		print_list2(lst);
}

void	exec_env(t_data *data)
{
	if (ft_strlen(data->env->content) > 0)
		print_list(data->env, 0);
}

int	is_space(char x)
{
	if (x == ' ')
		return (1);
	else if (x == '\n')
		return (1);
	else if (x == '\t')
		return (1);
	else
		return (0);
}
