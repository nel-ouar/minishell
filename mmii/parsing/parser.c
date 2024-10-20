

#include "../minishell.h"


// Function to handle filenames
void	handle_filename(const char *input, int *i, int len, t_token **tokens)
{
	int		start;
	char	*filename;

	start = *i;
	while (*i < len && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '\''
		&& input[*i] != '"')
	{
		(*i)++;
	}
	filename = ft_substr(input, start, *i - start);
	add_token(tokens, new_token(FILENAME, filename));
	free(filename);
}


void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

int	check_heredoc_delim(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC)
		{
			if (!tokens->next ||
				(ft_strcmp(tokens->next->value, "<") == 0
						|| ft_strcmp(tokens->next->value, ">") == 0 ||
					ft_strcmp(tokens->next->value, ">>") == 0
						|| ft_strcmp(tokens->next->value, "<<") == 0 ||
					ft_strcmp(tokens->next->value, "|") == 0) ||
				ft_strcmp(tokens->next->value, "") == 0)
			{
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

void	free_command(t_command *cmd)
{
	t_redirection	*redir;
	t_redirection	*next;

	if (cmd->name)
		free(cmd->name);
	for (int i = 0; i < cmd->arg_count; i++)
	{
		free(cmd->args[i]);
	}
	free(cmd->args);
	redir = cmd->redirections;
	while (redir)
	{
		next = redir->next;
		free(redir->filename);
		free(redir);
		redir = next;
	}
	free(cmd);
}

void	free_command_list(t_command *list)
{
	t_command	*next;

	while (list)
	{
		next = list->next;
		free_command(list);
		list = next;
	}
}
