# include "../pipex.h"

int	ft_env(t_pipe *cmd, t_list *env)
{
	if (cmd->argv[1] != NULL)
		return (127);
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}
