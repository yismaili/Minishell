/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:00:28 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/31 18:45:30 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <errno.h>

int	ft_change_dir(t_struct *shell, char *chpath)
{
	int		fd;
	char	*path;
	char	*join_slch;
	char	*join_path;

	path = NULL;
	path = getcwd(path, sizeof(path));
	join_slch = ft_strjoin(path, "/");
	free(path);
	join_path = ft_strjoin(join_slch, shell->arguments[1]);
	free(join_slch);
	fd = open(join_path, O_RDONLY);
	if (fd < 0)
		return (ft_not_found(shell->arguments[1]), free(join_path), 0);
	free(join_path);
	replace_oldpwd(shell);
	if (chdir(chpath) < 0)
		return (ft_not_found(shell->arguments[1]), 0);
	if (errno == ENOENT)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd("cannot access parent directories: \
				No such file or directory\n", 2);
	}
	replace_pwd(shell);
	return (0);
}

char	*ft_oldpath(t_struct *shell)
{
	int	i;

	i = 0;
	if (g_var.g_var == 0)
		return (getcwd(NULL, sizeof(NULL)));
	while (shell->env.tmp_var[i])
	{
		if (!ft_strcmp(shell->env.tmp_var[i], "OLDPWD"))
		{
			return (shell->env.tmp_con[i]);
		}
		i++;
	}
	return (getcwd(NULL, sizeof(NULL)));
}

void	ft_not_found(char *dir)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
}

char	**ft_swap_env(char	**dup_env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (dup_env[i])
	{
		j = i + 1;
		while (dup_env[j])
		{
			if (ft_strcmp(dup_env[i], dup_env[j]) > 0)
			{
				tmp = dup_env[i];
				dup_env[i] = dup_env[j];
				dup_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (dup_env);
}

void	ft_error_fork(void)
{
	ft_putstr_fd("Minishell: fork: ", 2);
	ft_putstr_fd("Resource temporarily unavailable\n", 2);
	return ;
}
