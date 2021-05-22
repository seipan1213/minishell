
#include "../../includes/exec.h"

int		lst_len(t_token *token)
{
	t_token		*list;
	int			token_len = 0;

	list = token;
	while (list)
	{
		list = list->next;
		token_len++;
	}
	return (token_len);
}

char	**to_wchar(t_token *token)
{
	t_token		*list;
	int			token_len = 0;
	int			i;
	char		**wp;

	token_len = lst_len(token);
	wp = (char **)malloc((token_len + 1) * sizeof(char *));
	wp[token_len] = NULL;
	list = token;
	i = 0;
	while (i < token_len)
	{
		wp[i] = ft_strdup(list->str);
		list = list->next;
		i++;
	}
	return (wp);
}

// int main()
// {
// 	char		**wp;
// 	t_token		*tokens;

// 	tokens = NULL;
// 	tokens = token_init();
// 	print_tokens(tokens);
// 	ft_putstr_fd("start\n", 1);
// 	wp = to_wchar(tokens);
// 	printf("%s\n", *wp);
// 	while (*wp)
// 	{
// 		printf("%s\n", *wp);
// 		wp++;
// 	}
// 	return(0);
// }