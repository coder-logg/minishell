#include <termios.h>
#include "../minishell.h"

void ctrl_ign(void)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	ts.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

static void	handle_sigint(int status)
{
	(void)status;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void print_exit(int i)
{
	(void)i;
	write(1, "yuhi", 3);
	rl_replace_line("yhiujo", 1);
	rl_redisplay();
//	ft_putstr_fd("exit", 1);

}

void	main_signals(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void)sig;
}

void	signal_non_interactive(void)
{
	signal(SIGINT, signal_pipes);
	signal(SIGQUIT, signal_pipes);
}

void	signal_in_forks(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, exit);
	signal(SIGQUIT, SIG_DFL);
}