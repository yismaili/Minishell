/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/07/07 17:32:04 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"includes/minishell.h"

void ft_print_export(t_struct *env)
{
	int i;

	i = 0;
	while(i < env->env.len)
	{
		ft_putstr_fd("declare -x ", env->output_fd);
		ft_putstr_fd(env->env.tab1[i], env->output_fd);
		ft_putchar_fd('=',env->output_fd);
		ft_putstr_fd("\"", env->output_fd);
		ft_putstr_fd(env->env.tab2[i], env->output_fd);
		ft_putstr_fd("\"", env->output_fd);
		ft_putstr_fd("\n", env->output_fd);
		i++;
		}
}
// void	ft_sort_export(t_struct *ptr)
// {
// 	//char	*temp;
// 	int		j;
// 	int i =0;
// 	int len = ptr->env.len;
// 	char temp[2000];
// 	while (len)
// 	{
// 		j = 0;
// 		while (ptr->env.env[i][j])
// 		{
// 			if(ptr->env.env[i][j] > ptr->env.env[i][j+1])
// 			{
// 				ft_strlcpy(temp, ptr->env.env[i], ft_strlen(ptr->env.env[i][j]));
// 				ft_strpy(ptr->env.env[i][j], ptr->env.env[i], ft_strlen(&ptr->env.env[i][j + 1]));
// 				ft_strpy(ptr->env.env[i], temp, ft_strlen(temp));
// 			}
// 			j++;
// 		}
// 		i++;
// 		len--;
// 	}
// }
void	ft_export(t_struct *shell)
{
	int		i;
	char	**env_aux;

	i = 1;
	if (!shell->arguments[1])
	{
		//ft_sort_export(shell);
		ft_print_export(shell);
	}
	if (shell->arguments[i] && !ft_isdigit(shell->arguments[1][0]))
	{
			while (shell->arguments[i] && !ft_isdigit(shell->arguments[1][0]))
			{
				env_aux = ft_split(shell->arguments[i], '=');
				if (env_aux[1])
					verify_if_env_exists(shell, env_aux);
				else if (shell->arguments[i][ft_strlen(shell->arguments[1]) - 1] == '=')
				{
					env_aux[1] = ft_strdup("");
					verify_if_env_exists(shell, env_aux);
				}
				free(env_aux[0]);
				free(env_aux[1]);
				free(env_aux);
				env_aux = NULL;
				i++;
			}
	}
	else if (shell->arguments[i] && ft_isdigit(shell->arguments[1][0]))
	{
		printf("export: %s: not a valid identifier\n", shell->arguments[1]);
	}
	
}

void	verify_if_env_exists(t_struct *shell, char **env_aux)
{
	if (find_envernement(shell, env_aux[0]))
	{
		free(shell->env.tab2[shell->env.position]);
		shell->env.tab2[shell->env.position] = ft_strdup(env_aux[1]);
	}
	else
		ajouter_envernement(shell, env_aux[0], env_aux[1]);
}

void	ajouter_envernement(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	int	i;

	shell->env.len++;
	Malloc_env_aux(shell);
	i = 0;
	while (i < shell->env.len - 1)
	{
		shell->env_aux.tab1[i] = ft_strdup(shell->env.tab1[i]);
		shell->env_aux.tab2[i] = ft_strdup(shell->env.tab2[i]);
		i++;
	}
	shell->env_aux.tab1[i] = ft_strdup(new_elem_tab1);
	shell->env_aux.tab2[i] = ft_strdup(new_elem_tab2);
	i++;
	shell->env_aux.tab1[i] = NULL;
	shell->env_aux.tab2[i] = NULL;
	free1(shell->env.tab1);
	free1(shell->env.tab2);
	shell->env.tab1 = shell->env_aux.tab1;
	shell->env.tab2 = shell->env_aux.tab2;
}

