/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:38:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 18:03:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (perror("Error"), NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if ((*s1 || *s2) && n > 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void	case_exit_code(void)
{
	printf("repalce this with exit code\n");
}

// find the value of the variable, return an empty string if no match
char	*find_variable(char *s, t_env **env)
{
	t_env	*temp;
	char	*line;

	temp = *env;
	line = ft_strdup("\0");
	if (line == NULL)
		return (perror("Error"), NULL);
	while (temp != NULL)
	{
		if (!ft_strncmp(s, temp->key, ft_strlen(s)))
		{
			free(line);
			line = ft_strdup(temp->value);
			if (line == NULL)
				return (perror("Error"), NULL);
			return (line);
		}
		temp = temp->next;
	}
	return (line);
}

char	*ft_strjoin_variable(char *s1, char *s2, int i)
{
	char	*line;
	int		j;

	line = malloc(sizeof(char) * (i + ft_strlen(s2)) + 1);
	if (line == NULL)
		return (perror("Error"), NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		line[j] = s2[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (line);
}

char	*case_expand(char *s, int i, t_env **env)
{
	int		count;
	char	*temp;
	char	*value;

	count = i;//s[count] is position of $
	i++;
	while (ft_isalnum(s[i]))
		i++;
	i--;//loop till the end of variable
	temp = ft_substring(&(s[count + 1]), i - count);// find the key
	if (temp == NULL)
		return (NULL);
	value = find_variable(temp, env);// find the value of the variable
	free(temp);
	if (value == NULL)
		return (NULL);
	temp = ft_strjoin_variable(s, value, count);
	free(value);
	if (temp == NULL)
		return (NULL);
	value = ft_strjoin(temp, &(s[i + 1]));
	free(temp);
	if (value == NULL)
		return (NULL);
	return (value);
}

char	*dollar_handler(char *s, t_env **env)
{
	char	*expand;
	char	*final;
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
		}
		else if (s[i] == '$' && s[i + 1] != '\0')
		{
			if (s[i + 1] == '?')
				case_exit_code();
			else if (ft_isalphabet(s[i + 1]) || s[i + 1] == '_')
			{
				expand = case_expand(s, i, env);
				if (expand == NULL)
					return (NULL);
				final = dollar_handler(expand, env);
				free(expand);
				return (final);
			}
		}
		i++;
	}
	return (ft_strdup(s));
}
