/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:19 by souchen           #+#    #+#             */
/*   Updated: 2022/07/04 17:31:05 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	t_struct	shell;

	
	print_welcome();
	envernoment(&shell);
	while (1)
	{
		shell.output_fd = 1;
	shell.input_fd = 0;
		commande_tape(&shell);
		if (shell.commande_tape)
		{
			//if (shell.commande_tape[0])
			//{
				divise_commande(&shell, shell.commande_tape);
				if (shell.commands[0][0] != '|')
					run_commands(&shell);
				else
					printf("bash: syntax error near unexpected token `|'");
				free2(shell.commands);
				free(shell.commande_tape);
			//}
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
	add_history(shell->commande_tape);
}

char	*create_prompt(void)
{
	char	*buf;
	char	*prompt;
	char	*white;
	char	*red;
	char	*green;

	buf = get_current_dir();
	red = ft_strdup(RED);
	white = ft_strdup(WHITE);
	green = ft_strdup(GREEN);
	prompt = ft_strjoin(red, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(red);
	prompt = ft_strjoin(prompt, " $-> ");
	return (prompt);
}
