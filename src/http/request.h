#ifndef __REQUEST_H
#define __REQUEST_H

#include <stddef.h>
#include <stdint.h>

#define HTTP_BUFSIZE 128

#define FL_REQSTART	0x00
#define FL_BODYPROC 	0x01
#define FL_HEADPROC 	0x02
#define FL_READBODY 	0x04

#define FL_GET		0x10
#define FL_POST		0x20
#define FL_HEAD		0x40
#define FL_PUT		0x80

#define METHOD(f) (f & 0xF0)

struct http_req {
	int socket;
	size_t body_size;
	char *url;
	char *header;
	char *body;
};

uint8_t http_read_request(struct http_req *rq);

#endif
