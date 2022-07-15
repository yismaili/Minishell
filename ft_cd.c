/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:32 by souchen           #+#    #+#             */
/*   Updated: 2022/07/15 11:43:01 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

bool	there_is_home(t_struct *shell)
{
	if (find_envernement(shell, "HOME"))
		return (true);
	else
		return (false);
}

void    replace_oldpwd(t_struct *env)
{
    char    *buff = NULL;
	int		i = 0;
   
    buff = getcwd(buff, sizeof(buff));
    while (env->env.tab1[i])
    {
        if (!ft_memcmp(env->env.tab1[i], "OLDPWD", 6))
        {
                free(env->env.tab2[i]);
                env->env.tab2[i] = ft_strdup(buff);
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
    while (env->env.tab1[i])
    {
        if (!ft_memcmp(env->env.tab1[i], "PWD", 3))
        {
                free(env->env.tab2[i]);
                env->env.tab2[i] = ft_strdup(buff);
            return ;
        }
        i++;
    }
}

int	ft_cd(t_struct *shell)
{
	char	*arg_aux;
	bool	home;

	home = there_is_home(shell);
	if (shell->arguments[1])
	{
		arg_aux = ft_strdup(shell->arg.all_cmd);
	}
	else
	{
		if (home == true)
		{
			arg_aux = ft_strdup(shell->home);
		}
		else
		{
			printf("Error/ home not set\n");
			return (1);
		}
	}
	replace_oldpwd(shell);
	if (chdir(arg_aux) == -1)
		printf("Minishell: cd: %s: %s", shell->arguments[1], "no such file or directory\n");
	replace_pwd(shell);
	free(arg_aux);
	return (0);
}

