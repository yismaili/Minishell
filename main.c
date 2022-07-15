/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/07/15 22:12:42 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
 /****************************** sigals**************************************/
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
/*****************************************************************************/
int	main(void)
{
	t_struct	shell;

	
	print_welcome();
	envernoment(&shell);
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

void	commande_tape(t_struct	*shell)
{
	char	*prompt;

	shell->home = ft_strdup(find_envernement(shell, "HOME"));
	prompt = create_prompt();
	shell->commande_tape = readline(prompt);
	if (shell->commande_tape)
        add_history(shell->commande_tape);
	if (!shell->commande_tape)
		exit(1);
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
	prompt = ft_strjoin(red, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(red);
	prompt = ft_strjoin(prompt, " $ ");
	return (prompt);
}
