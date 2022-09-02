/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:43 by souchen           #+#    #+#             */
/*   Updated: 2022/09/02 03:05:02 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	outredirection(t_struct *shell)
{
	char	**file;
	char	*ptr;

	file = NULL;
	ptr = shell->line_commande;
	if (shell->commands[shell->cmp][1] == '>')
	{
		file = ft_split(&shell->commands[shell->cmp][2], ' ');
		if (file[1] != NULL && shell->line_commande[0] == '>')
			ft_change_data(shell, ptr, file, 1);
		else if (file[1] != NULL)
			ft_change_data(shell, ptr, file, 2);
		if (check_file_dollar(file, file[0], shell) == 0)
			return (ft_free_cmd(file), 0);
		shell->output_fd = open(file[0], O_CREAT | \
				O_WRONLY | O_APPEND, 0777);
		if (shell->output_fd == -1)
			return (ft_putstr_fd("Open Error\n", 2), ft_free_cmd(file), 0);
		ft_free_cmd(file);
	}
	else
		if (ft_next_outredirection(shell, file) == 0)
			return (0);
	return (1);
}

int	ft_next_outredirection(t_struct *shell, char **fichier1)
{
	char	*ptr;

	ptr = shell->line_commande;
	fichier1 = ft_split(&shell->commands[shell->cmp][1], ' ');
	if (fichier1[1] != NULL && shell->line_commande[0] == '>')
	{
		shell->line_commande = ft_strdup(fichier1[1]);
		free(ptr);
	}
	else if (fichier1[1] != NULL)
	{
		shell->line_commande = \
			ft_strjoin(shell->line_commande, fichier1[1]);
		free(ptr);
	}
	if (check_file_dollar(fichier1, fichier1[0], shell) == 0)
		return (ft_free_cmd(fichier1), 0);
	shell->output_fd = open(fichier1[0], O_CREAT | \
			O_WRONLY | O_TRUNC, 0777);
	if (shell->output_fd == -1)
		return (ft_putstr_fd("Open Error\n", 2), ft_free_cmd(fichier1), 0);
	ft_free_cmd(fichier1);
	return (1);
}

int	check_file_dollar(char **f, char *f1, t_struct *shell)
{
	if (!f)
		return (0);
	if (red_with_dolar(f1, shell) == 0)
		return (0);
	return (1);
}

int	inredirection(t_struct	*shell)
{
	char	**fichier2;
	char	*line;

	line = NULL;
	fichier2 = NULL;
	if (shell->commands[shell->cmp][1] == '<')
	{
		if (ft_next_inredirection(shell, fichier2, line) == 0)
			return (0);
		if (shell->name)
		{
			unlink(shell->name);
			free(shell->name);
		}
	}
	else
	{
		if (next_inredirection(shell) == 0)
			return (0);
	}
	return (1);
}

int	ft_next_inredirection(t_struct	*shell, char **fichier2, char *line)
{
	char	*ptr;

	ptr = shell->line_commande;
	fichier2 = ft_split(&shell->commands[shell->cmp][2], ' ');
	if (fichier2[1] != NULL && shell->line_commande[0] == '<')
	{
		shell->line_commande = ft_strdup(fichier2[1]);
		free(ptr);
	}
	else if (fichier2[1] != NULL)
	{
		shell->line_commande = ft_strjoin(shell->line_commande, fichier2[1]);
		free(ptr);
	}
	if (in_check(fichier2, fichier2[1]) == 0)
		return (ft_free_cmd(fichier2), 0);
	line = ft_strdup("");
	if (ft_play_herdoc(shell, fichier2[0], line) == 0)
		return (ft_free_cmd(fichier2), 0);
	close(shell->input_fd);
	shell->input_fd = open(fichier2[0], O_RDONLY | O_CREAT, 0777);
	shell->name = ft_strdup(fichier2[0]);
	ft_free_cmd(fichier2);
	return (1);
}
