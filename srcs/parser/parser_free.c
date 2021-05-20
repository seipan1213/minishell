
// #include "../../includes/parser.h"

// void	del_token(void *ptr)
// {
// 	free(((t_token *)ptr)->val);
// 	((t_token *)ptr)->val = NULL;
// 	free(ptr);
// 	ptr = NULL;
// }

// void	exit_token(t_token *t)
// {
// 	t_token	*tmp;
// 	while (t)
// 	{
// 		tmp = t->next;
// 		ft_lstdelone((t_list *)t, del_token);
// 		t = tmp;
// 	}
// }