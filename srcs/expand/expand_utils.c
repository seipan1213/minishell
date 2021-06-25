#include "../../includes/expand.h"

char	*expand_env(char *str, t_env *envs)
{
	char	*key;
	char	*env;
	int		i;

	i = 0;
	if (str[i] != '$')
		return (NULL);
	i += add_cnt_stop_env(str + i);
	if (!(key = ft_substr(str, 1, i - 1)))
		return (NULL);
	env = get_env(key, g_data.envs);
	if (!env)
	{
		if (!(ft_strncmp(str, "$?", 2)))
			env = ft_strdup(ft_itoa(g_data.status));
		else if (ft_isspace(str[1]) || !str[1] || str[1] == '\"')
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

	tmp = front;
	front = ft_strjoin(front, str);
	free(tmp);
	free(str);
	return (front);
}

char	*sub_join(char *front, char *str, int i, int j)
{
	char	*tmp;
	char	*w;

	if (!(tmp = ft_substr(str, j, i - j)))
		return (NULL);
	front = front_join(front, tmp);
	return (front);
}

char	*sub_quote(char *front, char *str, int *i, int *j)
{
	while (str[*i] != '\'' && str[*i] != '\"' && str[*i] != '$' && str[*i])
		(*i)++;
	if (str[*i] == '$')
		(*i)--;
	if (*i > *j)
		front = sub_join(front, str, *i, *j);
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		if (str[*i] == '\'' && ++(*i))
		{
			while (str[*i] != '\'')
				(*i)++;
			front = sub_join(front, str, *i, *j + 1);
		}
		*j = (*i) + 1;
	}
	else
		*j = (*i);
	return (front);
}