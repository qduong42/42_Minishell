#include "../pipex.h"

char	**lst_to_strstr(t_list *env)
{
	char	**ret;
	int		i;
	t_list	*tmp;

	ret = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	tmp = env;
	while (1)
	{
		if (i == ft_lstsize(env))
		{
			ret[i] = NULL;
			return (ret);
		}
		ret[i] = malloc(sizeof(char) * (ft_strlen(tmp->content) + 1));
		ft_strlcpy(ret[i], tmp->content, ft_strlen(tmp->content) + 1);
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}

int		create_hd(char *delim)
{
	int		fd;
	char	*line;

	while (1)
	{
		fd = open("temp_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, delim, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
		close(fd);
	}
	return (fd);
}
