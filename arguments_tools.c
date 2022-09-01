/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 23:14:00 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/31 19:44:03 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	split_arg(t_struct *shell, char *cmd_joined)
{
	shell->cmp_space = 0;
	shell->alpha = 0;
	shell->con_failed = 0;
	cmp_spaces(shell);
	if (((((&shell->line_commande[shell->pos])[0] == '\"') || \
		((&shell->line_commande[shell->pos])[0] == '\'')) || \
		(((&shell->line_commande[shell->pos])[shell->size - 1] == '\"') || \
		((&shell->line_commande[shell->pos])[shell->size - 1] == '\''))))
	{
		cmd_joined = ft_split_cmd(shell->line_commande, shell);
		shell->arguments = ft_split(cmd_joined, ' ');
		if (ft_strncmp(shell->arguments[0], "'/bin/", 6))
			to_remove_quotes(shell);
		free(cmd_joined);
	}
	else
		shell->arguments = ft_split(shell->line_commande, ' ');
	if (exit_with_arg(shell) == 0)
		return (0);
	return (1);
}

int	exit_with_arg(t_struct	*shell)
{
	int	i;

	i = 0;
	if (!ft_strncmp(shell->arguments[0], "exit", 4) && shell->cmp_space >= 2)
	{
		while (shell->arguments[1][i] != '\0')
		{
			if (!ft_isalpha(shell->arguments[1][i]))
				shell->alpha++;
			i++;
		}
		if (shell->alpha == (int)ft_strlen(shell->arguments[1]))
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (0);
		}
	}
	return (1);
}

void	to_remove_quotes(t_struct *shell)
{
	char	*tmp;
	char	*tmp_tow;
	int		i;

	i = 0;
	while (shell->arguments[i] != NULL && \
			(ft_strncmp(shell->arguments[i], "echo", 4) && \
			ft_strncmp(&shell->arguments[0][1], "echo", 4)))
	{
		tmp = shell->arguments[i];
		shell->arguments[i] = ft_remove_quot(shell->arguments[i], '\"', shell);
		tmp_tow = shell->arguments[i];
		shell->arguments[i] = ft_remove_quot(shell->arguments[i], '\'', shell);
		free(tmp);
		free(tmp_tow);
		i++;
	}
}

int	split_and_cas_error(t_struct *shell, char *fichier2)
{
	shell->input_fd = open(fichier2, O_RDONLY, 0777);
	if (shell->input_fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(fichier2, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	arg_func(t_struct *shell)
{
	char	*cmd_joined;

	shell->indice = 0;
	shell->quote = 0;
	shell->double_quote = 0;
	cmd_joined = NULL;
	ft_check_quote(shell);
	shell->size = ft_strlen(&shell->line_commande[shell->pos]);
	ft_check_space(shell);
	if (ft_check_quote_pos(shell, cmd_joined) == 0)
		return (0);
	return (1);
}
