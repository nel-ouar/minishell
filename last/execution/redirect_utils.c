/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakhtou <stakhtou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:05:45 by stakhtou          #+#    #+#             */
/*   Updated: 2024/10/21 18:30:12 by stakhtou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_in(t_command *cmd, int fd_in)
{
	t_redirection	*redir;
	int				new_fd;

	redir = cmd->redirections;
	new_fd = fd_in;
	while (redir)
	{
		if (redir->type == INPUT)
		{
			if (new_fd != fd_in)
				close(new_fd);
			new_fd = open(redir->filename, O_RDONLY);
			if (new_fd == -1)
				return (ft_putstr_fd("minishell: ", 2), perror(redir->filename),
					-1);
		}
		else if (redir->type == HEREDOC)
		{
			if (new_fd != fd_in)
				close(new_fd);
			new_fd = open(redir->filename, O_RDONLY);
		}
		redir = redir->next;
	}
	return (new_fd);
}

int	get_out(t_command *cmd, int fd_out)
{
	t_redirection	*redir;
	int				new_fd;

	redir = cmd->redirections;
	new_fd = fd_out;
	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == APPEND)
		{
			if (new_fd != fd_out)
				close(new_fd);
			if (redir->type == OUTPUT)
				new_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else
				new_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND,
						0644);
			dup2(new_fd, fd_out);
			close(new_fd);
			if (new_fd == -1 || dup2(new_fd, fd_out) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (new_fd);
}
