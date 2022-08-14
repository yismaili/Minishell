/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:43 by souchen           #+#    #+#             */
/*   Updated: 2022/08/14 19:52:20 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	outredirection(t_struct *shell)
{
	char	*fichier1;

	if (shell->commands[shell->cmp][1] == '>')
	{
		fichier1 = ft_check_quotes_frst(shell);
		if (!fichier1)
			return (0);
		shell->output_fd = open(fichier1, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (shell->output_fd == -1)
			return (ft_putstr_fd("Open Error\n", 2), 0);
		free(fichier1);
	}
	else
	{
		fichier1 = ft_check_quotes_scnd(shell);
		if (!fichier1)
			return (0);
		printf("fichier1 =%s\n", fichier1);
		shell->output_fd = open(fichier1, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (shell->output_fd == -1)
			return (ft_putstr_fd("Open Error\n", 2), 0);
		free(fichier1);
	}
	return (1);
}

int	inredirection(t_struct	*shell)
{
	char	*fichier2;
	char	*line;

	if (shell->commands[shell->cmp][1] == '<')
	{
		fichier2 = ft_check_quotes_frst(shell);
		if (!fichier2)
			return (0);
		line = ft_strdup("");
		ft_play_herdoc(shell, fichier2, line);
		free(fichier2);
	}
	else
	{
		if (next_inredirection(shell) == 0)
			return (0);
	}
	return (1);
}

int	next_inredirection(t_struct *shell)
{
	char	*fichier2;

	fichier2 = ft_strtrim(&shell->commands[shell->cmp][2], " ");
	if ((((fichier2[0] == '\"' || fichier2[0] == '\'') || \
		(fichier2[ft_strlen(fichier2) - 1] == '\"' || \
		fichier2[ft_strlen(fichier2) - 1] == '\'')) && \
		((ft_strlen(fichier2) == 2) || (ft_strlen(fichier2) == 0))) || \
		(ft_strlen(fichier2) == 0))
	{
		g_var.g_status = 258;
		ft_putstr_fd("Minishell: : No such file or directory\n", 2);
		return (0);
	}
	else if (((fichier2[0] == '\"' || fichier2[0] == '\'') || \
	(fichier2[ft_strlen(fichier2) - 1] == '\"' || \
	fichier2[ft_strlen(fichier2) - 1] == '\'')) && (ft_strlen(fichier2) > 2))
	{
			fichier2 = ft_split_cmd(fichier2);
	}
	shell->input_fd = open(fichier2, O_RDONLY, 0777);
	if (shell->input_fd == -1)
		return (ft_putstr_fd("Open Error\n", 2), 0);
	return (1);
}

int	fun_redirection(t_struct *shell)
{
	shell->line_commande = ft_strdup(shell->commands[shell->cmp]);
	if (shell->divise.number_command > 1)
		shell->cmp++;
	while (shell->commands[shell->cmp] && \
			(shell->commands[shell->cmp][0] == '<' || \
			shell->commands[shell->cmp][0] == '>'))
	{
		if (shell->commands[shell->cmp][0] == '>')
		{
			if (outredirection(shell) == 0)
				return (0);
		}
		else if (shell->commands[shell->cmp][0] == '<')
		{
			if (inredirection(shell) == 0)
				return (0);
		}
		shell->cmp++;
	}
	return (1);
}

void	output_input(t_struct	*shell)
{
	if (shell->last_in != -1)
	{
		close(shell->last_in);
	}
	if (shell->output_fd != 1)
	{
		dup2(shell->output_fd, STDOUT_FILENO);
		close(shell->output_fd);
		close(shell->last_in);
	}
	if (shell->input_fd != 0)
	{
		dup2(shell->input_fd, STDIN_FILENO);
		close(shell->input_fd);
	}
}
