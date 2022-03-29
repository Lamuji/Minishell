/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:21:05 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/29 15:08:04 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_empty_list(t_list *lst)
{
	if (lst == NULL)
		return (1);
	else
		return (0);
}

int	chain_nb(t_data *data)
{
	int		nb;
	t_token	*tmp;

	tmp = data->token;
	nb = 0;
	while (tmp->type < 4)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}
