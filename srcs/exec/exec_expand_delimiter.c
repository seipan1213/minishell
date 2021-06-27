#include "../../includes/exec.h"

t_quote	*delimiter_point_init(void)
{
	t_quote	*new;

	new = (t_quote *)malloc(sizeof(t_quote));
	new->start = 0;
	new->end = 0;
	new->quote = '\0';
	return (new);
}

int	is_quote(char c)
{
	return (c == SQUOTE || c == DQUOTE);
}

char	*substr_quote(t_quote *point, char *deli)
{
	char	*substr;

	point->end++;
	point->start = point->end;
	while (deli[point->end] != point->quote && deli[point->end])
		point->end++;
	substr = ft_substr(deli, point->start, point->end - point->start);
	if (deli[point->end])
	{
		point->start = point->end + 1;
		point->end = point->start;
	}
	return (substr);
}

char	*expand_delimiter(char *deli)
{
	char	*front;
	char	*back;
	char	*new_deli;
	t_quote	*point;

	new_deli = NULL;
	point = delimiter_point_init();
	while (deli[point->end])
	{
		while (!is_quote(deli[point->end]) && deli[point->end])
			point->end++;
		point->quote = deli[point->end];
		front = ft_substr(deli, point->start, point->end - point->start);
		new_deli = strjoin_free(new_deli, front);
		if (point->quote)
		{
			back = substr_quote(point, deli);
			new_deli = strjoin_free(new_deli, back);
		}
	}
	free(point);
	return (new_deli);
}