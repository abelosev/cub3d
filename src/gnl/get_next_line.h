/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 10:55:39 by vfekete           #+#    #+#             */
/*   Updated: 2026/01/18 17:34:50 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_rd
{
	char	*buf;
	int		size;
	int		capacity;
	int		rd_index;
	int		start_index;
	int		nl_index;
}			t_rd;

char		*get_next_line(int fd);

// UTILS
t_rd		*init_rd(void);
t_rd		*resize_rd_buf(t_rd *rd);

#endif