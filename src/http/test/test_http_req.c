#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "httpserv.h"
#include "request.h"

char *reply = "HTTP/1.1 200 OK/r/n/r/n";

int main(int argc, char **argv)
{
	int ret = 0;
	struct httpd srv;
	struct http_req rq;
	
	ret = httpd_init(&srv);
	if(ret < 0) {
		printf("HTTPD init failure: %i\n", ret);
		return -1;
	}
	
	ret = httpd_start(&srv);
	if(ret < 0) {
		printf("HTTPD startup failure: %i\n", ret);
		return -1;
	}
	
	for(;;) {
		memset(&rq, 0x00, sizeof(rq));
		rq.socket = httpd_poll(&srv);
		if (rq.socket < 0) {
			perror(NULL);
		}
		uint8_t flags = http_read_request(&rq);
		printf("-------- HTTP REQUEST --------\n", flags);
		switch(METHOD(flags)) {
			case FL_GET: printf("METHOD: GET\n"); break;
			case FL_HEAD: printf("METHOD: HEAD\n"); break;
			case FL_POST: printf("METHOD: POST\n"); break;
			case FL_PUT: printf("METHOD: PUT\n"); break;
			default: printf("METHOD: <unknown>\n"); break;
		}
		printf("URL: %s\n", rq.url);
		printf("BODY: %s (size: %li)\n\n", rq.body, rq.body_size);
		write(rq.socket, reply, strlen(reply));
		close(rq.socket);
	}
	
	httpd_stop(&srv);
	return 0;
}

