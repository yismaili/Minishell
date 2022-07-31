/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/07/31 15:04:59 by yismaili         ###   ########.fr       */
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
		glob_var = 130;
	}
	else if (sig == SIGQUIT)
	{
		glob_var = 131;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"can't catch cntrl-\\", 2);
}

int	main(void)
{
	t_struct	shell;
	int			size;

	g_status = 0;
	print_welcome();
	start_create_env(&shell);
	signals();
	while (1)
	{
		commande_tape(&shell, &size);
		if (shell.commande_tape && !line_empty(shell.commande_tape))
		{
			if (shell.commande_tape[0])
			{
				divise_commande(&shell, shell.commande_tape);
				if (shell.commands[0][0] != '|' && \
						shell.commande_tape[size] != '|')
					run_commands(&shell);
				else
					ft_putstr_fd("Minishell: syntax error near \
							unexpected token `|'\n", 2);
			}
		}
	}
	free(shell.commande_tape);
}	

void	print_welcome(void)
{
	printf("%s*****************************************************\n", RED);
	printf("%s|                                                   |\n", RED);
	printf("%s|     Welcome to Souchen && Yismaili Minishell      |\n", RED);
	printf("%s|                                                   |\n", RED);
	printf("%s*****************************************************\n", RED);
}

int	commande_tape(t_struct	*shell, int *size)
{
	shell->output_fd = 1;
	shell->input_fd = 0;
	rl_catch_signals = 0;
	shell->commande_tape = readline(GREEN"Minishell-1.0$ "WHITE);
	*size = ft_strlen(shell->commande_tape);
	if (shell->commande_tape && line_empty(shell->commande_tape) != 1)
		add_history(shell->commande_tape);
	if (!shell->commande_tape)
		exit(1);
	return (1);
}
