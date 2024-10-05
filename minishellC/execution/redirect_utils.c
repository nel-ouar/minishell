#include "../minishell.h"

void dup_in_out(int in, int out)
{
	if (in)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void restore_fd(int in, int out, int new_in, int new_out)
{
	if (in)
	{
		dup2(new_in, STDIN_FILENO);
		close(new_in);
	}
	if (out != 1)
	{
		dup2(new_out, STDOUT_FILENO);
		close(new_out);
	}
}

int get_in(t_command *tmp, int fd_in)
{
	t_redirection *tmp1;
	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
		{
			int fd = open(ft_strjoin("minishell_",ft_itoa(0)), O_RDWR);
			if (fd == -1)
				fd_in = fd;
		}
		tmp1 = tmp1->next;
	}
	return fd_in;
}

int get_out(t_command *tmp, int fd_out)
{
	t_redirection *tmp1;
	tmp1 = tmp->redirrections;
	fd_out = 1;
	while (tmp1)
	{
		if (tmp1->type == '>' && !tmp1->delimiter)
			fd_out = tmp1->fd;
		tmp1 = tmp1->next;
	}
	return fd_out;
}

int get_in_v2(t_command *tmp, int fd_in, int index)
{
	t_redirection *tmp1;
    int fd;
	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
		{
			fd = open(ft_strjoin("minishell_", ft_itoa(index)), O_RDWR);
			if (fd != -1)
				fd_in = fd;
		}
		tmp1 = tmp1->next;
	}
    if (fd)
	    unlink(ft_strjoin("minishell_", ft_itoa(index)));
	return fd_in;
}