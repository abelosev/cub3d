/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:10:19 by anbelose          #+#    #+#             */
/*   Updated: 2025/04/29 19:10:34 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb);
}

static char	*word_fill(const char **s, char c)
{
	char	*word;
	int		w_len;
	int		i;

	w_len = 0;
	while ((*s)[w_len] && (*s)[w_len] != c)
		w_len++;
	word = (char *)malloc(sizeof(char) * (w_len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < w_len)
	{
		word[i] = **s;
		(*s)++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		nb;
	int		i;

	if (!s)
		return (NULL);
	nb = word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s && i < nb)
	{
		while (*s == c)
			s++;
		res[i] = word_fill(&s, c);
		if (!res[i])
		{
			free_tab(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
