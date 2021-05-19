/**
* @file parser.h

* @brief This is API for Sate machine
**/

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"
#include "lexer.h"

/**
 *
	<command line>	::=  	<job>
						|	<job> '&'
						| 	<job> '&' <command line>
						|	<job> ';'
						|	<job> ';' <command line>
	<job>			::=		<command>
						|	< job > '|' < command >
	<command>		::=		<simple command>
						|	<simple command> '<' <filename>
						|	<simple command> '>' <filename>
	<simple command>::=		<pathname>
						|	<simple command>  <token>
 *
**/

// typedef struct	s_token {
// 	char				*val;
// 	int					type;
// 	struct s_token		*next;
// }				t_token;

typedef struct	s_command{
	t_token				*arg;
	t_token				*rd;
	struct s_command	*next;
}				t_command;

typedef struct	astNode {
	int					type;
	t_command			*cmd;
	struct astNode		*left;
	struct astNode		*right;
}				astNode;

# define TRUE 1
# define FALSE 0

# define STR 0      // 文字列
# define RDIR 1     // >
# define RRDIR 2    // >>
# define LDIR 3     // <
# define LLDIR 4    // <<
# define LLLDIR 5   // <<<
# define SPACE 6    //  
# define SQUOTE 7   // '
# define DQUOTE 8   // "
# define PIPE 9     // |
# define DPIPE 10   // ||
# define AND 11     // &
# define DAND 12    // &&
# define SCOLON 13  // ;
# define DSCOLON 14 // ;;
# define DOLL 15    // $ 使わなかった
# define ESC 16     // \ 
# define SSTR 17    // single_quote内の文字列。 使わなかった。
# define RINT 18    // 2>file の[2]

void		del_token(void *ptr);
void		exit_token(t_token *t);
t_token		*token_init();
void		print_token(t_token *t);
t_token		*gen_token(char *val, int type);
void		set_cmd_args(t_token **tokens, t_command *cmd);
astNode		*new_cmd_node();
astNode		*new_parent_node(int type, astNode *left, astNode *right);
bool		is_type(t_token **tokens, int type);
bool		is_rd(int type);
void		set_cmd_token(t_token *src, t_token **args);
bool		set_cmd_rd(t_token **tokens, t_command *cmd);
bool		parser(t_token **tokens, astNode **node);

#endif