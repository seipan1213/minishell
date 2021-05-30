#include "../../includes/env.h"

static void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_envs(t_env *envs)
{
	t_env	*top;
	t_env	*back;
	char	*tmp;

	top = envs;
	while (top)
	{
		back = top->next;
		while (back)
		{
			if (ft_strcmp(top->name, back->name) > 0)
			{
				swap_str(&top->name, &back->name);
				swap_str(&top->value, &back->value);
			}
			back = back->next;
		}
		top = top->next;
	}
	return ;
}