/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/07/24 05:50:51 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd(create_prompt(), 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
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

	print_welcome();
	start_create_env(&shell);
	signals();
	while (1)
	{
		shell.output_fd = 1;
		shell.input_fd = 0;
		commande_tape(&shell);
		if (shell.commande_tape)
		{
			if (shell.commande_tape[0])
			{
				divise_commande(&shell, shell.commande_tape);
				if (shell.commands[0][0] != '|')
					run_commands(&shell);
				else
					printf("Minishell: syntax error near unexpected token `|'\n");
				free2(shell.commands);
				free(shell.commande_tape);
			}
		}
	}
		
}

void	print_welcome(void)
{
	printf("%s*****************************************************\n", WHITE);
	printf("%s¦                                                   *\n", WHITE);
	printf("%s¦ Welcome to Souchen Minishell ^^^^^^^^^^^^^^^^^^^^^*\n", WHITE);
	printf("%s¦                                                   *\n", WHITE);
	printf("%s*****************************************************\n", WHITE);
}

int	commande_tape(t_struct	*shell)
{
	// shell->home = ft_strdup(find_env_tmp(shell, "HOME"));
	// if (!shell->home)
	// 	ft_die("PATH not fuond\n");
	shell->commande_tape = readline(create_prompt());
	if (shell->commande_tape)
		add_history(shell->commande_tape);
	if (!shell->commande_tape)
		exit(1);
	return (1);
}

char	*create_prompt(void)
{
	char	*buf;
	char	*prompt;
	char	*white;
	char	*red;
	//char	*green;

	buf = get_current_dir();
	red = ft_strdup(RED);
	white = ft_strdup(WHITE);
	//green = ft_strdup(GREEN);
	prompt = ft_strjoin(white, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(red);
	prompt = ft_strjoin(prompt, "$ ");
	return (prompt);
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