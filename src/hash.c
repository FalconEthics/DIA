// hash.c: File hashing utilities for DIA.
// Provides functions to compute MD5 or SHA256 hashes for file contents.

#include "hash.h"
#include <stdio.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

extern int useSHA256; // Global flag for hash type

// Computes the hash of a file (MD5 or SHA256).
// filename: path to the file
// digest: output buffer (must be at least 32 bytes)
// useSHA256Flag: 1 for SHA256, 0 for MD5
// Returns 1 on success, 0 on failure.
int computeHash(const char *filename, unsigned char *digest, int useSHA256Flag) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;
    unsigned char buffer[4096];
    size_t bytesRead;
    if (useSHA256Flag) {
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
            SHA256_Update(&ctx, buffer, bytesRead);
        SHA256_Final(digest, &ctx);
    } else {
        MD5_CTX ctx;
        MD5_Init(&ctx);
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
            MD5_Update(&ctx, buffer, bytesRead);
        MD5_Final(digest, &ctx);
    }
    fclose(file);
    return 1;
}