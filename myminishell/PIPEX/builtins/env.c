# include "../pipex.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
<<<<<<< HEAD:myminishell/PIPEX/buildins/env.c
	return (0);
}
=======
}
>>>>>>> 7c578a878c333ff942db75bcacf465beab56e43d:myminishell/PIPEX/builtins/env.c
