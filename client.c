#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "thread_pool.h"


void *read_call(void *arg) {
	printf("recv::%s\n", (char*)arg);
	return NULL;
}

int main() {
	struct thread_pool * pool = thread_pool_init(1, 10);

	struct client_base * cbase = tcp_client_init("127.0.0.1", 8888);

	if (cbase == NULL)
	{
		printf("%s\n", "err");
		return 0;
	}
	int fd = tcp_client_start(cbase, pool, NULL, read_call);
	while (1)
	{
		for (int i = 0; i < 100; ++i)
		{
			const char *buf  = "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddxxd";
			if (tcp_client_closed(cbase) <= 0)
			{
				tcp_send(fd, (void*)buf, strlen(buf) + 1);
			}

			// sleep(1);
		}
		sleep(3);
	}

	sleep(10);
	return 0;
}