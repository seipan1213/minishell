#ifndef CONST_H
# define CONST_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "MINISHELL$ "
# define ERR_MSH "minishell: "
# define MALLOCERR "malloc error..."
# define SYNTAXERR "syntax error..."
# define QUOTEERR "quote is not close..."
# define NUMERR "numeric argument required"
# define HD_TMPFILE ".heredoc_tmpfile"
# define UNSET_ERR "unset: not enough arguments"

#endif