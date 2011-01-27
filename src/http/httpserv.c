#include <string.h>

#include "httpserv.h"

int httpd_init(struct httpd *srv)
{
	int val = 1;
	memset(srv, 0x00, sizeof(*srv));
	srv->saddr.sin_family = AF_INET;
	srv->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (srv->socket <= 0)
		return -1;
	if (setsockopt(srv->socket, SOL_SOCKET, 
			SO_REUSEADDR, &val, sizeof(val)) < 0)
		return -2;
	srv->ipaddr = INADDR_ANY;
	srv->queue = TCP_QUEUE;
	srv->port = 8080; 
	return 0;
}

int httpd_start(struct httpd *srv)
{
	srv->saddr.sin_addr.s_addr = htonl(srv->ipaddr);
	srv->saddr.sin_port = htons(srv->port);
	if (bind(srv->socket, (struct sockaddr *)&srv->saddr, sizeof(srv->saddr)) < 0)
		return -3;
	if (listen(srv->socket, srv->queue) < 0)
		return -4;
	return 0;
}

int httpd_poll(struct httpd *srv)
{
	return accept(srv->socket, NULL, NULL);
}

int httpd_stop(struct httpd *srv)
{
	return close(srv->socket);
}

