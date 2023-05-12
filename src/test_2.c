#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int fd = 9;
	int *fd_ptr = &fd;

	printf("int is: %d\n", *fd_ptr);
	return (0);
}
