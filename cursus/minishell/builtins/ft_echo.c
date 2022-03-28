/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:05:56 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/22 15:53:17 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	echo_option2(t_data *data, int i)
{
	int	x;
	int	y;

	y = ft_strlen(data->cmdline);
	if (y == 4)
		return (1);
	while ((ft_strchr(data->cmd->cmd[i], '"')
			|| ft_strchr(data->cmd->cmd[i], '\'')) && i < y)
	{
		x = 0;
		if (data->cmd->cmd[i][x] == '"' || data->cmd->cmd[i][x] == '\'')
		{
			x++;
			if ((data->cmd->cmd[i][x] != '"'
				|| data->cmd->cmd[i][x] == '\'') && data->cmd->cmd[i][x])
				return (x);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static int	echo_option(t_data *data, int i)
{
	int	x;
	int	y;

	y = ft_strlen(data->cmdline);
	if (y == 4)
		return (1);
	else if (y == 7 && ft_strcmp(data->cmdline, "echo -n") == 0)
		return (3);
	while (ft_strstr(data->cmd->cmd[i], "-n") && i < y)
	{
		x = 0;
		if (data->cmd->cmd[i][x] == '-')
		{
			x++;
			while (data->cmd->cmd[i][x] == 'n' && data->cmd->cmd[i][x])
				x++;
			if (data->cmd->cmd[i][x] != 'n' && data->cmd->cmd[i][x])
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static void	echo_exec(t_data *data, int i, int x, int a)
{
	if (!ft_strcmp(data->cmd->cmd[i], "$?"))
		ft_putnbr_fd(0, STDOUT_FILENO);
	else
	{
		if (ft_strchr(data->cmd->cmd[i], '\'')
			|| ft_strchr(data->cmd->cmd[i], '"'))
		{
			while (data->cmd->cmd[i][x + 1])
				ft_putchar_fd(data->cmd->cmd[i][x++], STDOUT_FILENO);
		}
		else
		{
			if (data->cmd->cmd[i] != NULL)
				ft_putstr_fd(data->cmd->cmd[i], STDOUT_FILENO);
		}
	}
	if (i < a - 1)
		ft_putchar_fd(' ', STDOUT_FILENO);
}

static void	ft_echo2(t_data *data, int i, int a, int opt)
{
	if (a > 1)
	{
		i = echo_option(data, i);
		if (data->cmd->cmd[i - 1] != (NULL))
		{
			if (data->cmd->cmd[i] != (NULL))
			{	
				data->ec_x = echo_option2(data, i);
				if (i > 1)
					opt = 1;
				while (i < a)
				{
					echo_exec(data, i, data->ec_x, a);
					if (i == a - 1 && !opt)
						ft_putchar_fd('\n', STDOUT_FILENO);
					i++;
				}
			}
		}
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_echo(t_data *data, int i)
{
	int	opt;
	int	a;

	opt = 0;
	a = 0;
	while (data->cmd->cmd[a])
		a++;
	ft_echo2(data, i, a, opt);
}
