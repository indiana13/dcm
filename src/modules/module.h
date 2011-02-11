#ifndef __MODULE_H__
#define __MODULE_H__

#include <http/request.h>

struct http_handlers {
	(int *get_proc)(struct http_req *);
	(int *post_proc)(struct http_req *);
	(int *head_proc)(struct http_req *);
	(int *put_proc)(struct http_req *);
};

#endif
