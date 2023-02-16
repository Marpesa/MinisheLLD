#include "minisheLLD.h"

static int	is_nflag(char *arg)
{
	if (*arg != '-' || *arg == '\0')
		return (0);
	arg++;
	if (*arg != 'n')
		return (0);
	while (*arg && *arg == 'n')
		arg++;
	if (*arg == '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **command, int fd)
{
	int	nflag;

	nflag = 0;
	while (*command && is_nflag(*command))
	{
		nflag = 1;
		command++;
	}
	while (*command && *(command + 1))
	{
		ft_putstr_fd(*command, fd);
		if (*(command + 1))
			ft_putstr_fd(" ", fd);
		command++;
	}
	if (*command)
		ft_putstr_fd(*command, fd);
	if (!nflag)
		ft_putendl_fd("", fd);
	//if (exit)
		//free_and_exit(0);
	return (0);
}
