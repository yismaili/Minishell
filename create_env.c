/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:18 by souchen           #+#    #+#             */
/*   Updated: 2022/08/26 11:40:14 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	create_env_tmp(t_struct *shell, char **my_env)
{
	int		i;
	char	**env_divise;

	shell->env.env = my_env;
	count_len_env(shell);
	if (!malloc_env_tmp(shell))
		ft_die_malloc("No spece lift\n");
	i = 1;
	shell->env.tmp_var[0] = ft_strdup("?");
	shell->env.tmp_con[0] = ft_strdup("0");
	while (shell->env.env[i])
	{
		env_divise = ft_split(shell->env.env[i], '=');
		shell->env.tmp_var[i] = ft_strdup(env_divise[0]);
		if (env_divise[1])
			shell->env.tmp_con[i] = ft_strdup(env_divise[1]);
		else
			shell->env.tmp_con[i] = ft_strdup("");
		if (env_divise)
			ft_free_env(env_divise);
		i++;
	}
	shell->env.tmp_var[i] = 0;
	shell->env.tmp_con[i] = 0;
	return (1);
}

void	ft_remplir_env(t_struct *env)
{
	char	*buff;

	buff = getcwd(NULL, sizeof(NULL));
	env->env.len = 4;
	if (!malloc_env_tmp(env))
		ft_die_malloc("No spece lift\n");
	env->env.tmp_var[0] = ft_strdup("?");
	env->env.tmp_con[0] = ft_strdup("0");
	env->env.tmp_var[1] = ft_strdup("OLDPWD");
	env->env.tmp_con[1] = ft_strdup(buff);
	env->env.tmp_var[2] = ft_strdup("PWD");
	env->env.tmp_con[2] = ft_strdup(buff);
	env->env.tmp_var[3] = ft_strdup("PATH");
	env->env.tmp_con[3] = \
	ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	env->env.tmp_var[4] = 0;
	env->env.tmp_con[4] = 0;
	free(buff);
	buff = NULL;
	g_var.g_var = 3;
}
