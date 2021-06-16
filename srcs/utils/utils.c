#include "../../includes/utils.h"

int		is_strdigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			flag = 1;
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	if (flag)
		return (1);
	return (0);
}