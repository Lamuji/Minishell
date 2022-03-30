/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:59:04 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:41:52 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_gb = 0;

void	manager(void *ptr, int err)
{
	static t_list	*heap = NULL;
	t_list			*new;

	if (err == 1)
		ft_lstclear(&heap, free);
	else
	{
		new = ft_lstnew(ptr);
		ft_lstadd_back(&heap, new);
	}
}

char	**copyenv(t_data *data)
{
	int		i;
	char	**res;

	i = 0;
	res = calloc(sizeof(char *), (ft_envsize(data->cenv) + 1));
	manager(res, 0);
	while (data->cenv)
	{
		res[i] = ft_calloc(sizeof(char), (ft_strlen(data->cenv->content) + 1));
		manager(res[i], 0);
		ft_strlcpy(res[i], data->cenv->content,
			(ft_strlen(data->cenv->content) + 1));
		i++;
		data->cenv = data->cenv->next;
	}
	return (res);
}

static t_list	*lstnew_env(char *str)
{
	t_list	*new_block;

	new_block = (t_list *)malloc(sizeof(t_list));
	manager(new_block, 0);
	if (!(new_block))
		return (NULL);
	new_block->content = ft_strdup(str);
	manager(new_block->content, 0);
	new_block->next = NULL;
	return (new_block);
}

void	ft_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(&data->env, lstnew_env(env[i]));
		ft_lstadd_back(&data->cenv, lstnew_env(env[i]));
		i++;
	}
	data->envp = copyenv(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	norme(&data, ac, av, env);
	while (1)
	{
		signals();
		data.cmdline = readline(PROMPT);
		manager(data.cmdline, 0);
		if (!data.cmdline)
			break ;
		if (*data.cmdline)
			add_history(data.cmdline);
		if (tokenizer(&data, data.cmdline) == FAILURE)
			continue ;
		if (exception(&data.token) == FAILURE)
		{
			lstclear_tk(&data.token);
			continue ;
		}
		var_cmd(&data);
		if (!execution(&data))
			continue ;
	}
	return (0);
}
