/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:18:40 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/14 22:27:46 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Process_line takes the fd's fdarr char string and finds the index of \n.
**	this index is stored in lenres (length result) 
**	Using that len as how long the line is and pushing all till \n to **line.
**	after **line is done, the leftover chars are stored in fdarr[fd]
**	to be used in the next recall of get_next_line.
**	statsize (static size) is the messured size of the extra bytes.
**	bres is imported from get_next_line for the EOF check as stated bellow. 
*/

int		process_line(int fd, char **line, char **fdarr, int bres)
{
	size_t			lenres;
	size_t			statsize;
	char			*tmp;

	if (!bres && !fdarr[fd][0])
	{
		ft_strdel(&fdarr[fd]);
		return (0);
	}
	lenres = ft_strdlen(fdarr[fd], '\n');
	if (!(*line = ft_strsub(fdarr[fd], 0, lenres)))
		return (-1);
	statsize = ft_strlen(ft_strchr(fdarr[fd], '\n')) - 1;
	if (!(tmp = ft_strsub(fdarr[fd], lenres + 1, statsize)))
		return (-1);
	ft_strdel(&fdarr[fd]);
	if (!(fdarr[fd] = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	return (1);
}

/*
**	Runs return checks and keeps track of FDs and handles return values.
**	fdarr is an hash index, the pointer is a holder of the current read string
**	that will later be pushed to **line, this allows the function to handle
**	mutiple FDs at once. fdarr also is used as storage between lines
**	after each recall, saving the unused chars for the next string in **line.
**	OPEN_MAX (from limits.h) is the total ammount of FDs next_line can handle.
**	...
**	Function Logic
**	Reads line from FD and joins the current buff and remaining bytes,
**	allocating the chars as it reads, allowing for dynamic string len.
**	bres (buffer result) is used to create a NULL terminator in buffer.
**	bres is also used as an EOF indicator, if bres = 0 then EOF is true.
**	*tmp string is nessesary to free &fdarr[fd] to assure there are no leaks.
**	if a \n is found the while loop breaks and enters phase 2 process_line.
*/

int		get_next_line(const int fd, char **line)
{
	static char		*fdarr[OPEN_MAX];
	int				bres;
	char		 	buffer[BUFF_SIZE + 1];
	char			*tmp;

	if (!fd || fd <= -1 || fd > OPEN_MAX || !line)
		return (-1);
	if (!(fdarr[fd]))
		fdarr[fd] = ft_strnew(0);
	while ((bres = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bres] = '\0';
		if (!(tmp = ft_strjoin(fdarr[fd], buffer)))
			return (-1);
		ft_strdel(&fdarr[fd]);
		if (!(fdarr[fd] = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return(process_line(fd, line, fdarr, bres));
}
