/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japarbs <japarbs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 01:32:33 by japarbs           #+#    #+#             */
/*   Updated: 2019/05/30 17:10:35 by japarbs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	read_line(int fd, char **line)
{
	size_t			count;
	size_t			i;
	static size_t	line_index;
	char			buffer[BUF_SIZE];

	count = 0;
	i = 0;
	while (read(fd, buffer + 1, BUF_SIZE))
		++count;
	if (!count || !(line[line_index] = ft_strnew(count)))
		return (-1);
	while (count)
	{
		if (buffer[i] == '\n')
		{
			line[line_index][i] = '\0';
			return (0);
		}
		line[line_index][i] = buffer[i++];
		--count;
	}
	if (!count)
		return (0);
}

int get_next_line(const int fd, char **line)
{
	static size_t	line_index;
	if (fd <= 0 || !line)
		return (-1);

	return (int	read_line(int fd, char **line));
}

/*
**	Sudo Code
**	Start code defining indexes and strings. Read the file and run checks.
**	Returns are 1: Line read, 0: Finished Reading, -1: Error.
**	Reads one line then exits. Looping get_next_line will read multipule lines.
**	 
*/
