#ifndef MEMORY_H_
#define MEMORY_H_

extern void *memory_malloc(unsigned int size, char *file, unsigned int line);
extern void memory_free(void *buf, char *file, unsigned int line);

#define malloc(n) memory_malloc(n, __FILE__, __LINE__)
#define free(n) memory_free(n, __FILE__, __LINE__)

#endif // MEMORY_H_