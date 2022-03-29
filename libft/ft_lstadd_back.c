/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:35:39 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/25 20:35:47 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p_courant;

	p_courant = *alst;
	if (*alst)
	{
		while (p_courant -> next != NULL)
			p_courant = p_courant -> next;
		p_courant -> next = new;
		p_courant = new;
	}
	else
		*alst = new;
}
