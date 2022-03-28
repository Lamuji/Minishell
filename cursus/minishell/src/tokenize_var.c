/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:28:18 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/24 15:32:29 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static char	*copy_word(char *str, int end, int start)
{
	char	*new_word;
	int		i;

	i = 0;
	new_word = (char *)malloc(sizeof(char) * (end - start + 1));
	manager(new_word, 0);
	if (!new_word)
		return (NULL);
	while (start < end)
	{
		new_word[i] = str[start];
		i++;
		start++;
	}
	new_word[i] = '\0';
	return (new_word);
}

static int	create_empty_str_in_new_node(t_token **tk_lst)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	manager(str, 0);
	if (!str)
		return (FAILURE);
	str[0] = '\0';
	lst_add_back_tk(tk_lst, lstnew_tk(str, VAR, DEFAULT));
	return (SUCCESS);
}

static t_token	*split_var(char *str, t_token *tk_lst)
{
	int		i;
	int		start;
	char	*new_word;

	i = 0;
	if (!str[i])
		create_empty_str_in_new_node(&tk_lst);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			start = i;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_word = copy_word(str, i, start);
		lst_add_back_tk(&tk_lst, lstnew_tk(new_word, VAR, DEFAULT));
	}
	return (tk_lst);
}

int	tokenize_var(t_data *data)
{
	t_token	*tmp;
	t_token	*new_lst;
	t_token	*tk_lst;

	tmp = data->token;
	new_lst = NULL;
	tk_lst = NULL;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			new_lst = split_var(tmp->token, tk_lst);
			tmp = insert_lst_between(&data->token, tmp, new_lst);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
