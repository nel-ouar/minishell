#include "../minishell.h"

char **ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (NULL);
}

char *check_path(char **cmd, char **path)
{
    int i;
    char *new_cmd;
    char *new_path;

    i = 0;
    while (path[i++])
    {
        new_cmd = ft_strjoin("/", cmd[0]);
        new_path = ft_strjoin(path[i], new_cmd);
        free(new_cmd);
        if (access(new_path, F_OK) == 0)
        {
            ft_free(path);
            return (new_path);
        }
        free(new_path);
    }
    ft_free(path);
    return (ft_strdup(cmd[0])); // leak;
}

char *get_path(char **cmd, char *envp[])
{
    int i;
    char **path;

    i = 0;
    while (ft_strncmp(envp[i], "PATH", 4) != 0)
        i++;
    path = ft_split(envp[i] + 5, ':');
    i = 0;
    return (check_path(cmd, path));
}


void execute_cmd(char **cmd, char **env, int *exit_code)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        return;
        }
        else if (pid == 0)
        {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (execve(get_path(cmd, env), cmd, env) == -1)
        {
            perror("minishell: execution failed");
            exit(127);
        }
    }
    else 
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            *exit_code = WEXITSTATUS(status);
        } 
        else
        {
            *exit_code = 128 + WTERMSIG(status);
    }
}

void exec(t_command *cmd, char **env)
{
    execute_cmd(cmd->cmd, env);
}


void execute_single_cmd(t_command *cmd, char **env)
{   
    int cmd_type = is_builtin(cmd);
    if (cmd->redirrections)
        ft_redic(cmd, env);
    else
    {
        if (cmd_type == NOT_BUILT_IN)
            exec(cmd, env);
        else
            execute_builtin(cmd, env, cmd_type);
    }
}