/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:12 by souchen           #+#    #+#             */
/*   Updated: 2022/07/30 16:43:36 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

char	**get_path(t_struct *ptr)
{
	int		i;
	char	**path;

	i = 0;
	while (ptr->env.tmp_var[i])
	{
		if (ft_strcmp(ptr->env.tmp_var[i], "PATH") == 0)
		{
			path = ft_split(ptr->env.tmp_con[i], ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int  start_create_env(t_struct *shell)
{
	extern char **environ;
	shell->cmp = 0;
	ft_check_env(environ);
	if (!create_env_tmp(shell, environ))
		return(0) ;
	return (1);
}
void	cmd_not_found(char *cmd)
{
	glob_var = 127;
	if (cmd)
	{
		ft_putstr_fd("Minishell :",2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : command not found\n",2);
		exit(glob_var);
	}
}
