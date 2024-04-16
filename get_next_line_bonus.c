/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmastroc <gmastroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:26:05 by gmastroc          #+#    #+#             */
/*   Updated: 2024/03/22 19:09:09 by gmastroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_leftover_file(char *selection, char	*line)
{
	size_t	i;
	size_t	j;
	size_t	snippet;

	i = 0;
	j = 0;
	while (selection[i] && selection[i] != '\n')
		i++;
	if (!selection[i])
	{
		free(selection);
		return (NULL);
	}
	snippet = ft_strlen(selection) - i;
	line = ft_calloc (snippet + 1, sizeof(char));
	i++;
	while (selection[i])
		line[j++] = selection[i++];
	free (selection);
	return (line);
}

char	*ft_defined_line(char *selection)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!selection[i])
		return (NULL);
	while (selection[i] && selection[i] != '\n')
		i++;
	line = ft_calloc (i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (selection[i] && selection[i] != '\n')
		line[j++] = selection[i++];
	if (selection[i] == '\n')
		line[j] = '\n';
	return (line);
}

char	*ft_read(int fd, char *selection)
{
	ssize_t	bytes_read;
	char	*read_sel;

	if (!selection)
		selection = ft_calloc(1, sizeof(char));
	read_sel = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(selection, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_sel, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (read_sel);
			free (selection);
			return (NULL);
		}
		read_sel[bytes_read] = '\0';
		selection = ft_strjoin(selection, read_sel);
	}
	free (read_sel);
	return (selection);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*page[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	page[fd] = ft_read(fd, page[fd]);
	if (!page[fd])
		return (NULL);
	line = ft_defined_line(page[fd]);
	page[fd] = ft_leftover_file(page[fd], line);
	return (line);
}
/* 
int	main(int argc, char **argv)
{
	char *line;

	int fd1 = open(argv[1], O_RDONLY);
	//int fd2 = open(argv[2], O_RDONLY);
	//int fd3 = open(argv[3], O_RDONLY);	
	//for (size_t i = 0; i < 10; i++)
	size_t i = 0;

	while (i < 3)
	{
		char *tmp = get_next_line(fd1);
		printf("L1:%s", tmp);
		free(tmp);
		//printf("L2:%s", get_next_line(fd2));
		//printf("L3:%s", get_next_line(fd3));
		i++;
	}
	return 0;
}  */

/* int main()
{
	int fd = open("./sdf/giant_line_nl (copy).txt", O_RDONLY);
	int fd2 = open("./sdf/1.txt", O_RDONLY);
	char *str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("primo is %s", str);
		free(str);
		str = get_next_line(fd2);
		printf("next is %s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return(0);
} */