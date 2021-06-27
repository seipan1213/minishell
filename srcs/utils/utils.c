#include "../../includes/utils.h"

int		is_strdigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		flag = 1;
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0' && flag)
		return (1);
	return (0);
}

char	*strjoin_free(char *front, char *back)
{
	char	*tmp;

	if (front && !back)
	{
		tmp = ft_strdup(front);
		free(front);
		return (tmp);
	}
	if (!front && back)
	{
		tmp = ft_strdup(back);
		free(back);
		return (tmp);
	}
	tmp = front;
	front = ft_strjoin(front, back);
	free(tmp);
	free(back);
	return (front);
}
