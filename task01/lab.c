#include <stdlib.h>
#include <stdio.h>


int main() {
	printf("ID пользователя = %d", getuid());
	printf("\n");
	printf("ID группы = %d", getgid());
	printf("\n");
	return 0;
}

