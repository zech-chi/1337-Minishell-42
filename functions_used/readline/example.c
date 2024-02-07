#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void f()
{
	system("leaks a.out");
}

int main()
{
	char *line;

	atexit(f);
	while (1)
	{
		line = readline("🍪🍪🍪\033[0;32m>$ \033[0m");
		printf("%s", line);
		free(line);
	}
	return (0);
}
