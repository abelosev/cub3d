/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:17:58 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/12 18:08:17 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(char const *s, char c)
{
	unsigned int	words;
	unsigned int	in_word;

	words = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			words++;
		}
		if (in_word && *s == c)
			in_word = 0;
		s++;
	}
	return (words);
}

static void	*free_all(char **split_out, unsigned int word_count)
{
	unsigned int	counter;

	counter = 0;
	while (counter < word_count + 1)
	{
		if (split_out[counter] != NULL)
			free(split_out[counter]);
		counter++;
	}
	free(split_out);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	w_c;
	unsigned int	words;
	unsigned int	i;

	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	w_c = 0;
	while (*s)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != *s)
			result[w_c++] = ft_substr(s, 0, i);
		if (w_c != 0 && result[w_c - 1] == NULL)
			return (free_all(result, words));
		s += i;
	}
	result[w_c] = NULL;
	return (result);
}

/* #include <stdio.h>
int	main(int ac, char **av)
{
	char **res = ft_split(av[1], av[2][0]);
	for (int i = 0; i < 5; i++)
		printf("%s\n", res[i]);
} */