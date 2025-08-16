/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 21:58:49 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes ***************************************************************** */

# include "../gc/includes/gc.h"
# include "../libft/includes/libft.h"
# include <bits/types/siginfo_t.h>
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pwd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define SIG_NONE 0
# define SIG_INTERRUPT 1
# define SIG_QUIT 2
# define SIG_EOF 3
# define PROMPT_MODE 0
# define HEREDOC_MODE 1

# ifndef MAX_VAR_NAME_LEN
#  define MAX_VAR_NAME_LEN 256
# endif

/* typedef ****************************************************************** */

typedef struct s_expand_params
{
	int							start;
	int							end;
	char						quote;
}								t_expand_params;

typedef struct s_path
{
	char						*dir;
	struct s_path				*prev;
	struct s_path				*next;
}								t_path;

// TOKEN ------------------------------

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_INVALID,
	TOKEN_EOF
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

// HEREDOC --------------------------------

typedef struct s_heredoc_data
{
	char						*delimiter;
	int							fd;
	char						*tmp_filename;
	int							expand;
}								t_heredoc_data;

// AST --------------------------------

typedef enum e_ast_type
{
	AST_CMD,
	AST_WORD,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_REDIR_APPEND,
	AST_HEREDOC,
	AST_AND,
	AST_OR
}								t_ast_type;

typedef struct s_ast
{
	t_ast_type					type;
	char						*word;
	char						**args;
	char						*filename;
	t_heredoc_data				*heredoc_data;
	struct s_ast				*left;
	struct s_ast				*right;
}								t_ast;

// REDIR (if needed) ------------------

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	struct s_redir				*next;
}								t_redir;

// SYS --------------------------------

typedef struct s_env
{
	char						*var;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_sys
{
	t_token						*token;
	t_ast						*ast;
	t_env						*env_lst;
	char						**envp;
	int							exit_status;
	int							path_hide;
	int							exit;
	int							last_status;
	int							in_pipe;
	int							hd_exp;
}								t_sys;

typedef struct s_pipe_fork
{
	int							pipe_fd[2];
	pid_t						pid_l;
	pid_t						pid_r;
}								t_pipe_fork;

/* global ******************************************************************* */

extern volatile sig_atomic_t	g_signal;

/* prototypes *************************************************************** */

// init.c -----------------------------

int								init_shell(t_sys **sys, char **envp);

// signals.c --------------------------

void							setup_signals(void);
void							heredoc_sigint_handler(int sig);
int								is_interactive_interrupt(int set_val);
void							handle_sigint_interactive(int sig);
void							handle_sigquit(int sig);
void							sigint_prompt(int sig);
void							sigquit_prompt(int sig);
void							sigint_heredoc(int sig);
void							set_signals_prompt(void);
void							set_signals_heredoc(void);
void							signals_handler(int mode);

// exec.c -----------------------------

int								execute_cmd(t_ast *node, t_sys *sys);
int								execute(t_ast *node, t_sys *sys);
int								shell_loop(t_sys *sys);

// exec_cmd.c -------------------------

int								execute_builtin(t_ast *node, t_sys *sys);
int								execute_external(t_ast *node, t_sys *sys);
int								execute_forked_cmd(t_ast *node, t_sys *sys);
int								is_builtin(char *cmd);

// pipe.c -----------------------------

int								handle_pipe(t_ast *node, t_sys *sys);
int								fork_left(t_ast *node, t_sys *sys,
									t_pipe_fork *fd);
int								fork_right(t_ast *node, t_sys *sys,
									t_pipe_fork *fd);

// env_array.c

char							**dup_array(char **array);
int								update_env_array(t_sys *sys);

// env_lst.c --------------------------

void							free_envnode(t_env *env_lst);
int								ft_envsize(t_env *env_lst);
t_env							*gc_envnew(char *var, char *content);
void							ft_envadd_back(t_env **env_lst, t_env *new);

// env_utils.c ------------------------

int								is_valid_identifier(char *arg);
int								unset_env_var(t_sys *sys, t_env **env_lst,
									char *var_name);
int								set_env_var(t_sys *sys, t_env **envp,
									char *var_name, char *content);
int								append_env_var(t_sys *sys, t_env **env_lst,
									char *var_name, char *content);
char							*get_env_var(char *var_name, t_env *env_lst);

// path.c -----------------------------

char							*find_cmd_path(t_sys *sys, char *cmd);
char							*get_home_dir(t_sys *sys);

// redir.c ----------------------------

int								handle_redirection(t_ast *node, t_sys *sys);
int								has_quotes(char *str);

// /built-ins -------------------------

int								builtin_cd(t_ast *node, t_sys *sys);
int								builtin_env(t_sys *sys);
int								builtin_echo(t_ast *node, t_sys *sys);
int								builtin_exit(t_ast *node, t_sys *sys);
int								builtin_export(t_ast *node, t_sys *sys);
int								builtin_pwd(t_sys *sys);
int								builtin_unset(t_ast *node, t_sys *sys);

// export_utils  -------------------------

t_env							*find_next_env(t_env *env_lst,
									char *last_printed);
int								is_invalid_export_key(char *var, char *arg);

// cd_path.c -------------------------

char							*build_logical_path(char *current_pwd,
									char *user_input);
char							*get_path(t_env *envp, char *arg);
void							print_not_a_dir(char *arg);

// bi_utils.c ------------------------

long long int					ft_atoll(const char *nptr, int *fail);
bool							is_valid_env_var_name(const char *name);

// lexer.c ----------------------------

t_token							*lexer(char *input);

// lexer_utils.c

int								handle_operator_token(char *input, int i,
									char **value, t_token_type *type);
int								parse_ansi_c_quoted(char *input, int i,
									char **value, t_token_type *type);

// parser.c --------------------------

t_ast							*parse_command(t_token **tokens, t_sys *sys);
char							*process_segment(char *str, int *i,
									int seg_start, t_sys *sys);
t_ast							*parse_line(char *line, t_sys *sys);
t_ast							*parse_simple_command(t_token **tokens);

// parser_utils.c --------------------

char							*extract_env_value(char *str, int *i, int start,
									t_sys *sys);
t_ast							*parse_and_or(t_token **tokens, t_sys *sys);

// parser_utils2.c

char							**allocate_args(int count, t_ast *node);
int								fill_args_array(t_token **tokens, char **args,
									int count);
t_ast							*handle_empty_command(t_ast *redirs);
char							*get_filename_from_t(t_token *filename_token);

// pipeline.c -------------------------

t_ast							*parse_pipeline(t_token **tokens, t_sys *sys);

// utils.c ----------------------------

int								count_consecutive_words(t_token *tokens);
char							**gather_all_words(t_token **tokens);
int								count_split_entries(char **split);
char							**copy_and_merge(char **flat, char **split,
									int total, int count);
int								skip_whitespace(char *input, int i);
int								has_quotes(char *str);

// vars_utils.c -----------------------

char							*expand_variable(char *str, int *i, t_sys *sys);

// operator.c -------------------------

int								is_operator(char c);
int								extract_operator(char *input, int i, char **op);
int								check_operator_syntax(t_token *curr,
									t_token *prev);
t_token_type					get_operator_type(char *input, int i);

// quotes.c ---------------------------

void							handle_single_quote(char *str, int *i,
									char **result);
void							handle_double_quote(char *str, int *i,
									t_sys *sys, char **result);
void							handle_quote_section(char *str, int *i,
									char **result, t_sys *sys);
int								extract_word_with_quotes(char *input, int i,
									char **word);

// quote_expand.c ---------------------

char							*expand_in_double_quotes(char *str, int start,
									int end, t_sys *sys);
char							*expand_quoted_content(char *str,
									t_expand_params *params, t_sys *sys);
char							*expand_outside_quotes(char *str, int start,
									int end, t_sys *sys);

// quotes_utils.c ---------------------

char							*remove_quotes(char *str);
int								are_quotes_closed(const char *str);

// ast.c-------------------------------

t_ast							*new_ast_node(t_ast_type type);
t_ast							*create_pipeline_node(t_ast *left,
									t_ast *right);
void							free_ast(t_ast *ast);

// tokens.c ---------------------------

int								is_operator_token(t_token_type type);
int								validate_syntax(t_token *tokens);
int								count_word_tokens(t_token *start);
void							free_tokens(t_token *tokens);

// tokens2.c --------------------------

t_token							*create_token(t_token_type type, char *value);
void							add_token(t_token **tokens, t_token *new_token);
// void							expand_tokens(t_token *tokens, t_sys *sys);
void							expand_tokens(t_token **tokens_ptr, t_sys *sys);
int								should_split_token(char *original,
									char *expanded);

// args.c -----------------------------

char							**merge_args(char **old_args, char **new_args);
t_ast							*collect_redirections_and_args(t_token **tokens,
									t_ast **cmd, t_sys *sys);
int								handle_redirection_args(t_token **tokens,
									t_ast **redirs, t_ast **cmd, t_sys *sys);
int								handle_word_args(t_token **tokens, t_ast **cmd,
									t_ast **redirs);

// redir.c ----------------------------

t_ast							*attach_redirections(t_ast *cmd, t_ast *redir);
t_ast							*parse_single_redirection(t_token **tokens,
									t_sys *sys);
int								is_redirection_token(t_token_type type);
int								check_redirection_syntax(t_token *curr);
t_ast_type						get_redirection_type(t_token_type token_type);

// heredoc.c --------------------------

char							*generate_tmp_filename(void);
char							*expand_heredoc_line(char *line, t_sys *sys);

// heredoc_handler.c ------------------

t_heredoc_data					*get_heredoc_data(char *delimiter, t_sys *sys);
void							clean_heredoc_data(t_heredoc_data *data);

// heredoc_utils.c

int								read_heredoc_content(t_heredoc_data *data,
									char *delimiter, t_sys *sys);
int								heredoc_interrupted(int b);

#endif