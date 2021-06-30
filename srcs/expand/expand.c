#include "../../includes/expand.h"

char	*expand_init(int *i, int *j)
{
	char	*str;

	*i = -1;
	*j = 0;
	str = ft_strdup("");
	if (!str)
		*i = -100;
	return (str);
}

char	*expand_null(char *str, char *front)
{
	if (!front)
		return (NULL);
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

char	*expand(char *str)
{
	int		i;
	int		j;
	char	*front;
	char	*env;

	front = expand_init(&i, &j);
	while (i >= -1 && str[++i])
	{
		front = sub_quote(front, str, &i, &j);
		if (str[i] == '$')
		{
			env = expand_env(str + i);
			i += add_cnt_stop_env(str + i);
			front = front_join(front, env);
			if (!front)
				return (NULL);
			j = i--;
		}
		if (!str[i])
			break ;
	}
	if (i >= -1 && i != j)
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