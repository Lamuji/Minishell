/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:07:25 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:24:32 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static	char	**copyenvunset(t_data *data)
{
	int		i;
	char	**res;
	t_list	*copy;

	i = 0;
	res = calloc(sizeof(char *), (ft_envsize(data->env) + 1));
	manager(res, 0);
	copy = data->env;
	while (copy)
	{
		res[i] = ft_calloc(sizeof(char), (ft_strlen(copy->content) + 1));
		manager(res[i], 0);
		ft_strlcpy(res[i], copy->content,
			(ft_strlen(copy->content) + 1));
		i++;
		copy = copy->next;
	}
	return (res);
}

void	check_path(t_data *data)
{
	int		i;
	char	*str;

	if (g_gb == 1)
	{
		ft_freestrarr(data->envp);
		data->envp = copyenvunset(data);
	}
	i = -1;
	while (data->envp[++i])
	{
		str = ft_strjoin("PATH=", getenv("PATH"));
		manager(str, 0);
		if (!ft_strcmp(data->envp[i], str))
			hound(&data->cmd);
	}
}

int	count_equals(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

void	pwd(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror(tmp);
	}
	else
	{
		ft_putstr_fd(tmp, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	free(tmp);
}
