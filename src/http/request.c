#include <stdlib.h>
#include <string.h>

#include "nstring.h"
#include "headers.h"
#include "request.h"

uint8_t http_get_method(struct http_req *rq)
{
	uint8_t res = FL_REQSTART;
	char *met = index(rq->header, ' ');
	size_t size = met - rq->header;
	if (size == 3) {
		if (strncasecmp(rq->header, HDR_METHOD_GET, size) == 0)
			res |= FL_GET;
		else if (strncasecmp(rq->header, HDR_METHOD_PUT, size) == 0)
			res |= FL_PUT;
	} else if (size == 4) {
		if (strncasecmp(rq->header, HDR_METHOD_POST, size) == 0)
			res |= FL_POST;
		else if (strncasecmp(rq->header, HDR_METHOD_HEAD, size) == 0)
			res |= FL_HEAD;
	}
	char *url = index(++met, ' ');
	size = url - met;
	rq->url = (char *)calloc(size + 1, sizeof(char));
	memcpy(rq->url, met, size);
	return res;
}

uint8_t http_get_header(struct http_req *rq) 
{
	char *colon = index(rq->header, ':');
	size_t name_size = colon - rq->header;
	if (strncasecmp(rq->header, HDR_CONTENT_LEN, name_size) == 0) {
		rq->body_size = atoi(++colon);
		if (rq->body_size > 0)
			return FL_READBODY;
	}
	return FL_REQSTART;
}

uint8_t http_get_body(struct http_req *rq) 
{
	uint8_t res = FL_BODYPROC;
	rq->body = (char *)calloc(rq->body_size + 1, sizeof(char));
	size_t size = recv(rq->socket, rq->body, rq->body_size, NULL);
	if(size > 0)
		rq->body_size = size;
	return res;
}

uint8_t http_read_request(struct http_req *rq)
{
	size_t size = 0;
	char buffer[HTTP_BUFSIZE + 1];
	rq->header = buffer;
	uint8_t flags = FL_REQSTART;
	uint8_t (*handler)(struct http_req *) = http_get_method;
	while(!(flags & (FL_HEADPROC | FL_BODYPROC))) {
		size = ngets(rq->socket, (const char *)buffer, HTTP_BUFSIZE);
		if(size == 0) {
			flags |= FL_HEADPROC;
			if (flags & FL_READBODY)
				handler = http_get_body;
			else
				flags |= FL_BODYPROC;
		} else if(METHOD(flags) && !(flags & FL_HEADPROC))
			handler = http_get_header;
		flags |= handler(rq);
	}
	rq->header = NULL;
	return flags;
}

