/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:16:58 by qduong            #+#    #+#             */
/*   Updated: 2022/08/01 18:48:39 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fix_pwd(void *data)
{
	t_list	**env;
	char	*to_free;
	char	*new_content;

	env = (t_list **)data;
	to_free = get_pwd();
	new_content = malloc(sizeof(char) * (ft_strlen(to_free) + 5));
	ft_strlcpy(new_content, "PWD=", ft_strlen(to_free) + 5);
	ft_strlcat(new_content, to_free, ft_strlen(to_free) + 5);
	ft_lstadd_back(env, ft_lstnew(new_content));
	free(to_free);
	return (0);
}

int	path_error(void *data)
{
	(void)data;
	error_msg("Error: define a PATH!\n");
	return (1);
}

int	react_if_ncontained(t_reaction reaction, char *contained, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (1)
	{
		if (!tmp)
		{
			if (reaction(env))
			{
				g_exit_status = 9000;
				return (1);
			}
			break ;
		}
		if (!ft_strncmp(tmp->content, contained, 4))
			break ;
		tmp = tmp->next;
	}
	return (0);
}

int	env_errors(t_list **env)
{
	if (react_if_ncontained(fix_pwd, "PWD=", env))
		return (1);
	return (0);
}

int	errors(char *line, t_list **env)
{
	if (unclosed_quotes(line))
	{
		error_msg("Error: unclosed quotes\n");
		g_exit_status = 696969;
		return (1);
	}
	if (unexpected_newline(line))
	{
		error_msg("Error: unexpected newline\n");
		g_exit_status = 2;
		return (1);
	}
	if (single_dollar(line))
	{
		error_msg("Error: single dollar sign\n");
		g_exit_status = 6969;
		return (1);
	}
	if (consecutive_specials(line))
	{
		error_msg("Error: consecutive special tokens\n");
		g_exit_status = 69;
		return (1);
	}
	return (env_errors(env));
}

// int	main(void)
// {
// 	char	*line;
// 	while (1)
// 	{
// 		line = readline("minishell: ");
// 		errors(line);
// 		free(line);
// 	}
// 	return (0);
// }
