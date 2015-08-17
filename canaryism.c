#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
    uint8_t *mem;
    ElfW(Ehdr) *ehdr;
    ElfW(Phdr) *phdr;
    ElfW(Shdr) *shdr;
    int fd, dynamic = 0, i;

    if (argc < 2) {
        printf("Usage: %s <binary>\n", argv[0]);
        exit(0);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }
    fstat(fd, &st);
    mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    for (dynamic = 0, i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == PT_DYNAMIC) {
            dynamic++;
            break;
        }
    }
    stackchk_addr = dynamic ? 
    get_plt_address("__stack_chk_fail", mem) : 
    resolve_sym("__stack_chk_fail", mem);
    
        
    
    
}


