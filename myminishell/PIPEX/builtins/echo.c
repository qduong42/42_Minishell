#include "../pipex.h"

static int	strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i); 
}

int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	i = 1;
	n_option = 0;
	if (strstrlen(args) > 1)
	{
		while (!ft_strncmp(args[i], "-n", 2))
		{
			n_option = 1;
			i++;
		}
		while (args[i] && args[i + 1])
		{
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		if (args[i])
			ft_putstr_fd(args[i], 1);
	}
	if (!n_option)
		ft_putstr_fd("\n", 1);
	return (0);
}
