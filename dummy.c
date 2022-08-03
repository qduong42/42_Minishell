#include <stdio.h>
int		quote_we_count(char *str, int i, char search);

# define SQ '\''
# define DQ '"'

int	inside_diff(char *line, int pos, char quote)
{
	int		num;
	int		i;
	char	negative;

	if (quote == '\'')
		negative = '"';
	else if (quote == '"')
		negative = '\'';
	else
		return (0);
	i = 0;
	num = 0;
	while (i < pos)
	{
		if (quote_we_count(line, i, negative))
			num++;
		i++;
	}
	if (num % 2 == 1)
		return (1);
	return (0);
}

int	inside_same(char *line, int pos, char quote)
{
	int	qq_num;
	int	i;

	i = 0;
	qq_num = 0;
	while (i < pos)
	{
		if (quote_we_count(line, i, quote))
			qq_num++;
		i++;
	}
	if (qq_num % 2 == 1)
		return (1);
	return (0);
}

int		quote_we_count(char *str, int i, char search)
{
	if (str[i] == search)
	{
		if (!(inside_diff(str, i, str[i]) && !inside_same(str, i, str[i])))
			return (1);
	}
	return (0);
}

int	delete_quote(char *str, int i, char quote)
{
	if (inside_diff(str, 4, '\"') && !inside_same(str, 4,'\"'))
		return (0);
	else
		return (1);
}

// int	main(void)
// {
// 	char str[69] = "\"\'\" \"\'\"";

// 	printf("%s\n", str);
// 	if (inside_diff(str, 4, '\"') && !inside_same(str, 4,'\"'))
// 		printf("NOT WORKING YET\n");
// 	else
// 		printf("RUN MORE TESTS\n");
// 	if(!inside_same(str, 2, '\"'))
// 		printf("Is working\n");
// }