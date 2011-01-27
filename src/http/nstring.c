#include "nstring.h"

size_t ngets(int sock, const char *str, size_t len)
{
	char *buff;
	size_t res = 1, total = 0;
	for(buff = (char*)str; res > 0 && total < len; buff++) {
		res = recv(sock, buff, 1, NULL);
		if (res > 0 && *buff == '\n') {
			res = 0;
			*buff = '\0';
			if (buff > str && *(buff-1) == '\r') {
				*(--buff) = '\0';
				--total;
			}
		}
		total += res;
	}
	return total;
}

size_t nputs(int sock, const char *str, size_t len)
{
	char *crlf = "\r\n";
	size_t res = send(sock, str, len, NULL);
	if( res > 0) {
		res = send(sock, crlf, 2, NULL);
	}
	return res;
}
