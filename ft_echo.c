/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:21:38 by souchen           #+#    #+#             */
/*   Updated: 2022/08/28 13:20:10 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(t_struct *shell)
{
	int	j;

	j = 0;
	shell->q1 = 0;
	shell->q2 = 0;
	shell->i = 0;
	shell->f_pipe = 0;
	if (shell->arguments[1][0] == '$' && shell->arguments[1][1] == '?')
		ft_chekexit_status(shell);
	if (shell->arguments[0][0] == '|')
		shell->f_pipe = 1;
	while (shell->variable == 1 && shell->arguments[j] != NULL \
	&& shell->f_pipe != 0)
	{
		shell->arguments[j] = shell->arguments[j + 1];
		j++;
	}
	if (shell->arguments[1] == NULL)
	{
		ft_putstr_fd("\n", shell->output_fd);
		return ;
	}
	ft_next_echo(shell);
}

void	ft_chekexit_status(t_struct *shell)
{
	char	*rm_es;
	char	*srch;
	char	*tmp;

	rm_es = ft_strtrim(shell->arguments[1], "$?");
	srch = find_env(shell, "?");
	tmp = shell->arguments[1];
	shell->arguments[1] = ft_strjoin(srch, rm_es);
	free(tmp);
}

int	ft_next_echo(t_struct *shell)
{
	int	i;

	i = 1;
	while (!ft_strncmp(shell->arguments[i], "-n", 2))
			i++;
	while (shell->arguments[i] && shell->qot % 2 == 0)
	{
		if (shell->arguments[i])
		{
			print_echo(shell, shell->arguments[i]);
			ft_putstr_fd(" ", shell->output_fd);
		}
		i++;
	}
	if (ft_strncmp(shell->arguments[1], "-n", 2))
		ft_putstr_fd("\n", shell->output_fd);
	return (0);
}

void	print_echo(t_struct *shell, char *echo_print)
{
	size_t	i;

	i = 0;
	if (echo_print == NULL)
	{
		ft_putstr_fd(" ", shell->output_fd);
		return ;
	}
	while (echo_print[i] != '$' && echo_print[i] != '\0')
	{
		ft_putchar_fd(echo_print[i], shell->output_fd);
		i++;
	}
	if (!ft_strncmp(&echo_print[i], "$", 1))
	{
		echo_with_dollar(shell, (&echo_print[i]));
	}
}

void	echo_with_dollar(t_struct *shell, char *echo_print)
{
	char	**splted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!shell->path)
		return ;
	splted = ft_split(echo_print, '$');
	while (splted[j])
	{
		i = 0;
		while (shell->env.tmp_var[i])
		{
			if (!ft_strcmp(shell->env.tmp_var[i], splted[j]))
				ft_putstr_fd(shell->env.tmp_con[i], shell->output_fd);
			i++;
		}
		j++;
	}
	ft_free_cmd(splted);
	return ;
}
