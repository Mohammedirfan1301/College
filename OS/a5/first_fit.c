/**
 *     Jason Downing
 *     Assignment 5 first first c file
 *
 */
#include "main.h"

int first_fit(int memorySize, char *fileToWrite) {

    char req_type[30];
    int req_seq = 0;
    int req_size = 0;

    FILE *file = fopen(fileToWrite, "r");

    // Free list
    struct free_list *freeList;
    total_free_space = total_free = (memorySize * 1024);

    // Init array
    int x = 0;
    for (x = 0; x < NUMBER_ENTRIES; x++) {
        req_array[x].is_req = FALSE;
        req_array[x].is_allocated = FALSE;
    }

    // Free node setup
    top = malloc(sizeof(struct free_list));
    top->next = NULL;
    top->previous = &list_head;
    top->block_size = total_free_space;
    top->block_adr = 0;
    top->adjacent_adr = total_free_space;

    // Next free node
    list_head.next = top;
    list_head.previous = NULL;
    list_head.block_size = -1;

    // Read all requests
    while (fscanf(file, "%d %s %d", &req_seq, &req_type, &req_size) != EOF) {

        if (strcmp(req_type, "alloc") == 0) {

            // Create request
            req_array[req_seq].is_req = TRUE;
            req_array[req_seq].size = req_size;

            allocate_first_fit(&req_array[req_seq]);

            // Reset
            req_array[req_seq].elements_on_free_list = 0;
            req_array[req_seq].largest_chunk = 0;

            for (freeList = list_head.next; freeList; freeList = freeList->next) {
                // Total free
                ++req_array[req_seq].elements_on_free_list;

                // FIRST FIT
                if (freeList->block_size > req_array[req_seq].largest_chunk) {
                    req_array[req_seq].largest_chunk = freeList->block_size;
                }
            }

        } else {
            // Free
            req_array[req_seq].size = req_array[req_size].size;
            req_array[req_seq].is_allocated = req_array[req_size].is_allocated;

            update_list(req_size);

            // Reset
            req_array[req_seq].memory_left = total_free;
            req_array[req_seq].elements_on_free_list = 0;
            req_array[req_seq].largest_chunk = 0;

            for (freeList = list_head.next; freeList; freeList = freeList->next) {
                // Total free
                ++req_array[req_seq].elements_on_free_list;

                // FIRST FIT
                if (freeList->block_size > req_array[req_seq].largest_chunk) {
                    req_array[req_seq].largest_chunk = freeList->block_size;
                }
            }

        }

    }
    print_results("First Fit", memorySize, req_array);
    fclose(file);
}

int allocate_first_fit(struct request *request) {

    struct free_list *freeList = NULL;

    // Find first block that fits
    for (freeList = list_head.next; freeList; freeList = freeList->next) {
        if (request->size <= freeList->block_size) {
            // Valid
            request->is_allocated = TRUE;
            request->base_adr = freeList->block_adr;
            request->next_boundary_adr = request->base_adr + request->size;

            total_free = total_free - request->size;
            request->memory_left = total_free;

            if ((freeList->block_size = freeList->block_size - request->size) == 0) {
                freeList->previous->next = freeList->next;
                freeList->next->previous = freeList->previous;

                free(freeList);
                return 0;
            }

            freeList->block_adr = freeList->block_adr + request->size;
            return 0;
        }
    }

    // No valid block
    request->memory_left = total_free;
    return 0;

}
