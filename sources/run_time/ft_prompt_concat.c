/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_concat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiqueir <rsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:12:41 by wrosendo          #+#    #+#             */
/*   Updated: 2022/03/10 17:29:18 by rsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_minishell.h"

// não sei se realmente é necessario.
// lembram do caso root (sudo su)
/* Retorna o path retirando /home/nome_do_user */
char	*ft_find_path(char *abs_path)
{
	char *pointer;

	pointer = abs_path + 1;
	pointer = ft_strchr(pointer, '/');
	pointer++;
	pointer = ft_strchr(pointer, '/');
	return (pointer);
}

/* preenche a struct prompt com as variáveis de ambiente user, hostname e
path absoluto */
void	ft_fill_prompt(t_prompt *prompt)
{
	prompt->user = getenv("USER");
	prompt->hostname = getenv("NAME");
	prompt->path = getenv("PWD");
}

int	concat_and_clean(t_prompt *prompt, char *path)
{
	int		a;
	int		b;
	char	*pointer;

	a = ft_strlen(prompt->user);
	b = ft_strlen(prompt->hostname);
	pointer = malloc(a + b + ft_strlen(path) + 4);
	if (!(pointer))
		exit(1);
	ft_strlcpy(pointer, prompt->user, a + 1);
	pointer[a++] = '@';
	ft_strlcpy(&pointer[a], prompt->hostname, b + 1);
	a+=b;
	pointer[a++] = ':';
	pointer[a++] = '~';
	b = ft_strlen(path);
	ft_strlcpy(&pointer[a], path, b + 1);
	a+=b;
	pointer[a] = '\0';
	prompt->result = pointer;
	return (0);
}

void color_string(t_prompt *prompt)
{
	char **strings;
	char *str1;
	char *str2;
	char *tmp;

	
	strings = ft_split(prompt->result, ':');
	str1 = ft_strjoin(GREEN, strings[0]);
	str2 = ft_strjoin(BLUE, strings[1]);
	tmp = str1;
	str1 = ft_strjoin(str1, "\e[37;1m:");
	free(tmp);
	tmp = str1;
	str1 = ft_strjoin(str1, str2);
	free(tmp);
	tmp = str1;
	str1 = ft_strjoin(str1, "\e[0m$ ");
	free(tmp);
	free(prompt->result);
	free(strings[0]);
	free(strings[1]);
	free(strings);
	free(str2);
	prompt->result=str1;
}

/* Gera a linha do prompt de comando formatada */
void	ft_prompt_concat(t_prompt *prompt)
{
	char	*right_path;

	ft_fill_prompt(prompt);
	right_path = ft_find_path(prompt->path);
	concat_and_clean(prompt, right_path);
	color_string(prompt);
}
