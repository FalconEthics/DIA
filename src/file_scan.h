#ifndef FILE_SCAN_H
#define FILE_SCAN_H

#include <sys/stat.h>
#include <ftw.h>

int processFile(const char *path, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
void scan_directory(const char *targetDir, int recursive);

#endif // FILE_SCAN_H