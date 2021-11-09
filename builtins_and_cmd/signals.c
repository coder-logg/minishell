#include <termios.h>
#include "../minishell.h"

void ctrl_ign(void)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	ts.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

static void	handle_sigint()
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

void	main_signals(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	change_global()
{
	signal(SIGINT, SIG_IGN);
	write(2, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	g_status = 130;
}

void	signal_pipes_cmd(void)
{
	signal(SIGINT, change_global);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
