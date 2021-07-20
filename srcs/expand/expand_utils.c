/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:14 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:02:14 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

char	*expand_env(char *str)
{
	char	*key;
	char	*env;
	int		i;

	i = 0;
	i += add_cnt_stop_env(str + i);
	key = ft_substr(str, 1, i - 1);
	if (!key)
		return (NULL);
	env = get_env(key, g_data.envs);
	if (!env)
	{
		if (!(ft_strncmp(str, "$?", 2)))
			env = ft_itoa(g_data.status);
		else if (ft_isspace(str[1]) || !str[1] || str[1] == '$')
			env = ft_strdup("$");
		else
			env = ft_strdup("");
	}
	else
		env = ft_strdup(env);
	free(key);
	return (env);
}

char	*front_join(char *front, char *str)
{
	char	*tmp;

	if (!front || !str)
		return (NULL);
	tmp = front;
	front = ft_strjoin(front, str);
	free(tmp);
	free(str);
	return (front);
}

char	*sub_join(char *front, char *str, int i, int j)
{
	char	*tmp;

	tmp = ft_substr(str, j, i - j);
	if (!tmp)
		return (NULL);
	front = front_join(front, tmp);
	return (front);
}

void	expand_sub_sp(t_token **lst, char *str, int *i, int *j)
{
	char	*tmp;
	int		tmp_i;

	tmp_i = *i;
	if (str[(*i) - 1] == '$' && (str[*i] == '\'' || str[*i] == '\"'))
		tmp_i--;
	tmp = ft_substr(str, *j, tmp_i - *j);
	if (!tmp)
		exit_error(MALLOCERR, NULL, 1);
	*j = *i;
	expand_str(lst, tmp, 1);
	free(tmp);
	if (!(*lst)->str)
		exit_error(MALLOCERR, NULL, 1);
}

void	expand_sub(t_token **lst, char *str, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(str, *j, *i - *j);
	if (!tmp)
		exit_error(MALLOCERR, NULL, 1);
	*j = *i;
	if (str[*i] == '\'')
		(*lst)->str = front_join((*lst)->str, tmp);
	else
	{
		expand_str(lst, tmp, 0);
		free(tmp);
	}
	if (!(*lst)->str)
		exit_error(MALLOCERR, NULL, 1);
}
