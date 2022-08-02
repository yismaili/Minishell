/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:00:28 by yismaili          #+#    #+#             */
/*   Updated: 2022/07/31 19:01:43 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_change_dir(t_struct *shell, char *chpath)
{
	replace_oldpwd(shell);
	if (chdir(chpath) == -1)
		ft_not_found(shell->arguments[1]);
	replace_pwd(shell);
}

char	*ft_oldpath(t_struct *shell)
{
	int	i;

	i = 0;
	while (shell->env.tmp_var[i])
	{
		if (!ft_strcmp(shell->env.tmp_var[i], "OLDPWD"))
		{
			return (shell->env.tmp_con[i]);
		}
		i++;
	}
	return (NULL);
}

void	ft_not_found(char *dir)
{
	if (dir)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
}
