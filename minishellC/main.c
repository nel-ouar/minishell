   #include "minishell.h"


void init_shell()
{
    while(1)
    {
        char *line = readline("minishell$ ");
        if (line == NULL)
        {
            break;
        }
        if (ft_strlen(line) > 0)
        {
            t_token *tokens = tokenize_input(line);
            if (tokens)
            {
                print_tokens(tokens);  // Print tokens for debugging
                t_command *commands = parse_tokens(tokens);
                if (commands)
                {
                    print_command_list(commands);  // Print parsed commands for debugging
                    free_command_list(commands);
                }
                free_tokens(tokens);  // Free tokens
            }
            add_history(line);
        }
        free(line);
    }
}
int main()
{
    init_shell();
    // free_tokens(tokens);  // Removed as tokens is not defined in main
    return 0;
}    
