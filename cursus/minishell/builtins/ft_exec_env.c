/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:35:08 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/25 15:59:15 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static t_list	*free_at(t_list **lst, int pos, int i)
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
	free(cur->content);
	free(cur);
	return (*(lst));
}

int	exec_unset(t_data *data)
{
	int		i;
	int		j;
	t_list	*temp_lst;

	i = 1;
	if (ft_strlen(data->cmdline) > 1)
	{
		while (data->cmd->cmd[i])
		{
			j = 0;
			temp_lst = data->env;
			while (temp_lst)
			{
				if (ft_strstr_int(temp_lst->content, data->cmd->cmd[i]) == 1)
				{
					data->env = free_at(&data->env, j, 0);
					break ;
				}
				j++;
				temp_lst = temp_lst->next;
			}
			i++;
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
			if (ft_strstr_int(lst->content, "_=") == 1)
			{
				lst = lst->next;
			}
			if (lst == NULL)
				break ;
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(lst->content, 1);
			write(1, "\n", 2);
			lst = lst->next;
		}
	}
	else
		print_list2(lst);
}

void	exec_env(t_data *data)
{
	if (ft_strlen(data->env->content) > 0)
	{
		print_list(data->env, 0);
	}
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
