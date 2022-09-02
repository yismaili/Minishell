/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:39:50 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/02 02:37:07 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	next_inredirection(t_struct *shell)
{
	char	**fichier2;
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
	if (red_with_dolar(fichier2[0], shell) == 0)
		return (ft_free_cmd(fichier2), 0);
	if (split_and_cas_error(shell, fichier2[0]) != 1)
		return (ft_free_cmd(fichier2), 0);
	ft_free_cmd(fichier2);
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

char	*ft_chek_dlr_arg(char *arguments, t_struct *shell, char **strrm, \
char *join)
{
	char	*rm;
	char	*con;
	int		p;
	int		j;

	p = 0;
	j = 0;
	strrm = ft_splt_dlor_arg(arguments, shell);
	while (strrm[j])
	{
		rm = ft_strtrim(strrm[j], "$");
		if (!is_empty(rm) && ft_isalpha(rm[0]))
			con = find_env(shell, rm);
		else if (rm[0] == '?' )
			con = find_env(shell, rm);
		if (shell->chek_plc == 1)
			con = ft_strjoin(con, "+");
		shell->chek_plc = 0;
		join = ft_strjoin(join, con);
		if (arguments == NULL)
			exit(127);
		p = 1;
		j++;
	}
	return (join);
}

char	**ft_splt_dlor_arg(char	*arguments, t_struct *shell)
{
	char	**strrm;

	strrm = NULL;
	if (ft_strchr(arguments, '+'))
	{
		strrm = ft_split(arguments, '+');
		shell->chek_plc = 1;
	}
	else
		strrm = ft_split(arguments, '$');
	return (strrm);
}

void	cmd_not_found(t_struct *shell)
{
	if (shell->arguments[0])
	{
		if (shell->arguments[0][0] == '<' || shell->arguments[0][0] == '>')
			exit(127);
		if (shell->arguments[0][0] != '|' && \
			ft_strlen(shell->arguments[0]) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell->arguments[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}	
	}
	if (shell->arguments[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[1], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (shell->arguments[0] == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(127);
}
