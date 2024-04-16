/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_commentato.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmastroc <gmastroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:01:01 by gmastroc          #+#    #+#             */
/*   Updated: 2024/03/15 16:54:52 by gmastroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* 				  		WHAT SHOULD MY FUNCTION DO							  */
/* 
	- OPEN/READ my file (.txt) and read the first line (until \n or EOF)
	by buffer size. - I do this in the main
	- String up to \n to be copied and calloc'd in a new string(LINE).
	Return the line.
	- Remainder after \n to be saved in TEMP.
	- TEMP_LEFTOVER to be then joined to the new line read by buffer.
	the approach becomes a mess in case of a very big buffer.
*/

#include "get_next_line.h"
//clearing the page from the line already read/allocated
char	*ft_leftover_file(char *selection, char *line)
{
	size_t	i;
	size_t	j;
	size_t	period;//the sentence i already dealt with

	i = 0;
	j = 0;
	while (selection[i] && selection[i] != '\n')
		i++;//i keep running through the string until |n
	if (!selection[i])
	{
		free(selection);
		return (NULL);
	}
	period = ft_strlen(selection) - i;//result of length of sel - snippet until \n
	line = ft_calloc(period + 1, sizeof(char));
	i++;//salto \n(already inserted in the other funct.), move to following char
	while (selection[i])
		line[j++] = selection[i++];
	free(selection);
	return(line);
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
	line = ft_calloc(i + 2, sizeof(char));
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

char	*ft_read(int fd, char *selection)// i need to return "selection" after it's been updated
{
	ssize_t	bytes_read;
	char	*temp_sel;//i'll store my selection here
	char	*read_sel;//will create mem space for buffer by its size

	if (!selection)
		selection = ft_calloc(1, sizeof(char));//write a nice 0 if it aint got shit
	temp_sel = selection;
	read_sel = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_sel)
		return (NULL);
	bytes_read = 1; //why was this - FOR OBVIOUS BELOW REASONS DUH
	while (!ft_strchr(selection, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_sel, BUFFER_SIZE);
				/* if(bytes_read < BUFFER_SIZE)
		{ */
			/**
			 * quando sei qui dentro sei arrivata all ultimo giro di gnl
			 * e hai letto meno caratteri di BUFFER_SIZE
			 * 
			 * te allochi es. 20 caratteri ma all ultimo giro ne leggi di meno
			 * 
			 * devi fare uno strjoin/copiarti la stringa dentro la statica/o quello che devi ritornare
			 * pero di bytes_read caratteri
			 * 
			 * una volta joinata puoi ritornarla
			 * 
			*/
		}
		if (bytes_read == -1)//if error free all
		{
			free (temp_sel);
			free (read_sel);
			return (NULL);
		}
		temp_sel = selection;
		selection = ft_strjoin(temp_sel, read_sel);
		free (temp_sel);
	}
	free (read_sel);
	return (selection);
}

char	*get_next_line(int fd)
{
	//array[1024]: bonus ver, allows for more fds to be taken until max num
	char		*line;
	static char	*page[1024];//il mio buffer
	//is fd valid?
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//line that was read/selected, store it in "main container" PAGE
	page[fd] = ft_read(fd, page[fd]);
	if (!page[fd])
		return (NULL);
	line = ft_defined_line(page[fd]);//qui ho calcolato la linea di ritorno
	page[fd] = ft_leftover_file(page[fd], line);//i copy whats left of file after sending out 1 line
	return (line);
}
int main(int argc, char **argv)
{
	char	*line;
	//int	fd = open("ita1.txt", O_RDONLY);
	int 	fd = open(argv[1], O_RDONLY); //to open spec file from term

	//while ((line = get_next_line(0)) != NULL) --- write in terminal
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}

	return (0);
}