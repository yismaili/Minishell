/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/07/25 20:14:09 by yismaili         ###   ########.fr       */
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
	{}
}
void	signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"can't catch cnrtl-C", 2);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		ft_putstr_fd(RED"can't catch cntrl-\\", 2);
}
//int	main(int ac, char **av)
int	main(void)
{
	t_struct	shell;

	print_welcome();
	start_create_env(&shell);
	signals();
	// if (ac == 2)
	// {
	// 	shell.commande_tape = av[1];
	// 	if (shell.commande_tape)
	// 	{
	// 		if (shell.commande_tape[0])
	// 		{
	// 			divise_commande(&shell, shell.commande_tape);
	// 			if (shell.commands[0][0] != '|')
	// 			{
	// 				run_commands(&shell);
	// 				ft_free_cmd(shell.commands);
	// 			}
	// 			else
	// 				printf("Minishell: syntax error near unexpected token `|'\n");
	// 			free(shell.commande_tape);
	// 		}
	// 	}
	// }
	while (1)
	{
		shell.output_fd = 1;
		shell.input_fd = 0;
		rl_catch_signals = 0;
		commande_tape(&shell);
		if (shell.commande_tape)
		{
			if (shell.commande_tape[0])
			{
				divise_commande(&shell, shell.commande_tape);
				if (shell.commands[0][0] != '|')
				{
					run_commands(&shell);
				}
				else
					printf("Minishell: syntax error near unexpected token `|'\n");
				// ft_free_cmd(shell.commands);
			}
		}
	}
}

void	print_welcome(void)
{
	printf("%s*****************************************************\n", RED);
	printf("%s|                                                   |\n", RED);
	printf("%s|     Welcome to Souchen && Yismaili Minishell      |\n", RED);
	printf("%s|                                                   |\n", RED);
	printf("%s*****************************************************\n", RED);
}

int	commande_tape(t_struct	*shell)
{
	// shell->home = ft_strdup(find_env_tmp(shell, "HOME"));
	// if (!shell->home)
	// 	ft_die("PATH not fuond\n");
	shell->commande_tape = readline(GREEN"Minishell-1.0$ "WHITE);
	if (shell->commande_tape)
		add_history(shell->commande_tape);
	if (!shell->commande_tape)
		exit(1);
	return (1);
}
 
void ft_check_env(char **env)
{
	int i = 0;

	if (!env)
		glob_var = 0;
	while (env[i])
	{
		i++;
	}
	glob_var = i;
}
void	ft_free_cmd(char **cmd)
{
	int i = 0;

	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
}