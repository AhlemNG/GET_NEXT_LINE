/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:06:33 by anouri            #+#    #+#             */
/*   Updated: 2023/01/22 13:08:29 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_found_line(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read(char *stock, int fd)
{
	long int	status;
	char		*buff;
	char		*temp;

	status = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (status > 0 && ft_found_line(stock) == 0)
	{
		status = read (fd, buff, BUFFER_SIZE);
		if (status == -1)
		{
			free(stock);
			free(buff);
			return (NULL);
		}
		buff[status] = '\0';
		temp = stock;
		stock = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (stock);
}

static char	*ft_get_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_update_stock(char *str, char *line)
{
	size_t	p;
	char	*new_str;
	size_t	size;
	size_t	line_len;

	if (!str)
		return (NULL);
	line_len = ft_strlen(line);
	size = ft_strlen(str) - ft_strlen(line);
	new_str = malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	p = 0;
	while (p < size)
	{
		new_str[p] = str[line_len + p];
		p++;
	}
	new_str[p] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	stock = ft_read(stock, fd);
	if (!stock)
	{
		free(stock);
		return (NULL);
	}
	line = ft_get_line(stock);
	stock = ft_update_stock(stock, line);
	if (!line)
	{
		free(stock);
		stock = (NULL);
	}
	return (line);
}

/*int main()
{
     int fd;
     fd = open("a_lire.txt", O_RDONLY);
     char    *line;

    while (line = get_next_line(fd))
    {
     printf("%s", line);
     free(line);
    }
    close(fd);
}
*/
