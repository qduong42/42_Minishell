#include "minishell.h"

int	unset(char **args, t_list **env)
{
	int	i;
	t_list	*tmp;
	t_list	*dragging;

	if (!args[1])
		error_msg("Unset: invalid number of arguments\n");
	else
	{
		i = 1;
		while (args[i])
		{
			tmp = *env;
			dragging = NULL;
			while (1)
			{
				if (!tmp)
					return (1);
				if (!ft_strncmp(tmp->content, args[i], ft_strlen(args[i])))
				{
					if (!dragging)
						*env = tmp->next;
					else
						dragging->next = tmp->next;
					free(tmp->content);
					free(tmp);
					break ;
				}
				dragging = tmp;
				tmp = tmp->next;
			}
			i++;
		}
	}
	return (0);
}
