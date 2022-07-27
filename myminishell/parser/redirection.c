/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:09:37 by qduong            #+#    #+#             */
/*   Updated: 2022/07/27 21:14:42 by qduong           ###   ########.fr       */
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
	temp = ft_calloc(1, len - len_fn + 1);
	ft_strlcpy(temp, sub, be_r);
	ft_catall(temp, sub + end);
	if (sub)
		free(sub);
	return (temp);
}

void	input(t_pipe *sp, char *temp)
{
	if (sp->fd_in > 2)
		close(sp->fd_in);
	sp->fd_in = open(temp, O_RDONLY);
	if (sp->fd_in == -1)
	{
		perror(temp);
	}
	sp->last = 1;
}

void	output(t_pipe *sp, char *temp)
{
	if (sp->fd_out > 2)
		close(sp->fd_out);
	sp->fd_out = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sp->fd_out == -1)
		perror(temp);
}

void	hd(t_pipe *sp, char *temp)
{
	if (sp->hd)
		free (sp->hd);
	sp->hd = temp;
	sp->last = 0;
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
// 	while (sp->sub[*i] && sp->sub[*i] != ' ' 
//&& sp->sub[*i] != '<' && sp->sub[*i] != '>')
// 	{
// 		fn[y] = sp->sub[*i];
// 		*i++;
// 		y++;
// 		*z++;
// 	}
// 	fn[y] = '\0';
// 	return (fn);
// }

char	*fnhandler(t_pipe *sp, int i, int z)
{
	char	fn[256];
	char	*temp;
	int		y;

	y = 0;
	while (sp->sub[i] && sp->sub[i] == ' ')
	{
		z++;
		i++;
	}
	while (sp->sub[i] && sp->sub[i] != ' ' && \
	sp->sub[i] != '<' && sp->sub[i] != '>')
	{
		z++;
		fn[y] = sp->sub[i];
		i++;
		y++;
	}
	fn[y] = '\0';
	temp = ft_strtrim(fn, "\"'");
	return (temp);
}

int	iohandler(t_pipe *sp, int i, int id)
{
	int		z;
	int		be_r;
	char	*temp;

	z = 1;
	i++;
	be_r = i;
	if (id == 3 || id == 4)
		z++;
	if (id == 3 || id == 4)
		be_r--;
	temp = fnhandler(sp, i, z);
	printf("Filename string:%s\tID:%d\n", temp, id);
	if (id == 1)
		input(sp, temp);
	if (id == 2)
		output(sp, temp);
	if (id == 3)
		hd(sp, temp);
	if (id == 4)
		append(sp, temp);
	sp->sub = del_re(sp->sub, z, i, be_r);
	if (id != 3)
		free (temp);
	return (-1);
}
