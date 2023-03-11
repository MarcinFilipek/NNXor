#include <stdio.h>
#include <malloc.h>

void *memory_malloc(unsigned int size, char *file, unsigned int line)
{
    printf("File: %s, line: %d: malloc %dbytes\n", file, line, size);
    return malloc(size);
}

void memory_free(void *buf, char *file, unsigned int line)
{
    printf("File: %s, line: %d: free %p \n", file, line, buf);
    free(buf);
    buf = NULL;
}