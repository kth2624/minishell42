#include "minishell.h"

static void	child_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "^C\n", 3);
		g_status = 130;
	}
	if (signo == SIGQUIT)
	{
		write(2, "^\\Quit: 3\n", ft_strlen("^\\Quit: 3\n"));
		g_status = 131;
	}
}

void	handle_signal_child(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		printf("\n");
		rl_redisplay();
		return ;
	}
	if (signo == SIGQUIT)
		return ;
}

int	handle_signal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}
