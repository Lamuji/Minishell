/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <edalmis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:53:59 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/29 14:28:50 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <termios.h>
# include "../libft/libft.h"

# define RESET "\033[0m"
# define WHITE "\033[0;37m"
# define SUCCESS 0
# define FAILURE 1
# define PROMPT "💻\033[1;37m ~ Minishell : \033[0m"

typedef struct s_cmd
{
	char			**cmd;
	int				nb_cmd;
	int				nb_args;
	int				status;
	int				pipe[2];
	int				pos;
	int				in;
	int				out;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_line
{
	char	*cmd_line;
	char	**cmds;
	int		i;
}	t_line;

typedef struct s_token
{
	char			*token;
	int				type;
	int				state;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_data
{
	int		x_i;
	int		x_j;
	char	*rstr;
	int		ec_x;
	int		t_state;
	int		t_start;
	int		t_type;
	int		nb_cmd;
	char	**envp;
	char	*cmdline;
	char	*path;
	char	**cmd_lines;
	t_token	*token;
	char	**cmd_tab;
	t_cmd	*cmd;
	t_list	*env;
	t_list	*cenv;
}				t_data;

enum e_tk_types {
	BLANK = 1,	
	WORD,		
	VAR,		
	PIPE,
	LESSER,
	GREATER,
	DLESSER,
	DGREATER,
	END
};

enum e_states {
	DEFAULT,
	SIMPLE,
	DOUBLE
};

int		redir_dekita(t_token *tk);
void	norme(t_data *data, int ac, char **av, char **env);
void	var_cmd(t_data *data);
int		pre_exec(t_data *data);
char	*cases_export(t_data *data, char *temp_str, char *sstr);
void	add_at_export2(t_list *prec, t_list *cur, t_list *cell, t_list lst);
char	*export_squote(t_data *data, char *temp_str, char *sstr);
int		check_export_args_str(char *str);
void	add_var_last_export(t_data *data, t_list **lst,
			char *str, int export);
void	exec_export2(t_data *data, int i, int j);
void	signals(void);
void	print_list2(t_list *lst);
void	ft_begining(int ac, char **av);
void	ft_var_and_token(t_data *data);
int		tokenizer2(t_data *data, char *cmdline, int i, int end);
int		stock_sep2(t_token **tk_list, char *line, int index, int type);
int		verify_squote(char *c);
int		verify_dquote(char *c);
int		len_list(t_list *lst);
int		check_if_arg_in_env(char *var_name, t_list *lst);
t_list	*creat_cell2(char *str);
char	*ft_arrange_bin(char *bin, char **sp_path, int i, t_cmd *cmd);
int		erase_var(t_token **tk_node, char *str, int index);
int		erase_and_replace(t_token **tk_node, char *str,
			char *var_value, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*grep_env_var(t_data *data, char *var);
void	state_update(t_token **tk, char c);
void	ft_env(t_data *data, char **env);
void	manager(void *ptr, int err);
char	**copyenv(t_data *data);
int		ft_envsize(t_list *lst);
int		verify_char(char *c);
void	print_list(t_list *lst, int d);

void	handler(int signum);
void	handler_exec(int signum);

void	cmd_builtins(t_data *data);
char	*add_content_to_var(char *dest, char *content_to_add, int i);
void	exec_cd(t_data *data, char *path);
char	*ft_strstr(char *str, char *to_find);
void	ft_echo(t_data *data, int i);
void	pwd(void);
void	exec_env(t_data *data);
void	exec_export(t_data *data, int i);
int		exec_unset(t_data *data);

int		execution(t_data *data);
void	hound(t_cmd **cmd);
int		launch_exec(t_data *data);
int		child_process(t_data *data);
void	exec_cmd(t_data *data, char **env);
void	exit_exe(void);
void	not_found(t_data *data);

char	*identify_variable(char *str);
int		is_var_compliant(char c);
int		count_len_var(char *str);
int		substitute_var(t_data *data, t_token **tk);
int		replacement(t_token **tk_node, char *var_value, int index);
char	*retrieve_val(char *str, t_data *data);
int		count_length(char *str, int count, int i);
int		if_quotes(char *str);
int		handle_quotes(t_data *data);
int		tokenize_var(t_data *data);
int		remove_quotes(t_token **tk_node);

int		tokenizer(t_data *data, char *cmdline);
int		nb_pipes(t_token *tk);
void	set_cmd(t_token *tk, t_cmd **cmd, int pipes);
t_cmd	*get_cmds(t_token **tk);
void	set_args(t_token **token, int nb_args, char ***args);
char	**get_args(t_token *token);
int		get_nb_args(t_token *token);
t_cmd	*init_cmd(void);
void	addback_cmd(t_cmd **cmd, t_cmd *new);
t_cmd	*get_last_cmd(t_cmd *cmd);

int		open_pipes(t_cmd *cmd);
void	close_pipes(t_cmd *cmd);
void	handle_pipes(t_cmd *cmd);

int		is_empty_list(t_list *lst);
int		is_builtins(t_data *data);
t_token	*lstnew_tk(char *str, int type, int state);
void	lst_add_back_tk(t_token **alst, t_token *new_node);
void	lstdelone_tk(t_token *lst, void (*del)(void *));
void	lstclear_tk(t_token **lst);
void	lstclear_cmd(t_cmd **cmd);
void	lstclear_env(t_data *data);
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);
void	creat_cell(t_list **cell, char *str);
t_list	*empty_list(void);

int		init_env_file(void);
char	*ft_search_env_value(char *var, char *name);
int		ft_is_name_env_arr(char *name, char **env);
void	set_nbcmd_envfile(t_cmd *cmd);
void	increment_shlvl(char ***env);
void	set_exitstatus(int status);
char	*ft_getenv_arr(char *name, char **envp);
char	**ft_get_new_env_content(char *name, char *value);
char	*get_env_var(char *name);
int		get_exitstatus(void);
char	*ft_before_c(char *s, int c);
int		ft_delete_env_content(char *name, char ***env);
int		ft_unsetenv(char *name, char ***env);
int		exception(t_token **tk_list);
void	free_line(t_data *data);
int		check_ops_rule(t_token **tk_list);
char	*create_prompt(void);
char	*ft_strnew(size_t size);
char	*ft_strjoinch(char const *s1, char c);
int		ft_strstartswith(char *s1, char *s2);
char	*ft_pathjoin(char *p1, char *p2);
char	*ft_strjoincl(char *s1, char *s2, int free_both);
void	*ft_memalloc(size_t size);
void	ft_freestrarr(char **arr);
void	exit_shell(void);
int		ft_strendswith(char *s1, char *s2);
void	ft_line_init(t_line *line);
int		ft_isemptystr(char *str, int consider_space);
char	**ft_strsplit(char const *s, char c);
int		ft_countwords(char const *str, char c);
char	*ft_realloc(char *s1, char *s2);
int		execute_commands(char **commands);
char	**ft_strsplitall(char const *s);
int		ft_countwords(char const *str, char c);
int		ft_countwordsall(char const *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_concat(char *s1, char *s2);

char	*ft_str_chr(const char *str, int c);
int		ft_strchr_env(char *str, char *to_find);
char	*ft_strstr(char *str, char *to_find);
int		ft_strstr_int(char *str, char *to_find);
char	*act2(char *new_dest_content, char *content_to_add, int i);
char	*act(char *dest, char *new_dest_content, char *content_to_add, int i);
char	*ft_getenv(char *env, t_data *data, int i);
t_list	*add_at(t_list *lst, char *str, int pos, int i);
int		count_equals(char *str);
int		is_space(char x);

#endif
