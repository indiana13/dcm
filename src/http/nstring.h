#ifndef __NSTRING_H
#define __NSTRING_H

#include <stddef.h>

size_t ngets(int sock, const char *str, size_t len);

size_t nputs(int sock, const char *str, size_t len);

#endif
