/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:09 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:02:09 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

char	*expand_init(int *i, int *j)
{
	*i = -1;
	*j = 0;
	return (ft_strdup(""));
}

char	*expand_null(char *str, char *front)
{
	if (front[0] == '\0' && !ft_strchr(str, '\"'))
	{
		free(front);
		return (NULL);
	}
	return (front);
}

int	add_cnt_stop_env(char *str)
{
	int	i;

	i = 0;
	while (!ft_isspace(str[i]) && str[i] != '\"' && str[i] != '?'\
				&& str[i] != '=' && !(i != 0 && str[i] == '$') && str[i])
		i++;
	if (str[i] == '?' && str[i - 1] == '$')
		i++;
	return (i);
}

char	*expand(char *str)
{
	int		i;
	int		j;
	char	*front;
	char	*env;

	if (!(front = expand_init(&i, &j)))
		return (NULL);
	while (str[++i])
	{
		front = sub_quote(front, str, &i, &j);
		if (str[i] == '$')
		{
			env = expand_env(str + i);
			i += add_cnt_stop_env(str + i);
			if (!(front = front_join(front, env)))
				return (NULL);
			j = i--;
		}
		if (!str[i])
			break ;
	}
	if (i != j)
		front = sub_join(front, str, i, j);
	return (expand_null(str, front));
}
