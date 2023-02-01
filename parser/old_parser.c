/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmery <lmery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:20:24 by lmery             #+#    #+#             */
/*   Updated: 2023/01/20 17:32:26 by lmery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisheLLD.h"

static char	*ft_get_cmd_type(enum e_cmd_type type)
{
	if (type == CMD_REDIR)
		return ("Redir");
	else if (type == CMD_WORD)
		return ("Word");
	else if (type == CMD_PIPE)
		return ("Pipe");
	else if (type == CMD_EOF)
		return ("Eof");
	return (NULL);
}

static t_list	*lst_add_command(t_list **lst_cmd, t_command *command)
{
	t_list	*new;

	new = ft_lstnew(command);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(lst_cmd, new);
	return (*lst_cmd);
}

void	lst_print_command(t_list *lst_cmd)
{
	t_command	*cmd;
	int	i;

	printf("\n___________________________________________ \n\n");
	i = 0;
	while (lst_cmd)
	{
		cmd = lst_cmd->content;
		printf("commande %d, type %d : %s\n", i, cmd->type, cmd->text);
		i++;
		lst_cmd = lst_cmd->next; 
	}
}

static char	**convert_cmd(t_list *lst_cmd)
{
	t_command	*cmd;
	char		**commands;
	int			*tab;
	int i;

	i = 0;
	commands = malloc(sizeof(char *) * (ft_lstsize(lst_cmd) + 1));
	if (!commands)
		return (0);
	tab = malloc(sizeof(int) * (ft_lstsize(lst_cmd) + 1));
	if (!tab)
		return (0);
	cmd = malloc(sizeof(t_command));
 	if (!cmd)
 		return (0);
	while (lst_cmd)
	{
		commands[i] = NULL;
		cmd = lst_cmd->content;
		while (lst_cmd && cmd->type == 0)
		{
			if (!commands[i])
				commands[i] = ft_strdup(cmd->text);
			else 
			{
				commands[i] = ft_strjoin(commands[i], " ");
				commands[i] = ft_strjoin(commands[i], cmd->text);
			}
			tab[i] = cmd->type;
			lst_cmd = lst_cmd->next;
			if (lst_cmd)
				cmd = lst_cmd->content;
		}
		if (commands[i])
		{
			i++;
			commands[i] = NULL;
		}
		while (lst_cmd && cmd->type == 1)
		{
			if (!commands[i])
				commands[i] = ft_strdup(cmd->text);
			else 
			{
				commands[i] = ft_strjoin(commands[i], " ");
				commands[i] = ft_strjoin(commands[i], cmd->text);
			}
			tab[i] = cmd->type;
			lst_cmd = lst_cmd->next;
			if (lst_cmd)
				cmd = lst_cmd->content;
		}
		i++;
	}
	commands[i] = NULL;
	i = 0;
	while (commands[i])
	{
		printf (_BOLD "\nCommand %d : %s\n" _END, i, commands[i]);
		printf ("Type = %s\n", ft_get_cmd_type(tab[i]));
		i++;
	}
	return (commands);
}

t_list	*parser(t_list *lst_token)
{
	t_token		*token;
	t_token		*tkn_last;
	t_command	*cmd;
	t_list		*lst_cmd;
	int			i;

	i = 0;
	tkn_last = NULL;
	lst_cmd = NULL;
	cmd = malloc(sizeof(t_command));
 	if (!cmd)
 		return (0);
	while (lst_token)
	{
		token = lst_token->content;	
		if (token->type == TOKEN_WORD && (tkn_last == NULL || \
		tkn_last->type == TOKEN_WORD))
		{
			cmd->inedx_cmd = i;
			cmd->text = token->text;
			cmd->type = CMD_WORD;
			lst_add_command(&lst_cmd, cmd);
			cmd = malloc(sizeof(t_command));
 			if (!cmd)
 				return (0);
		}
		else if ((token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT) || \
		(token->type == TOKEN_WORD && \
		(tkn_last->type == TOKEN_REDIRECT_IN || tkn_last->type == TOKEN_REDIRECT_OUT)))
		{
			cmd->inedx_cmd = i;
			cmd->text = token->text;
			cmd->type = CMD_REDIR;
			lst_add_command(&lst_cmd, cmd);
			cmd = malloc(sizeof(t_command));
 			if (!cmd)
 				return (0);
		}
		if (token != NULL)
			tkn_last = lst_token->content;
		lst_token = lst_token->next;
		i++;
	}
	convert_cmd(lst_cmd);
	return (lst_cmd);
}

// t_list	*parser(t_list *lst_token)
// {
// 	t_token	*token;
// 	// t_token	*token_next;
// 	t_command *command;
// 	t_bool	heredoc_before;
// 	t_bool	new_node;
// 	t_list	*lst_command;
// 	t_list	*head;
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	heredoc_before = false;
// 	new_node = false;
// 	lst_command = NULL;
// 	head = lst_command;
// 	command = NULL;
// 	command = malloc(sizeof(t_command));
// 	if (!command)
// 		return (0);
// 	command->word = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
// 	if (! command->word)
// 		return (0);
// 	command->redir = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
// 	if (! command->redir)
// 		return (0);

// 	t_command newcommand = lst_command->content;
// 	newcommand->word;
// 	// Gestion garbage collector 
// 	while (lst_token)
// 	{
// 		token = lst_token->content;
// 		// if (lst_token->next)
// 		//  	token_next = lst_token->next->content;
// 		if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || 
// 		(token->type == TOKEN_WORD && heredoc_before == true))
// 		{
// 			// printf("test\n");
// 			command->redir[j] = ft_strdup(token->text);
// 			if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT)
// 				heredoc_before = true;
// 			else
// 			{
// 				heredoc_before = false;
// 				lst_command = lst_add_command(&head, command);
// 				new_node = true;
// 			}
// 			//Ajouter ici tous les words en cours et la redir dans un maillon lst_cmd
// 			j++;
// 		}
// 		else if (token->type == TOKEN_WORD)
// 		{
// 			if (new_node == true)
// 			{
// 				printf("TESSSST\n");
// 				// lst_command = lst_command->next;
// 				command->word[i] = NULL;
// 				command->redir[j] = NULL; 
// 				command = malloc(sizeof(t_command));
// 				if (!command)
// 					return (0);
// 				command->word = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
// 				if (! command->word)
// 					return (0);
// 				command->redir = malloc(sizeof(char *) * (ft_lstsize(lst_token) + 1));
// 				if (! command->redir)
// 					return (0);
// 				i = 0;
// 				j = 0;
// 				new_node = false;
// 			}
// 			command->word[i] = ft_strdup(token->text);
// 			heredoc_before = false;
// 			i++;
// 		}
// 		if (lst_command == NULL)
// 		{
// 			printf("TEST2\n");
// 			lst_command = lst_add_command(&head, command); 
// 			// lst_command = lst_command->next; 
// 		}
// 		lst_token = lst_token->next;
// 	}
// 	printf("I = %d\n", i);
// 	printf("J = %d\n", j);

// 	command->word[i] = NULL;
// 	command->redir[j] = NULL;

// 	i = 0;
// 	j = 0;
// 	while (command->word[i])
// 		{
// 			printf (_BOLD "Word %d = %s\n"_END, i, command->word[i]);
// 			i++;
// 		}
// 	while (command->redir[j])
// 		{
// 			printf (_BOLD "Redir %d = %s\n"_END, j, command->redir[j]);
// 			j++;
// 		}
// 	return (head);
// }