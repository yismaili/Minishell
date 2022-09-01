/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:30:46 by souchen           #+#    #+#             */
/*   Updated: 2022/09/01 17:35:45 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include \
	</goinfre/yismaili/.brew/opt/readline/include/readline/readline.h>
# include \
	</goinfre/yismaili/.brew/opt/readline/include/readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

# define DOUBLE_QUOTE '\"'
# define QUOTE '\''
# define D_QUOTE_S "\""
# define QUOTE_S "\'"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\033[0;31m"
# define PIPE_ERROR "Minishell: syntax error near unexpected token `|'\n"
# define QUOTE_ERROR "> bash: unexpected EOF while looking for matching quote\n"
# define RED_ERROR "bash: syntax error near unexpected token `newline'\n"

typedef struct s_gl
{
	int	g_var;
	int	g_status;
	int	g_isrun;
}	t_gl;

t_gl	g_var;

typedef struct s_env
{
	char	**env;
	int		len;
	char	**tmp_var;
	char	**tmp_con;
	char	**str;
	int		position;
}	t_env;

typedef struct s_divise
{
	int	number_command;
	int	initial;
	int	len;
	int	quote;
	int	pipe;
}	t_divise;

typedef struct s_arg
{
	char	*all_cmd;
	char	*to_exec;
	char	*txt_toprint;
	char	quote;
	char	*seconde;
	char	*first;
	int		i;
	int		init;
	int		len;
	int		position;
}			t_arg;

typedef struct s_struct
{
	int			builtin_exist;
	int			last_redir;
	int			output_fd;
	int			input_fd;
	int			cmp;
	int			id;
	int			fd_out;
	int			last_in;
	char		*line_commande;
	char		*commande_tape;
	char		*home;
	pid_t		pid;
	int			test;
	char		*commands[600000];
	char		**arguments;
	int			i;
	int			j;
	int			len;
	t_env		env_aux;
	t_env		env;
	t_divise	divise;
	int			indice_space;
	t_arg		arg;
	int			q1;
	int			variable;
	int			q2;
	int			size;
	int			dup_pipe;
	int			quote;
	int			double_quote;
	int			var;
	int			space;
	int			right;
	int			indice;
	char		**path;
	int			inc1;
	int			inc2;
	int			check;
	int			last;
	int			quote_cmd;
	int			dquote_cmd;
	int			start;
	int			end;
	int			dup_red;
	int			i_for_chek;
	int			pos;
	int			not_alpha;
	int			failed;
	int			qot;
	int			qot_tow;
	char		*name;
	char		*msg;
	int			f_pipe;
	int			cmp_space;
	int			alpha;
	int			con_failed;
	int			fic;
	int			dolar;
	int			t;
	int			not_alpha2;
	int			fd;
	char		*frst;
	char		*scnd;
	int			var2;
	int			tty;
	int			chek_plc;
	int			chek_num;
	int			chek_plc_;
	int			chek_dlr;
	int			chek_test;
	int			count_dolr;
	int			dif_j;
}				t_struct;

int		builtin_exist(t_struct *shell);
int		run_builtin(t_struct *shell);
int		count_len_env(t_struct *shell);
void	ft_exit(t_struct *shell);
void	free_line(char *line_read);
void	ft_unset(t_struct *shell);
void	remove_env(t_struct *shell);
void	print_welcome(void);
void	run_commands(t_struct *shell);
void	run_commande_next(t_struct *shell);
int		fun_redirection(t_struct *shell);
int		execution(t_struct *shell);
int		divise_commande(t_struct *shell, char *in);
int		arguments_func(t_struct *shell);
int		argument_find_char(char *string, char needle);
void	free_arg(t_arg *arg);
void	finish_put_arg(t_struct *shell, t_arg *arg);
void	init_divise_struct(t_struct *shell);
void	ft_env(t_struct *shell);
void	ft_export(t_struct *shell);
bool	there_is_home(t_struct *shell);
int		ft_cd(t_struct *shell);
void	ft_pwd(t_struct *shell);
void	ft_echo(t_struct *shell);
int		init_echo(t_struct *shell, int n);
void	print_echo(t_struct *shell, char *shell_print);
void	ft_export(t_struct *shell);
void	verify_if_env_exists(t_struct *shell);
void	export_to_env(t_struct *shell, char *tab1, char *tab2);
void	pipe_next(t_struct *shell, int i, char *command);
int		inredirection(t_struct *shell);
int		outredirection(t_struct *shell);
int		next_run_commands(t_struct *shell);
int		next(t_struct *shell, char*commande_read);
char	*execute_cmd(t_struct *shell);
void	output_input(t_struct *shell);
void	check_to_execute(t_struct *shell);
void	sig_handler(int signum);
void	cmd_not_found(t_struct *shell);
int		check_export(t_struct *export);
int		ft_search(t_struct *env, char *var);
int		malloc_env_tmp(t_struct *shell);
char	*find_env_tmp(t_struct *shell, char *search);
int		commande_tape(t_struct	*shell, int *size);
int		malloc_env_aux_tmp(t_struct *shell);
void	ft_die(char *str);
int		create_env_tmp(t_struct *shell, char **my_env);
int		start_create_env(t_struct *shell);
void	ft_die_malloc(char *str);
void	ft_check_env(char	**env);
void	ft_free_env(char **env);
void	ft_free_cmd(char **cmd);
int		is_empty(char *input);
void	ft_not_found(char *dir);
int		ft_search_in_env(t_struct *env, char	*var, char *con);
void	ft_wait_pid(t_struct *shell);
void	ft_free(t_struct *shell);
void	get_exit_code(int status);
char	**get_path(t_struct *ptr);
void	next_execute_cmd(char **cmd_path);
void	process_shild_execute(char **path, t_struct *shell);
void	print_cmd_not_f(t_struct *shell);
void	signals(void);
void	restore_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
int		ft_cd_tool(t_struct *shell);
char	*ft_oldpath(t_struct *shell);
int		ft_change_dir(t_struct *shell, char *chpath);
int		ft_check_cd(t_struct *shell);
void	replace_oldpwd(t_struct *env);
void	replace_pwd(t_struct *env);
void	ft_echo_tool(t_struct *shell, char *echo_print);
char	*remplir(char *s1, char c, int len, t_struct *shell);
int		arg_func(t_struct *shell);
int		find_char(char *string, char c);
char	*ft_split_cmd(char *cmd, t_struct *shell);
char	*ft_remove_quot(char *s1, char c, t_struct *shell);
int		next_inredirection(t_struct *shell);
t_arg	*init_arg(void);
void	echo_with_quote(char *echo_print, t_struct *shell);
void	echo_with_dollar(t_struct *shell, char *splt_quot);
void	swap_env(char **dup_env);
void	export_with_arg(t_struct *shell, char *arguments);
void	sort_env(t_struct *shell);
void	ft_print_export(char **exp, t_struct *shell);
void	next_export(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2);
int		next_execute_commands(t_struct *shell, int i, char *command);
void	ft_cmd(char **env);
void	cmd_not_found2(t_struct *shell);
int		create_process(t_struct *shell);
char	*find_env(t_struct *shell, char *search);
char	*ft_check_quotes_frst(t_struct *shell);
char	*ft_check_quotes_scnd(t_struct *shell);
int		ft_play_herdoc(t_struct *shell, char *fichier2, char *line);
void	run_commands_next(t_struct *shell);
void	ft_remplir_env(t_struct *env);
int		check_export_tow(t_struct *export);
int		check_export_con(char *export);
void	check_pipe(int i, t_struct *shell, char *commande_read);
void	check_quote(int i, t_struct *shell, char *commande, char c);
void	check_next_arg(t_struct *shell);
void	check_aux(t_struct *shell, int i);
int		ft_loop(char **splted);
int		ft_with_dlr(t_struct *shell);
int		ft_else(t_struct *shell, int i);
void	ft_execute_tools(t_struct *shell, int i, char *command);
char	*ft_return_con(t_struct *shell);
int		split_arg(t_struct *shell, char *cmd_joined);
int		check_quotes_next(t_struct *shell);
int		ft_check_quote(t_struct *shell);
void	ft_check_space(t_struct *shell);
int		ft_check_quote_pos(t_struct *shell, char	*cmd_joined);
void	check_char(t_struct *shell, char *commande_line);
char	*ft_split_cmd2(char	*cmd, t_struct *shell);
void	to_remove_quotes(t_struct *shell);
int		split_and_cas_error(t_struct *shell, char *fichier2);
int		run_commande_next1(t_struct *shell);
void	cas_error(t_struct *shell, char *msg);
int		ft_check_file(t_struct *shell, char	**fichier);
int		ft_builtin_exist_next(t_struct	*shell);
int		divise_pipe_redir_next(t_struct *shell, char *commande_read);
int		ft_next_echo(t_struct *shell);
void	ft_identifier_export(t_struct *shell);
void	sig_handler2(int sig);
void	sig(int nb);
void	cmd_not_found3(char *fichier);
int		red_with_dolar(char *fichier, t_struct *shell);
char	*herdoc_with_dolars(char *line, char *fichier, t_struct *shell);
char	*search_in_env(int j, char *f2, char *l, t_struct *s);
int		exit_with_arg(t_struct *shell);
void	cmp_spaces(t_struct *shell);
void	cas_failed(t_struct *shell);
int		check_file_dollar(char **f, char *f1, t_struct *shell);
int		in_check(char **fichier, char *fichier1);
void	remove_quote_to_file(t_struct *shell, int size);
int		cas_error_quote(t_struct *shell, int size);
void	ft_dup_rdtion(t_struct *shell);
void	cmp_q(t_struct *shell);
void	ft_identifier_export(t_struct *shell);
void	ft_split_argu(t_struct *shell, char *arguments);
int		len_ofarg(char *str);
void	next_export(t_struct *shell, char *new_elem_tab1, char *new_elem_tab2);
int		check_export(t_struct *export);
int		check_unset(char *arg);
void	ft_print_qot(t_struct *shell);
void	ft_chekexit_status(t_struct *shell);
void	for_close(t_struct *shell);
void	exp_with_pipe(t_struct *shell);
char	*ft_split_cmd3(char	*cmd, t_struct *shell);
char	*ft_chek_dlr_arg(char *arguments, t_struct *shell, char \
	**strrm, char *join);
char	**ft_splt_dlor_arg(char	*arguments, t_struct *shell);
int		ft_chek_isdigit(char *echo_print, t_struct	*shell);
char	**ft_split_num_dlr(t_struct *shell, char *echo_print, char num);
int		ft_skip_qote(char **splted, t_struct *shell, int *j);
void	ft_print_env_var(t_struct *shell, char *splted);
int		ft_next_echo_dlr(char **splted, t_struct *shell);
void	ft_count_doler(char *echo_print, t_struct *shell);
void	ft_print_env_var_next(t_struct *shell, char *splted, int i, int q);
int		ft_builtin_exist_else(t_struct	*shell);
int		run_builtin_next(t_struct *shell);
int		ft_failed_fork(void);
int		ft_next_redirection(t_struct *shell, int size);
void	ft_print_msg(t_struct *shell, char	*line);
int		ft_count_len_ofqut(t_struct	*shell, char *line, char *fic);
char	*ft_hndl_qot(t_struct *shell, char *line, char *fic, int j);
char	*ft_hndl_qot_next(t_struct *shell, char *line, char *fic, int j);
int		ft_next_outredirection(t_struct *shell, char **fichier1);
int		ft_next_inredirection(t_struct	*shell, char **fichier2, char *line);
#endif
