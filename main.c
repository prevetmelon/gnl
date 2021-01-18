#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *line;
	int fd = open("matrix", O_RDONLY);
	
	while (get_next_line(fd, &line) > 0)
	{
		printf("|%s|\n", line);
		free(line);
	}
	printf("|%s\n|", line);
	free(line);
	return (0);
}
