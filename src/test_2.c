#include <stdio.h>

int	main(void)
{
	int	fd;
	int	*fd_ptr;

	fd = 9;
	fd_ptr = &fd;
	printf("int is: %d\n", *fd_ptr);
	return (0);
}
