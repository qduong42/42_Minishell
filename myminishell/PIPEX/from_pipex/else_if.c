#include "../pipex.h"

int	is_buildin(t_pipe *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) && !cmd->argv[1])
		return(1);
	return (0);
}

int	exec_buildin(t_pipe *cmd, t_list **env_lst)
{
	if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		return (ft_echo(cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
		return (pwd());
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) && !cmd->argv[1])
		return (ft_export(cmd->argv, env_lst));
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		return (ft_env(*env_lst));
	return (187);
}

int	is_parent(t_pipe *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0])))
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) && cmd->argv[1])
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])))
		return(1);
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		return(1);
	return (0);
}

void	exec_parent(t_pipe *cmd, t_list **env_lst)
{
	if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0])))
		ft_cd(cmd->argv, *env_lst);
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])) && cmd->argv[1])
		ft_export(cmd->argv, env_lst);
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])))
		unset(cmd->argv, env_lst);
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		exit(0);
}
