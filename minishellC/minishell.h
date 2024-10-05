#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "1337Libft/libft.h"
#define NOT_BUILT_IN -1

typedef enum {
   COMMANDE,
   ARG,
    REDIRECTION,
    PIPE,
    APPEND,
    INPUT,
    OUTPUT,
    HEREDOC,
    FILENAME,
    DELIMITER,
    ENV_VAR,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    EXIT_STATUS,

} t_token_type;

typedef struct s_token {
    int type;
     int space;
    char *value;
    struct s_token *next;
} t_token;

// typedef struct s_command {
//     char *name;
//     char **args;
//     int arg_count;
//     int pipe_next;
//     struct s_redirection *redirections;
//     struct s_command *next;
// } t_command;

typedef struct s_redirection {
    int type;  // INPUT, OUTPUT, or APPEND
	int					fd;
	char				*delimiter;
    struct s_redirection *next;
} t_redirection;

typedef struct s_tokenizer_params {
    const char *input;
    int i;
    int len;
    int expect_command;
    int expect_filename;
    t_token **tokens;
} t_tokenizer_params;

// Existing function prototypes
void init_shell();
void sigint_handler(int sig);
void sigquit_handler(int sig);
void all_signals();
t_token *new_token(int type, const char *value);
void add_token(t_token **head, t_token *new_token);
t_token *tokenize_input(const char *input);
char *remove_quotes(const char *str);
void print_tokens(t_token *tokens);
int my_mkstemp(char *template);
char *handle_heredoc(const char *delimiter, int expand_vars);

// New function prototypes for command parsing
t_command *new_command();
void add_argument(t_command *cmd, char *arg);
void add_redirection(t_command *cmd, int type, char *filename);
void add_command(t_command **list, t_command *cmd);
t_command *parse_tokens(t_token *tokens);
void free_command(t_command *cmd);
void free_command_list(t_command *list);
void print_command_list(t_command *list);



typedef struct s_command
{
    char *name;
	char				**args;
	int					pipe;
	t_redirection			*redirrections;
	int					exit_val;
	struct s_command		*next;
}	t_command;

//builtins

void	update_old_pwd(char *old_pwd, char **env);
void	update_pwd(char *pwd, char **env);
char	*ft_chr(char **env, char *vrb);
void    cd(t_command *cmd, char **env);
int     echo(char **args);
int first_non_option(char **args);
int is_n_option(char *arg);
void	env(char **envp, char **after_expand);
int	double_pointer_len(char **str);
void	ft_setter(int value);
int	ft_getter(void);
void exit(t_command *cmd, char **env)
int	is_num(char *str);
void export(t_command *cmd, char **env);
int check_export(char *args);
void    export_helper(char *cmd, char **env, int len);
int check_env(char *cmd, char **env);
void    print_export(char *env);
void pwd(t_command *cmd, char **env)
void unset(t_command *cmd, char **env)
void unset_helper(char *cmd, char **env, int len);
size_t length(char *s);

//execution
void execute_single_cmd(t_command *input, char **env);
void exec(t_input *input, char **env);
void execute_cmd(char **cmd, char **env, int *exit_code);
char *get_path(char **cmd, char *envp[]);
char *check_path(char **cmd, char **path);
char **ft_free(char **str);

//redirection
void    ft_redict(t_command *cmd, char **env);
void redic_not_builtin(t_command *cmd, char **env);
void redic_builtin(t_command *cmd, char **env);
void exec_in_child(t_command *cmd, char **env);
int get_in_v2(t_command *tmp, int fd_in, int index);
int get_out(t_command *tmp, int fd_out);
int get_in(t_command *tmp, int fd_in);
void restore_fd(int in, int out, int new_in, int new_out);
void dup_in_out(int in, int out);

#endif