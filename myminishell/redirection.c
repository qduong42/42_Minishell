#include "minishell.h"

//string is everything after '<' s is for whole sub_string

int	input_handle(t_pipe *s, int i)
{
	char fn[256];
	int y = 0;
	while (s->sub[i])
	{
		while (s->sub[i] == ' ')
			i++;
		while (s->sub[i]!= ' ')
		{
			fn[y] = s->sub[i];
			i++;
			y++;
		}
		fn[y] = '\0';
		printf("CHAR LEFTOVER%c\n", s->sub[i]);
		printf("Filename string:%s\n", fn);
	}
	return (i);
}