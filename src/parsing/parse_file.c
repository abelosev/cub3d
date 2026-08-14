#include "parsing.h"

static int	has_cub_extension(char *filename)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(CUB_EXT);
	if (len <= ext_len)
		return (0);
	return (ft_strncmp(filename + (len - ext_len), CUB_EXT, ext_len) == 0);
}

int	open_cub_file(char *filename, t_cub *cub)
{
	int	fd;

	if (!has_cub_extension(filename))
		parse_error(cub, "the scene file must have a .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error(cub, strerror(errno));
	return (fd);
}

static void	free_line_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}

/*
** Читает весь файл в связный список malloc'нутых строк (по одной на
** строку, '\n' обрезан). Список — просто растущий контейнер, сразу
** конвертируется в обычный массив.
*/
t_list	*read_lines(int fd, t_cub *cub)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			free_line_list(lst);
			close(fd);
			parse_error(cub, "malloc failure while reading the file");
		}
		ft_lstadd_back(&lst, node);
		line = get_next_line(fd);
	}
	return (lst);
}

void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/*
** Переносит содержимое t_list в обычный char** (NULL-terminated),
** затем освобождает узлы списка (не их content — владение
** передаётся массиву).
*/
char	**list_to_array(t_list *lst)
{
	char	**arr;
	t_list	*tmp;
	int		n;
	int		i;

	n = ft_lstsize(lst);
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
	{
		free_line_list(lst);
		return (NULL);
	}
	i = 0;
	while (lst)
	{
		arr[i++] = (char *)lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Идёт по массиву строк: пустые строки и распознанные config-
** идентификаторы (NO/SO/WE/EA/F/C) поглощаются и освобождаются по
** одной. Первая строка, которая не пустая и не подошла ни под один
** идентификатор, считается началом карты: с неё (включительно) и до
** конца всё передаётся в cub->map как есть.
*/
void	split_config_and_map(t_cub *cub, char **lines)
{
	int	total;
	int	i;
	int	map_count;
	int	j;

	cub->raw_lines = lines;
	total = 0;
	while (lines[total])
		total++;
	cub->raw_lines_total = total;
	i = 0;
	while (i < total)
	{
		if (is_blank_line(lines[i]))
			free(lines[i]);
		else if (try_parse_config(cub, lines[i]))
			free(lines[i]);
		else
			break ;
		lines[i] = NULL;
		i++;
	}
	if (i == total)
		parse_error(cub, "scene file is missing a map");
	map_count = total - i;
	cub->map = malloc(sizeof(char *) * (map_count + 1));
	if (!cub->map)
		parse_error(cub, "malloc failure while building the map");
	j = 0;
	while (j < map_count)
	{
		cub->map[j] = lines[i + j];
		j++;
	}
	cub->map[j] = NULL;
	cub->map_h = map_count;
	j = 0;
	while (j < map_count)
	{
		if (is_blank_line(cub->map[j]))
			parse_error(cub, "empty line found inside the map block");
		j++;
	}
	free(lines);
	cub->raw_lines = NULL;
	cub->raw_lines_total = 0;
}

int	parse_cub(char *filename, t_cub *cub)
{
	int		fd;
	t_list	*lst;
	char	**lines;

	init_cub(cub);
	fd = open_cub_file(filename, cub);
	lst = read_lines(fd, cub);
	close(fd);
	lines = list_to_array(lst);
	if (!lines)
		parse_error(cub, "malloc failure while reading the file");
	split_config_and_map(cub, lines);
	check_config_complete(cub);
	validate_map_chars(cub);
	find_player(cub);
	check_map_closed(cub);
	return (0);
}
