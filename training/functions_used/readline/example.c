#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
	char *line;

	while (1)
	{
		line = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
