#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../libft/libft.h"

#define STDERR 2
#define MINISHELL "MINISHELL$ "

void minishell(char **envp);
void sig_int_input();
void sig_quit_input();
int launch(char *line, char **envp);
void sig_input();
void sig_ign();
int launch(char *line, char **envp);

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell(envp);
}

void minishell(char **envp)
{
	char *line;
	int ret;

	ret = 0;
	while (1)
	{
		ft_putstr_fd(MINISHELL, STDERR);
		sig_input();
		if ((get_next_line(0, &line) == 0))
		{
			ft_putstr_fd("exit\n", STDERR);
			exit(ret);
		}
		sig_ign();
		ret = launch(line, envp);
		free(line);
	}
}

void sig_input()
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(1);
	}
	if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(1);
	}
}

void sig_ign()
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN == SIG_ERR))
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(1);
	}
}

int launch(char *line, char **envp)
{
	char *argv[] = {NULL, NULL};
	int pid;
	int status;
	char *tmp;
	char *path;

	argv[0] = line;

  // builtinコマンドか判定
  if (builtin_table(line))
    return (builtin_function(argv, envp))
	pid = fork();
	// forkエラー処理。
	if (pid < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	// 子プロセスの処理
	if ((pid == 0)
	{
		errno = 0;
		path = ft_strjoin("/bin/", line);
		// 実行できるbinallyがpathに存在すればexecveはEXITする
		execve(path, argv, envp);
		// 実行できるbinallyが存在しなかった場合
		if (errno)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(errno);
		}
	}
	// 親プロセスの処理
	if (waitpid(pid, &status, 0) < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(errno);
	}
	return (WEXITSTATUS(status));
}

bool builtin_table(char *line)
{
	if (!ft_strncmp(line, "echo", 5))
		return (true);
	if (!ft_strncmp(line, "exit", 5))
		return (true);
	return (false);
}

int builtin_function(char **argv, char **envp)
{
	if (!ft_strncmp(argv[0], "echo", 5))
		return (msh_echo());
	if (!ft_strncmp(argv[0], "exit", 5))
		return (msh_exit());
}