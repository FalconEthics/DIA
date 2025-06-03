// hash.h: Header for file hashing utilities in DIA.
// Declares the interface for computing file hashes (MD5 or SHA256).

#ifndef HASH_H
#define HASH_H

#include <openssl/md5.h>
#include <openssl/sha.h>

// Computes the hash of a file (MD5 or SHA256).
// filename: path to the file
// digest: output buffer (at least 32 bytes)
// useSHA256: 1 for SHA256, 0 for MD5
int computeHash(const char *filename, unsigned char *digest, int useSHA256);

#endif // HASH_H