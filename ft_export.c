/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:19:21 by souchen           #+#    #+#             */
/*   Updated: 2022/07/25 21:36:25 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"includes/minishell.h"

void	ft_print_export(char **export, t_struct	*shell)
{
	int	i;
	int	j;

	i = 0;
	while (export[i])
	{
		j = 0;
		if (i != 0)
		{
			ft_putstr_fd("declare -x ", shell->output_fd);
			while (export[i][j])
			{
				ft_putchar_fd(export[i][j], shell->output_fd);
				if (export[i][j] == '=')
				{
					ft_putchar_fd('"', shell->output_fd);
				}
				j++;
			}
			ft_putchar_fd('"', shell->output_fd);
			ft_putchar_fd('\n', shell->output_fd);
		}
		i++;
	}
}
// dup and join env in one array 
char	**ft_dup_env(t_struct *env)
{
	char	**dup_str;
	int		len_env;
	char	*first_join;
	char	*second_join;
	int		i;

	len_env = glob_var;
	i = 0;
	dup_str = (char **)malloc(sizeof(char *) * (len_env + 1));
	if (!dup_str)
		return (NULL);
	dup_str[len_env] = 0;
	while (i < len_env)
	{
		first_join = ft_strjoin(env->env.tmp_var[i], "=");
		second_join = ft_strjoin(first_join, env->env.tmp_con[i]);
		dup_str[i] = ft_strdup(second_join);
		free(first_join);
		free(second_join);
		i++;
	}
	return (dup_str);
}
void		sort_env(t_struct *env)
{
	char	**dup_env;
	char	*tmp;
	int	i;
	int	j;

	if (glob_var == 0)
	{
		ft_die("environment not found\n");
		return ;
	}
	dup_env = ft_dup_env(env);
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
	ft_print_export(dup_env, env);
	ft_free_cmd(dup_env);
	free(dup_env);
}

void	ft_export(t_struct *shell)
{
	int		i;
	char	**env_aux;

	i = 1;
	if (!shell->arguments[1])
		sort_env(shell);
	if (shell->arguments[i] && check_export(shell) == 0)
	{
			while (shell->arguments[i] && check_export(shell) == 0)
			{
				env_aux = ft_split(shell->arguments[i], '=');
				if (env_aux[0])
				{
					verify_if_env_exists(shell, env_aux);
				}
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
	else if (shell->arguments[i] && check_export(shell) == 1)
	{
		printf("export: %s: not a valid identifier\n", shell->arguments[1]);
	}
	
}

void	verify_if_env_exists(t_struct *shell, char **env_aux)
{
	if (find_env_tmp(shell, env_aux[1]))
	{
		free(shell->env.tmp_con[shell->env.position]);
		shell->env.tmp_con[shell->env.position] = ft_strdup(env_aux[1]);
	}
	else if (!find_env_tmp(shell, env_aux[0]))
		export_to_env(shell, env_aux[0], env_aux[1]);
}

void	export_to_env(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2)
{
	int	i;

	if(!malloc_env_aux_tmp(shell))
		ft_die_malloc("No space left on device\n");
	if(glob_var == 0)
	{
		shell->env_aux.tmp_var[0] = ft_strdup(new_elem_tab1);
		shell->env_aux.tmp_con[0] = ft_strdup(new_elem_tab2);
		shell->env.tmp_var = shell->env_aux.tmp_var;
		shell->env.tmp_con = shell->env_aux.tmp_con;
		return ;
	}
	i = 0;
	while (i < shell->env.len - 1 )
	{
		shell->env_aux.tmp_var[i] = ft_strdup(shell->env.tmp_var[i]);
		shell->env_aux.tmp_con[i] = ft_strdup(shell->env.tmp_con[i]);
		i++;
	}
	shell->env_aux.tmp_var[i] = ft_strdup(new_elem_tab1);
	shell->env_aux.tmp_con[i] = ft_strdup(new_elem_tab2);
	free1(shell->env.tmp_var);
	free1(shell->env.tmp_con);
	shell->env.tmp_var = shell->env_aux.tmp_var;
	shell->env.tmp_con = shell->env_aux.tmp_con;
}

int check_export(t_struct *export)
{
	int i = 0;
	char	**splted;

	if (export->arguments[1][0] == '=')
		return(1);
	if (glob_var == 0)
		return(0);
	splted = ft_split(export->arguments[1], '=');
	while (splted[0][i])
	{
		if(!ft_isalpha(splted[0][i]))
			return(1);
		i++;
	}
	i = 0;
	free(splted);
	return(0);
}