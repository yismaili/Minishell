/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/08/24 22:59:28 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("", 1);
	}
}

void	signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"Error cnrtl-C", 2);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"Error cntrl-\\", 2);
}

int	main(void)
{
	t_struct	shell;
	int			size;

	start_create_env(&shell);
	g_var.g_status = 0;
	signals();
	while (1)
	{
		commande_tape(&shell, &size);
		check_char(&shell, shell.commande_tape);
		if (shell.commande_tape && !is_empty(shell.commande_tape) \
				&& shell.failed == 0)
		{
			if (shell.commande_tape[0])
			{
				if (divise_commande(&shell, shell.commande_tape) != 0 && \
				shell.commande_tape[0] != '|' && shell.commande_tape
					[size - 1] != '|')
					{
					 run_commands(&shell);
					}
				else
				{
					cas_error(&shell, shell.msg);
				}
			}
		}
		free(shell.commande_tape);
	}
}

void	cas_error(t_struct *shell, char *msg)
{
	ft_cmd(shell->commands);
	ft_putstr_fd(msg, 2);
}

int	commande_tape(t_struct	*shell, int *size)
{
	shell->quote = 0;
	shell->double_quote = 0;
	shell->indice = 0;
	shell->right = 0;
	shell->output_fd = 1;
	shell->input_fd = 0;
	shell->check = 0;
	shell->quote_cmd = 0;
	shell->dquote_cmd = 0;
	shell->end = 0;
	shell->start = 0;
	rl_catch_signals = 0;
	shell-> qot = 0;
	shell->msg = NULL;
	shell->commande_tape = readline(GREEN"Minishell-1.0$ "WHITE);
	*size = ft_strlen(shell->commande_tape);
	if (shell->commande_tape && is_empty(shell->commande_tape) != 1)
		add_history(shell->commande_tape);
	if (!shell->commande_tape)
		exit(1);
	return (1);
}
