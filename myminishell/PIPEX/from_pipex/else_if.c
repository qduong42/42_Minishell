/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else_if.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:47:46 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 11:52:17 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_buildin(t_pipe *cmd)
{
	int	size;

	size = ft_strlen(cmd->argv[0]);
	if (!ft_strncmp(cmd->argv[0], "echo", size))
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "pwd", size))
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "env", size))
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "export", size) && !cmd->argv[1])
		return (1);
	return (0);
}

int	exec_buildin(t_pipe *cmd, t_list **env_lst)
{
	int	size;

	size = ft_strlen(cmd->argv[0]);
	if (!ft_strncmp(cmd->argv[0], "echo", size))
		return (ft_echo(cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "pwd", size))
		return (pwd(cmd));
	else if (!ft_strncmp(cmd->argv[0], "export", size) && !cmd->argv[1])
		return (ft_export(cmd->argv, env_lst));
	else if (!ft_strncmp(cmd->argv[0], "env", size))
		return (ft_env(cmd, *env_lst));
	return (187);
}

int	is_parent(t_pipe *cmd)
{
	int	size;

	size = ft_strlen(cmd->argv[0]);
	if (!ft_strncmp(cmd->argv[0], "cd", size))
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "export", size) && cmd->argv[1])
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "unset", size))
		return (1);
	else if (!ft_strncmp(cmd->argv[0], "exit", size))
		return (1);
	return (0);
}

int	ft_exit(t_pipe *cmd)
{
	if (!cmd->argv[1])
		exit (0);
	else if (ft_strstrlen(cmd->argv) > 2)
	{
		error_msg("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ft_isnum(cmd->argv[1]))
		exit(ft_atoi(cmd->argv[1]));
	else
	{
		error_msg("minishell: exit: numeric argument required\n");
		exit (-1);
	}
	return (187);
}

int	exec_parent(t_pipe *cmd, t_list **env_lst)
{
	int	size;

	size = ft_strlen(cmd->argv[0]);
	if (!ft_strncmp(cmd->argv[0], "cd", size))
		return (ft_cd(cmd->argv, *env_lst));
	else if (!ft_strncmp(cmd->argv[0], "export", size) && cmd->argv[1])
		return (ft_export(cmd->argv, env_lst));
	else if (!ft_strncmp(cmd->argv[0], "unset", size))
		return (unset(cmd->argv, env_lst));
	else if (!ft_strncmp(cmd->argv[0], "exit", size))
		return (ft_exit(cmd));
	return (187);
}
