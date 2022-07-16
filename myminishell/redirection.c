#include "minishell.h"

void	ft_catall(char *dst, const char *src)
{
	int i = 0;
	int dest_len = ft_strlen(dst);
	while (src[i])
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
}

//string is everything after '<' s is for whole sub_string
//fixed to work with ' && " by trimming, frees the allocated string after open.
char	*del_re(char *sub, int len_fn, int end, int be_r)
{
	int len;
	len = 0;
	len = ft_strlen(sub);
	// printf("Len of sub:%d\n", len);
	// printf("Len of len_fn:%d\n", len_fn);
	// printf("End(i):%d\n", end);
	// printf("be_r:%d\n", be_r);
	char *temp;
	temp = ft_calloc(1, len - len_fn + 1);
	ft_strlcpy(temp, sub, be_r);
	// printf("temp:1:%s\n", temp);
	ft_catall(temp, sub + end);
	// printf("temp:2:%s\n", temp);
	free(sub);
	return (temp);
}

void	input(t_pipe *sp, char *temp)
{
	if (sp->fd_in > 2)
		close(sp->fd_in);
	sp->fd_in = open(temp, O_RDONLY);
	printf("fd_in:%d\n", sp->fd_in);
	if (sp->fd_in == -1)
		perror(temp);
}

void	output(t_pipe *sp, char *temp)
{
	if (sp->fd_out > 2)
		close(sp->fd_out);
	sp->fd_out = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sp->fd_out == -1)
		perror(temp);
}

void	append(t_pipe *sp, char *temp)
{
	if (sp->fd_out > 2)
		close(sp->fd_out);
	sp->fd_out = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (sp->fd_out == -1)
		perror(temp);
}

char	*iohandler(t_pipe *sp, int i, int id)
{
	char fn[256];
	int y = 0;
	int z = 1;
	int be_r = i;
	if (id == 3 || id == 4)
		z++;
	i++;
	while (sp->sub[i] && sp->sub[i] == ' ')
	{
		z++;
		i++;
	}
	while (sp->sub[i] && sp->sub[i] != ' ' && sp->sub[i] != '<' && sp->sub[i] != '>')
	{
		fn[y] = sp->sub[i];
		i++;
		y++;
		z++;
	}
	fn[y] = '\0';
	char *temp;
	temp = ft_strtrim(fn,"\"'");
	// printf("error handling:%p\n", temp);
	// printf("Filename string:%s\n", temp);
	if (id == 1)
		input(sp, temp);
	if (id == 2)
		output(sp, temp);
	if (id == 3)
		sp->hd = temp;
	if (id == 4)
		append(sp, temp);
	sp->sub = del_re(sp->sub, z, i, be_r);
	if (id != 3)
	{
		// printf("TEMP FREED\n");
		free (temp);
	}
	return (sp->sub);
}
