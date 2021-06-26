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

int		add_cnt_stop_env(char *str)
{
	int	i;

	i = 0;
	while (!ft_isspace(str[i]) && str[i] != '\"' && str[i] != '?'
				&& str[i] != '=' && !(i != 0 && str[i] == '$') && str[i])
				i++;
	if (str[i] == '?' && str[i - 1] == '$')
		i++;
	return (i);
}

char	*expand(char *str, t_env *envs)
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
			env = expand_env(str + i, envs);
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

/* int	main()
{
	t_env	*envs;
	char	*str;

	envs = envs_init();
	str = ft_strdup("'dasdd'");
	printf("%s\n\n", expand(str, envs));
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
	str = ft_strdup("$DQ");//expot DQ="\"dq\""
	printf("%s\n\n", expand(str, envs));
} */