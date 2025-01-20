/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 03:48:53 by nopareti          #+#    #+#             */
/*   Updated: 2025/01/20 14:15:35 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redirection
{
	char			*file;
	int				type;
	int				fd;
}					t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redirections;
	int				nb_redirections;
	int				pipe_presence;
}					t_cmd;

typedef struct s_cmd_line
{
	t_cmd			*cmds;
	int				nb_cmds;
}					t_cmd_line;

typedef struct s_shell
{
	t_env			*env;
}					t_shell;

typedef struct s_quote_state
{
	int				in_single_quote;
	int				in_double_quote;
	int				i;
	int				j;
}					t_quote_state;

typedef struct s_env_parse_state
{
	int				i;
	int				j;
	int				k;
	int				in_single_quote;
	char			*var_name;
	char			*var_value;
	char			*new_arg;
}					t_env_parse_state;

typedef struct s_split_state
{
	int				in_single_quote;
	int				in_double_quote;
	char			*token_start;
	int				count;
}					t_split_state;
