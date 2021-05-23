#include "../../includes/expansion.h"

char	*expand_str(char *str, t_env *envs)
{
	char	*key;
	char	*env;
	int		i;

	i = 0;
	if (str[i] != '$')
		return (NULL);
	while (!ft_isspace(str[i]) && str[i])
		i++;
	if (!(key = ft_substr(str, 1, i - 1)))
		return (NULL);
	env = ft_strdup(search_env(key, envs)->value);
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

char	*expand(char *str, t_env *envs)
{
	int		i;
	int		j;
	char	*front;
	char	*env;
	char	*tmp;

	i = 0;
	front = ft_strdup("");
	j = i;
	while (str[i])
	{
		while (str[i] != '\'' && str[i] != '$' && str[i])
			i++;
		if (str[i] == '\'' && ++i)
			while (str[i] != '\'')
				i++;
		else if (str[i] == '$')
		{
			if (!(tmp = ft_substr(str, j, i - j)))
				return (NULL);
			if (!(front = front_join(front, tmp)))
				return (NULL);
			env = expand(str + i, envs);
			while (!ft_isspace(str[i]) && str[i])
				i++;
			if (!(front = front_join(front, env)))
				return (NULL);
			j = i;
		}
		i++;
	}
	if (i != j)
	{
		if (!(tmp = ft_substr(str, j, i - j)))
			return (NULL);
		if (!(front = front_join(front, tmp)))
			return (NULL);
	}
	return (front);
}

/* int	main()
{
	t_env	*envs;
	char	*str;


	envs = envs_init();
	str = ft_strdup("$SHELL");
	printf("%s\n\n", expand(str, envs));
	str = ft_strdup("$USER");
	printf("%s\n\n", expand(str, envs));
	str = ft_strdup("'$SHELL'");
	printf("%s\n\n", expand(str, envs));
	str = ft_strdup("dasdsa DSAD $SHELL dasda");
	printf("%s\n\n", expand(str, envs));
	str = ft_strdup("$SHELL \n$NAME \n$USER ");
	printf("%s\n\n", expand(str, envs));
	str = ft_strdup("STRING");
	printf("%s\n\n", expand(str, envs));
} */