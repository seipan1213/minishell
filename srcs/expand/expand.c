/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:09 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/10 03:19:04 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"
#include "../../includes/lexer.h"

char	*expand_init(t_token **lst, int *i, int *j)
{
	char	*tmp;

	tmp = (*lst)->str;
	(*lst)->str = ft_strdup("");
	*i = -1;
	*j = 0;
	if (!(*lst)->str)
		exit_error(MALLOCERR, NULL, 1);
	return (tmp);
}

void	expand_null(char *str, char **front)
{
	if (*front && *front[0] == '\0' && \
		!ft_strchr(str, '\"') && !ft_strchr(str, '\''))
	{
		free(*front);
		*front = NULL;
	}
}

int	add_cnt_stop_env(char *str)
{
	int	i;

	i = 0;
	while (!ft_isspace(str[i]) && str[i] != '\"' && str[i] != '?'\
				&& str[i] != '=' && str[i] != '\''\
				&& !(i != 0 && str[i] == '$') && str[i])
		i++;
	if (str[i] == '?' && str[i - 1] == '$')
		i++;
	return (i);
}

void	expand(t_token **lst)
{
	int		i;
	int		j;
	char	*str;

	str = expand_init(lst, &i, &j);
	while (str[++i])
	{
		while (str[i] != '\'' && str[i] != '\"' && str[i])
			i++;
		if (i > j)
			expand_sub_sp(lst, str, &i, &j);
		if ((str[i] == '\'' || str[i] == '\"') && ++i)
		{
			while (str[i] != str[j])
				i++;
			j++;
			expand_sub(lst, str, &i, &j);
			j++;
		}
		if (!str[i])
			break ;
	}
	expand_null(str, &(*lst)->str);
	free(str);
}

void	expand_str(t_token **lst, char *str, int flag)
{
	int		i;
	int		j;
	char	*env;

	i = -1;
	j = 0;
	while (i >= -1 && str[++i])
	{
		if (str[i] == '$')
		{
			(*lst)->str = sub_join((*lst)->str, str, i, j);
			env = expand_env(str + i);
			i += add_cnt_stop_env(str + i);
			expand_div(lst, env, flag);
			j = i--;
		}
		if (!str[i])
			break ;
	}
	if (i >= -1 && i != j)
		(*lst)->str = sub_join((*lst)->str, str, i, j);
}
