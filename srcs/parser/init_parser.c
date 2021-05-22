
#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void		put_token(t_token *t, char *val, int type)
{
	t->str = ft_strdup(val);
	t->type = (t_ttype)type;
}

t_token		*gen_token(char *val, int type)
{
	t_token	*new_t;

	new_t = NULL;
	new_t = (t_token *)malloc(sizeof(t_token));
	put_token(new_t, val, type);
	new_t->next = NULL;
	return(new_t);
}

// void		print_token(t_token *t)
// {
// 	if (t == NULL)
// 		return ;
// 	while (t)
// 	{
// 		printf("TOKEN | type: %-2d  name:[%s] \n", t->type, t->val);
// 		t = t->next;
// 	}
// 	printf("last token: %p\n", t);
// }

// t_token		*last_token(t_token *t)
// {
// 	t_token *last;

// 	last = NULL;
// 	if (!t)
// 		return (NULL);
// 	last = t;
// 	while (last->next != NULL)
// 		last = last->next;
// 	return (last);
// }

// int		adb_token(t_token **lst, t_token *new)
// {
// 	t_token	*last;

// 	if (!lst || !new)
// 		return (0);
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return (0);
// 	}
// 	last = last_token(*lst);
// 	last->next = new;
// 	new->next = NULL;
// 	return (1);
// }

/*
t_token		*token_init()
{
	int		ret;
	t_token	*tmp;
	t_token *lst;

	lst = NULL;
	ret = 0;
	tmp = gen_token("echo", STR);
	adb_token(&lst, tmp);

	tmp = gen_token("aaa", STR);
	adb_token(&lst, tmp);

	tmp = gen_token("|", PIPE);
	adb_token(&lst, tmp);

	tmp = gen_token("echo", STR);
	adb_token(&lst, tmp);

	tmp = gen_token("bbb", STR);
	adb_token(&lst, tmp);

	tmp = gen_token("|", PIPE);
	adb_token(&lst, tmp);

	tmp = gen_token("echo", STR);
	adb_token(&lst, tmp);

	tmp = gen_token("ccc", STR);
	adb_token(&lst, tmp);

	return (lst);
}
*/

// int main()
// {
// 	t_token		*tokens;
// 	// t_list	*semi;
// 	// t_pipe	*pipe;

// 	tokens = NULL;
// 	// tokens = token_init();
// 	print_token(tokens);

	

// 	// del_token(list);
// 	// system("leaks a.out");
// 	return(0);
// }