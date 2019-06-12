/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:18:40 by japarbs           #+#    #+#             */
/*   Updated: 2019/06/12 01:58:47 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Reads line from FD and joins the current buff and current index of **line,
**	allocating the chars as it reads, allowing for dynamic string len.
**	bres (buffer result) is used to create a NULL terminator in buffer.
**	bres is also used as an EOF indicator, if bres = 0 then EOF is true.
**	lenres (length result) is used as an \n check and is used for the
**	length limit in ft_strsub to push to current string of **line.
*/

int		read_line(int fd, char **line, char **fdarr, int bres)
{
	size_t			lenres;
	size_t			statsize;
	char			*tmp;

	if (!bres && !fdarr[fd])
	{
		free(fdarr[fd]);
		fdarr[fd] = NULL;
		return (1);
	}
	lenres = ft_strdlen(fdarr[fd], '\n');
	if (!(*line = ft_strsub(fdarr[fd], 0, lenres)))
		return (-1);
	statsize = ft_strlen(ft_strchr(fdarr[fd], '\n'));
	if (!(tmp = ft_strsub(fdarr[fd], lenres + 1, statsize)))
		return (-1);
	free(fdarr[fd]);
	if (!(fdarr[fd] = ft_strdup(tmp)))
		return (-1);
	free(tmp);
	return (0);
}

/*
**	Runs return checks and keeps track of FDs and handles return values.
**	fdarr is an array of pointers, FD is used as an index and the pointer
**	is a holder of the current read string that will later be pushed to **line,
**	this allows the function to handle mutiple FDs at once. fdarr also is used
**	as storage between lines after each recall, saving the unused chars for the
**	next **line 
**	MAX_FD is the total ammount of FDs get_next_line can handle (defined in .h)
*/

int		get_next_line(const int fd, char **line)
{
	static char		*fdarr[MAX_FD];
	int				bres;
	char			buffer[BUFF_SIZE + 1];
	char			*tmp;

	if (!(fdarr[fd]))
		fdarr[fd] = ft_strnew(0);
	if (fd == -1 || !line)
		return (-1);
	while ((bres = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bres] = '\0';
		if (!(tmp = ft_strjoin(fdarr[fd], buffer)))
			return (-1);
		free(fdarr[fd]);
		if (!(fdarr[fd] = ft_strdup(tmp)))
			return (-1);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return(read_line(fd, line, fdarr, bres));
}
