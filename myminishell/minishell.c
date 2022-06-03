#include "minishell.h"

t_list *create_env_list(char **envp)
{
	t_list *a;
	int	i;

	a = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&a, ft_lstnew(envp[i]));
		i++;
	}
	return (a);
}

// void	print_list(t_list *to_print)
// {
// 	t_list *current;
// 	current = to_print;
// 	while (current->next != NULL)
// 	{
// 		printf("%s\n", current->content);
// 		current = current->next;
// 	}
// 	printf("%s\n", current->content);
// }

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	while (69)
	{
		t_shell s;
		s.env = create_env_list(envp);
		//print_list(s.env);
		s.line = readline(PROMPT);
		add_history(s.line);
		if (!ft_strncmp(s.line, "exit", ft_strlen(s.line)))
			exit (0);
	}
	return (0);
}

// add_history functionality is built in, so further work required.