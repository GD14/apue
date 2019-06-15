#include "rong.h"
#include <stdio.h>
#include <string.h>

int main()
{
	char line[MAXLINE];
	int n;
	int a, b;

	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		line[n] = 0;
		if (sscanf(line, "%d%d", &a, &b) == 2)
		{
			sprintf(line, "%d\n", a + b);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				err_sys("write error\n");
		}
		else
			err_sys("read error\n");
	}

	return 0;
}
