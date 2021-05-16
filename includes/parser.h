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

typedef struct	s_command{
	char				*arg;
	char				*rd;
	struct s_command	*next;
}				t_command;

typedef struct	astNode {
	int					type;
	t_command			*cmd;
	struct astNode	*left;
	struct astNode	*right;
}				astNode;

/*
	t_list	*cmdline;
	t_pipe	*job;

	cmdline->content = job;

	((t_pipe *)cmdline->content)->argv = "echo" "aaa"
	((t_pipe *)cmdline->content)->rd = ">" "file1"
*/

/** t_token */

typedef struct	s_token {
	char			*val;
	int				type;
	struct s_token	*next;
}				t_token;

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
t_command	*new_cmd_node(t_token **tokens, astNode **node);

#endif