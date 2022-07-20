/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:09:37 by qduong            #+#    #+#             */
/*   Updated: 2022/07/20 20:27:25 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_catall(char *dst, const char *src)
{
	int	i;
	int	dest_len;

	dest_len = ft_strlen(dst);
	i = 0;
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
	int		len;
	char	*temp;

	len = 0;
	len = ft_strlen(sub);
	printf("Len of sub:%d\n", len);
	printf("Len of len_fn:%d\n", len_fn);
	printf("End(i):%d\n", end);
	printf("be_r:%d\n", be_r);
	temp = ft_calloc(1, len - len_fn + 1);
	ft_strlcpy(temp, sub, be_r);
	printf("temp:1:%s\n", temp);
	ft_catall(temp, sub + end);
	printf("temp:2:%s\n", temp);
	free(sub);
	return (temp);
}

void	input(t_pipe *sp, char *temp, int in)
{
	if (sp->fd_in > 2)
		close(sp->fd_in);
	if (in != 0)
		sp->fd_in = open(temp, O_RDONLY);
	// printf("fd_in:%d\n", sp->fd_in);
	if (sp->fd_in == -1)
	{
		perror(temp);
		exit_status = 1;
	}
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

// char	*filename(t_pipe *sp, int *i, int *z)
// {
// 	char	*fn;
// 	int		y;

// 	y = 0;
// 	fn = malloc(256);
// 	*i ++;
// 	while (sp->sub[*i] && sp->sub[*i] == ' ')
// 	{
// 		*z++;
// 		*i++;
// 	}
// 	while (sp->sub[*i] && sp->sub[*i] != ' ' && sp->sub[*i] != '<' && sp->sub[*i] != '>')
// 	{
// 		fn[y] = sp->sub[*i];
// 		*i++;
// 		y++;
// 		*z++;
// 	}
// 	fn[y] = '\0';
// 	return (fn);
// }

char	*iohandler(t_pipe *sp, int i, int id, int in)
{
	char	fn[256];
	int		y;
	int		z;
	int		be_r;

	y = 0;
	z = 1;
	be_r = i;
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
	char	*temp;
	// char	*fn;
	// fn = filename(sp, &i, &z);
	temp = ft_strtrim(fn, "\"'");
	// free (fn);
	// printf("error handling:%p\n", temp);
	printf("Filename string:%s\tID:%d\tIN%d\n", temp, id, in);
	if (id == 1)
		input(sp, temp, in);
	if (id == 2)
		output(sp, temp);
	if (id == 3)
		sp->hd = temp;
	if (id == 4)
		append(sp, temp);
	sp->sub = del_re(sp->sub, z, i, be_r + 1);
	if (id != 3)
		free (temp);
	return (sp->sub);
}
