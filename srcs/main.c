#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main (void)
{
  long page_size = sysconf(_SC_PAGESIZE);
  printf("size = %ld", page_size);

  return 0;
}
