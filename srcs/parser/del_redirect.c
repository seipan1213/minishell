
// #include "../../includes/parser.h"

// void	del_filename(t_token *list)
// {
	
// }

// void	del_redirect(t_redirect **list)
// {
// 	t_redirect	*tmp;
// 	t_redirect	*now;

// 	if (!*list)
// 		return ;
// 	now = *list;
// 	while (now)
// 	{
// 		tmp = now;
// 		del_filename(tmp->filename);
// 		free(tmp);
// 		now = now->next;
// 	}
// }