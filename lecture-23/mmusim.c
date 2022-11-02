#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096

#define LEVELS 3
#define PTE_VALID (1 << 0)

static uint64_t* root_page_table = NULL;

static uint64_t* allocate_page_table() {
    void* page = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (page == MAP_FAILED) {
        int err = errno;
        perror("mmap");
        exit(err);
    }
    return page;
}

static void deallocate_page_table(void* page) {
    if (munmap(page, PAGE_SIZE) == -1) {
        int err = errno;
        perror("munmap");
        exit(err);
    }
}

static uint64_t mmu(uint64_t virtual_address) {
    uint64_t* page_table = root_page_table;
    uint64_t va = (uint64_t) virtual_address;
    for (int i = LEVELS - 1; i >= 0; --i) {
        uint8_t start_bit = 9 * i + 12;
        uint64_t mask = (uint64_t) 0x1FF << start_bit;
        uint16_t index = (mask & va) >> start_bit;

        uint64_t pte = page_table[index];
        if (!(pte & PTE_VALID)) {
            printf("0x%lX: page fault\n", va);
            return 0;
        }

        if (i != 0) {
            page_table = (uint64_t*) ((pte >> 10) << 12);
            continue;
        }

        uint64_t pa = ((pte & ~0x3FF) << 2) | (va & 0xFFF);
        printf("0x%lX: 0x%lX\n", va, pa);
        return pa;
    }
    __builtin_unreachable();
}


uint64_t pte_from_ppn(uint64_t ppn) {
    uint64_t pte = ppn << 10;
    pte |= PTE_VALID;
    return pte;
}

uint64_t pte_from_page_table(uint64_t* page_table) {
    return pte_from_ppn(((uint64_t) page_table) >> 12);
}

int main() {
    assert(sysconf(_SC_PAGE_SIZE) == PAGE_SIZE);

    root_page_table = allocate_page_table();

    uint64_t* l1_page_table = allocate_page_table();
    root_page_table[0] = pte_from_page_table(l1_page_table);

    uint64_t* l0_page_table = allocate_page_table();
    l1_page_table[5] = pte_from_page_table(l0_page_table);

    l0_page_table[188] = pte_from_ppn(0xCAFE);

    mmu(0xABCDEF);

    deallocate_page_table(root_page_table);
    root_page_table = NULL;

    return 0;
}
