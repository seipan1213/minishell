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