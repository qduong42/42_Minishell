#include "../pipex.h"

static int	env_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z') || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
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
			if (!env_name(args[i]))
			{
				error_msg("Unset: invalid env variable name\n");
				return (1);
			}
			tmp = *env;
			dragging = NULL;
			while (1)
			{
				if (!tmp)
					break;
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
