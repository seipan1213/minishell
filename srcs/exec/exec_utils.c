/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:55 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/17 20:32:56 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_builtin(char **args)
{
	int			i;
	const char	*builtin[] = {"echo", "cd", "pwd", \
								"export", "unset", \
									"env", "exit", NULL};

	i = 0;
	while (builtin[i])
	{
		if (ft_strcmp(args[0], builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	token_lst_len(t_token *token)
{
	t_token		*list;
	int			token_len;

	token_len = 0;
	list = token;
	while (list)
	{
		if (list->str)
			token_len++;
		list = list->next;
	}
	return (token_len);
}

char	**token_to_args(t_token *token)
{
	t_token		*list;
	int			token_len;
	int			i;
	char		**args;

	list = token;
	i = 0;
	while (list)
	{
		expand(&list);
		list = list->next;
	}
	token_len = token_lst_len(token);
	args = (char **)malloc((token_len + 1) * sizeof(char *));
	args[token_len] = NULL;
	while (token)
	{
		if (token->str)
		{
			args[i] = ft_strdup(token->str);
			i++;
		}
		token = token->next;
	}
	return (args);
}
