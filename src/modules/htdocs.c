#include "module.h"

static struct http_handlers handlers = {
	.get_proc = htdocs_get
};

static int htdocs_get(http_req *req)
{
	return 0;
}
