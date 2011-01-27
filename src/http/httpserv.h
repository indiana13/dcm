#ifndef __HTTPSERV_H
#define __HTTPSERV_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_QUEUE 10

struct httpd {
	int socket;
	short port;
	long ipaddr;
	short queue;
	struct sockaddr_in saddr;
	char* docroot;
};

int httpd_init(struct httpd *srv);

int httpd_start(struct httpd *srv);

int httpd_poll(struct httpd *srv);

int httpd_stop(struct httpd *srv);

#endif
