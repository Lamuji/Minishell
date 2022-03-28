/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:54:16 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/27 19:48:20 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*export_squote(t_data *data, char *temp_str, char *sstr)
{
	while (data->rstr[data->x_i])
	{
		if (data->rstr[data->x_i] == '\'')
		{
			sstr[data->x_j] = '"';
			data->x_i++;
			data->x_j++;
		}
		sstr[data->x_j] = data->rstr[data->x_i];
		if (data->rstr[data->x_i] == '=')
		{
			sstr[++data->x_j] = '"';
			data->x_i++;
		}
		data->x_i++;
		data->x_j++;
	}
	sstr[data->x_j] = '"';
	sstr[++data->x_j] = '\0';
	temp_str = ft_strdup(sstr);
	manager(temp_str, 0);
	return (temp_str);
}

void	add_at_export2(t_list *prec, t_list *cur, t_list *cell, t_list lst)
{
	while (lst.a < lst.pos)
	{
		prec = cur;
		cur = cur->next;
		lst.a++;
	}
	prec->next = cell;
	cell->next = cur;
}

char	*cases_export(t_data *data, char *temp_str, char *sstr)
{
	data->x_i = 0;
	data->x_j = 0;
	if (verify_dquote(data->cmdline))
	{
		temp_str = ft_strdup(data->rstr);
		manager(temp_str, 0);
	}
	else if (verify_squote(data->cmdline))
		temp_str = export_squote(data, temp_str, sstr);
	else
	{
		temp_str = ft_strdup(data->rstr);
		manager(temp_str, 0);
	}
	return (temp_str);
}
