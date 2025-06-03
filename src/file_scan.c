// file_scan.c: Directory traversal and file registration for DIA.
// Responsible for walking the directory tree, hashing files, and building the file list.

#include "file_scan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>
#include "hash.h"

#define MAX_PATH 1024
#define MAX_FILES 100000

// Externs for shared state (defined in main.c)
typedef struct FileEntry {
    char *path;                // Full path to the file
    off_t size;                // File size in bytes
    unsigned char hash[32];    // File hash (MD5 or SHA256)
} FileEntry;
extern FileEntry *fileList;
extern int fileCount;
extern int useSHA256;
extern int dryRun;
extern int interactive;
extern FILE *logFile;

// Forward declarations for logging and prompt
// (actual implementations in other modules)
typedef int (*PromptFunc)(const char *);
extern int prompt_user(const char *filename);
extern void log_msg(FILE *logFile, const char *fmt, ...);

// Callback for nftw() - processes each file found
int processFile(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag != FTW_F) return 0; // Only process regular files
    // Check for duplicates by size and hash
    for (int i = 0; i < fileCount; i++) {
        if (fileList[i].size != sb->st_size) continue;
        unsigned char hash[32];
        if (!computeHash(path, hash, useSHA256)) return 0;
        int hashLen = useSHA256 ? 32 : 16;
        if (memcmp(fileList[i].hash, hash, hashLen) == 0) {
            // Duplicate found
            printf("⚠️  Duplicate: %s\n", path);
            log_msg(logFile, "Duplicate: %s\n", path);
            if (!dryRun) {
                if (interactive && !prompt_user(path)) {
                    printf("🚫 Skipped: %s\n", path);
                    return 0;
                }
                if (remove(path) == 0) {
                    printf("🗑️  Deleted: %s\n", path);
                    log_msg(logFile, "Deleted: %s\n", path);
                } else {
                    perror("❌ Error deleting");
                }
            }
            return 0;
        }
    }
    // Register new file in the list
    if (fileCount >= MAX_FILES) {
        fprintf(stderr, "🚨 Too many files. Increase MAX_FILES.\n");
        exit(1);
    }
    FileEntry *entry = &fileList[fileCount++];
    entry->path = strdup(path);
    entry->size = sb->st_size;
    computeHash(path, entry->hash, useSHA256);
    return 0;
}

// Kicks off the directory scan using nftw()
void scan_directory(const char *targetDir, int recursive) {
    int flags = FTW_PHYS;
    // If not recursive, only scan the top-level directory
    nftw(targetDir, processFile, 10, flags | (recursive ? 0 : FTW_DEPTH));
}