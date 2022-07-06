/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:18 by souchen           #+#    #+#             */
/*   Updated: 2022/07/06 00:04:06 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void	init_tabs_struct_env(t_struct *shell)
{
	shell->env.tab1 = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.tab1)
		exit(0);
	shell->env.tab2 = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.tab2)
		exit(0);
}
void	len_envernement(t_struct *shell)
{
	int	i;

	i = 0;
	while (shell->env.env[i])
		i++;
	shell->env.len = i;
}
void	create_envernement(t_struct *shell, char **my_env)
{
	int		i;
	char	**env_divise;
	shell->env.env = my_env;
	len_envernement(shell);
	init_tabs_struct_env(shell);
	i = 0;
	while (shell->env.env[i])
	{
		env_divise = ft_split(shell->env.env[i], '=');
		shell->env.tab1[i] = ft_strdup(env_divise[0]);
		if (env_divise[1])
			shell->env.tab2[i] = ft_strdup(env_divise[1]);
		else
			shell->env.tab2[i] = ft_strdup("");
		free(env_divise);
		env_divise = NULL;
		i++;
	}
	shell->env.tab1[i] = 0;
	shell->env.tab2[i] = 0;
}
char	*find_envernement(t_struct *shell, char *search)
{
	int	i;
	int	length;
	int	len_search;

	i = 0;
	shell->env.position = 0;
	len_search = ft_strlen(search);
	while (shell->env.tab1[i] && i < shell->env.len)
	{
		length = ft_strlen(shell->env.tab1[i]);
		if (!ft_strncmp(shell->env.tab1[i], search, len_search) && length == len_search)
		{
			shell->env.position = i;
			return (shell->env.tab2[i]);
		}
		i++;
	}
	return (0);
}
char	*get_current_dir(void)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
}
