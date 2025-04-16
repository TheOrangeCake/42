/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:07 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/16 14:49:32 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"


enum	e_node_t
{
	NT_Candidate = 0,
	NT_Cmd = 1,
	NT_Expand = TK_USD,
	NT_Assign = TK_Assign,
	NT_RdrOut = TK_Out,
	NT_RdrAppn = TK_Append,
	NT_RdrIn = TK_In,
	NT_HereDoc = TK_HereDoc,
	NT_Pipe = TK_Pipe,
	NT_And = TK_And,
	NT_Or = TK_Or,
};

typedef struct s_args
{
	char	**argv;
	int		argc;
}	t_args;

union u_data
{
	t_args	*args;
	char	*field;
	t_token	*token;
};

typedef struct s_node
{
	int				type;
	struct s_node	*lnode;
	struct s_node	*rnode;
	union u_data	data;
}	t_node;

int	main(int ac, char **av, char **envp)
{
	char	**test[4]
}