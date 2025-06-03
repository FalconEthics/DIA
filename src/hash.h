#ifndef HASH_H
#define HASH_H

#include <openssl/md5.h>
#include <openssl/sha.h>

int computeHash(const char *filename, unsigned char *digest, int useSHA256);

#endif // HASH_H