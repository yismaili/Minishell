/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divise_commandes_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:28:36 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/18 01:05:40 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_pipe(int i, t_struct *shell, char *commande_read)
{
	int	j;

	j = 0;
	while (i < (int)ft_strlen(commande_read) && (shell->quote_cmd % 2 == 0 \
				|| shell->dquote_cmd % 2 == 0) && (i > shell->end || i == 0))
	{
		if (commande_read[i] == '\"')
		{
			check_quote(i, shell, commande_read, '\"');
			break ;
		}
		else if (commande_read[i] == '\'')
		{
			check_quote(i, shell, commande_read, '\'');
			break ;
		}
		i++;
	}
}

void	check_quote(int i, t_struct *shell, char *commande_read, char character)
{
	int	j;

	j = 0;
	shell->start = i;
	while ((&commande_read[shell->start])[j] != '\0')
	{
		if ((&commande_read[shell->start + 1])[j] == character)
		{
			shell->end = i + 1;
			break ;
		}
		i++;
		j++;
	}
}

int	ft_else(t_struct *shell, char **env_aux, int i)
{
	if (g_var.g_var == 0)
	{
		verify_if_env_exists(shell, env_aux);
		ft_free_cmd(env_aux);
		return (1);
	}
	if (env_aux[0] && shell->arguments[i] \
		[ft_strlen(shell->arguments[1]) - 1] != '=' && \
			env_aux[1] != NULL)
		verify_if_env_exists(shell, env_aux);
	else if (env_aux[0] && env_aux[1] == NULL)
	{
		env_aux[1] = NULL;
		verify_if_env_exists(shell, env_aux);
	}
	return (0);
}

int	ft_with_dlr(char **env_aux, t_struct *shell)
{
	char	*ptr;
	char	*rm;

	ptr = env_aux[0];
	rm = ft_strtrim(env_aux[0], "$");
	env_aux[0] = ft_strdup(find_env(shell, rm));
	free(ptr);
	free(rm);
	if (check_export_con(env_aux[0]) == 1)
	{
		ft_putstr_fd("Export: ", 2);
		ft_putstr_fd(env_aux[0], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		ft_free_cmd(env_aux);
		return (1);
	}
	else if (check_export_con(env_aux[0]) == 3)
	{
		sort_env(shell);
		ft_free_cmd(env_aux);
		return (1);
	}
	return (0);
}
