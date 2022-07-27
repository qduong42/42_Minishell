#include "minishell.h"

int	special_token(char c)
{
	char	specials[4];
	int		i;

	specials[0] = '<';
	specials[1] = '>';
	specials[2] = '|';
	specials[3] = '$';
	i = 0;
	while (i < 4)
	{
		if (c == specials[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_whitespace(char c)
{
	char	white[5];
	int		i;

	white[0] = ' ';
	white[1] = '\t';
	white[2] = '\r';
	white[3] = '\v';
	white[4] = '\f';
	i = 0;
	while (i < 5)
	{
		if (c == white[i])
			return (1);
		i++;
	}
	return (0);
}

int	valid_name(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (!special_token(line[i]) && !ft_whitespace(line[i]))
			return (1);
		if (special_token(line[i]))
			return (0);
		i++;
	}
	return (0);
}

int	unclosed_quotes(char *line)
{
	int	q_num;
	int	qq_num;
	int	i;

	i = 0;
	q_num = 0;
	qq_num = 0;
	while (line[i])
	{
		if (q_num % 2 == 0)
		{
			if (line[i] == '"')
				qq_num++;
		}
		if (qq_num % 2 == 0)
		{
			if (line[i] == '\'')
				q_num++;
		}
		i++;
	}
	if (q_num % 2 == 1 || qq_num % 2 == 1)
		return (1);
	return (0);
}

int	outside_quotes(char *line, int pos)
{
	int	q_num;
	int	qq_num;
	int	i;

	i = 0;
	q_num = 0;
	qq_num = 0;
	while (i < pos)
	{
		if (q_num % 2 == 0)
		{
			if (line[i] == '"')
				qq_num++;
		}
		if (qq_num % 2 == 0)
		{
			if (line[i] == '\'')
				q_num++;
		}
		i++;
	}
	if (q_num % 2 == 1 || qq_num % 2 == 1)
		return (0);
	return (1);
}

void	file_exists(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return ;
	}
	close(fd);
}

int	special(char *line)
{
	if (line[0])
	{
		if (line[0] == '<' && line[1] == '<')
			return (2);
		if (line[0] == '>' && line[1] == '>')
			return (2);
	}
	if (special_token(line[0]))
		return (1);
	return (0);
}

int	single_dollar(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (outside_quotes(line, i))
		{
			if (line[i] == '$')
			{
				if(line[i + 1] == ' ')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	unexpected_newline(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if(special(line + i))
		{
			j = i + special(line + i);
			while (line[j] == ' ')
				j++;
			if (!line[j])
				return (1);
		}
		i++;
	}
	return (0);
}

int	consecutive_specials(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (outside_quotes(line, i))
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return (1);
			if (line[i] == '$' && line[i + 1] == '$')
				return (1);
			if (special(line + i) && line[i] != '|')
			{
				j = i + special(line + i);
				while (line[j] == ' ')
					j++;
				if (special(line + j) && line[j] != '$')
					return (1);
			}
		}
		i++;
	}
	return (0);
}
