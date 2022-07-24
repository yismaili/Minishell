/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:32 by souchen           #+#    #+#             */
/*   Updated: 2022/07/24 05:54:35 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

bool	there_is_home(t_struct *shell)
{
	if (find_env_tmp(shell, "HOME"))
		return (true);
	else
		return (false);
}

void    replace_oldpwd(t_struct *env)
{
    char    *buff = NULL;
	int		i = 0;
   
    buff = getcwd(buff, sizeof(buff));
	if (glob_var == 0)
	{
		 env->env.tmp_con[0] = ft_strdup(buff);
		 return ;
	}
    while (env->env.tmp_var[i])
    {
        if (!ft_memcmp(env->env.tmp_var[i], "OLDPWD", 6))
        {
                free(env->env.tmp_con[i]);
                env->env.tmp_con[i] = ft_strdup(buff);
            return ;
        }
        i++;
    }
}

void    replace_pwd(t_struct *env)
{
    char    *buff = NULL;
	int		i = 0;
   
    buff = getcwd(buff, sizeof(buff));
	if (glob_var == 0)
	{
		 env->env.tmp_con[0] = ft_strdup(buff);
		 return ;
	}
    while (env->env.tmp_var[i])
    {
        if (!ft_memcmp(env->env.tmp_var[i], "PWD", 3))
        {
                free(env->env.tmp_con[i]);
                env->env.tmp_con[i] = ft_strdup(buff);
            return ;
        }
        i++;
    }
}

int	ft_cd(t_struct *shell)
{
	char	*arg_aux = NULL;
	bool	home;
	char	*current_path = NULL;
	char	*old_path = NULL;

	if (glob_var == 0)
	{
		ft_die("PWD not fuond\n");
		return (0);
	}
	home = there_is_home(shell);
	if (!ft_strncmp(shell->arguments[1], "-", 1))
	{
		int i = 0;
		current_path = ft_strdup(getcwd(current_path, sizeof(current_path)));
		while (shell->env.tmp_var[i]) 
		{
			if (!ft_strncmp(shell->env.tmp_var[i], "OLDPWD", 6))
			{
				old_path = ft_strdup(shell->env.tmp_con[i]);
				break;
			}
			i++;
		}
		if (!ft_strcmp(current_path, old_path))
		{
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", shell->output_fd);
		}
		else
		{
			if (ft_strcmp(old_path, getcwd(NULL, sizeof(NULL))))
			{
				replace_oldpwd(shell);
				if (chdir(old_path) == -1)
					printf("Minishell: cd: %s: %s", shell->arguments[1], "no such file or directory\n");
				ft_putstr_fd(getcwd(NULL, sizeof(NULL)), shell->output_fd);
				printf("\n");
				replace_pwd(shell);
			}
		}
		return(0);
	}
	if (shell->arguments[1])
	{
		arg_aux = ft_strdup(shell->arg.all_cmd);
	}
	// else
	// {
	// 	if (home == true)
	// 	{
	// 		arg_aux = ft_strdup(shell->home);
	// 	}
	// 	else
	// 	{
	// 		printf("Error/ home not set\n");
	// 		return (1);
	// 	}
	// }
	replace_oldpwd(shell);
	if (chdir(arg_aux) == -1)
		printf("Minishell: cd: %s: %s", shell->arguments[1], "no such file or directory\n");
	replace_pwd(shell);
	free(arg_aux);
	return (0);
}

