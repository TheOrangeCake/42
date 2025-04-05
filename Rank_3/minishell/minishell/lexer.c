/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/05 22:07:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	case_input(t_token *token)
{
	token->type = TK_In;
	token->str[0] = '<';
	token->str[1] = '\0';
	token->next = NULL;
}

void	case_pipe(t_token *token)
{
	token->type = TK_Pipe;
	token->str[0] = '|';
	token->str[1] = '\0';
	token->next = NULL;
}

void	case_usd(t_token *token)
{
	token->type = TK_USD;
	token->str[0] = '$';
	token->str[1] = '\0';
	token->next = NULL;
}

t_token	**case_single_char(t_token **head, char character)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = malloc(sizeof(char) * 2);
	if (token->str == NULL)
		return (free(token), NULL);
	if (character == '$')
		case_usd(token);
	else if (character == '|')
		case_pipe(token);
	else if (character == '<')
		case_input(token);
	ft_lstadd_back(head, token);
	return (head);
}

// tokenizer, note: "" and '' not removed to 
// take care of $ in string later, treat with ft_strtrim
t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			i++;
		if (line[i] != '\"' && line[i] != '\'')
		{
			if (line[i] == '$'
				|| (line[i] == '|' && (i == 0 || line[i - 1] != '|')
					&& line[i + 1] && line[i + 1] != '|')
				|| (line[i] == '<' && (i == 0 || line[i - 1] != '<')
					&& line[i + 1] && line[i + 1] != '<'))
			{
				if (case_single_char(&head, line[i]) == NULL)
					return (ft_lstclear(&head), NULL);
			}
			i++;
		}
		else
		{
			printf("test\n");
			i++;
		}
	}
	while (head != NULL)
	{
		printf("token: %s\n", head->str);
		head = head->next;
	}
	return (head);
}
