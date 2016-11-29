/**
 *     Jason Downing
 *     Assignment 5 best fit c file
 */
#include "main.h"

int best_fit(int memorySize, char *fileToWrite) {

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

            allocate_best_fit(&req_array[req_seq]);

            // Reset
            req_array[req_seq].elements_on_free_list = 0;
            req_array[req_seq].largest_chunk = 0;

            for (freeList = list_head.next; freeList; freeList = freeList->next) {
                // Total free
                ++req_array[req_seq].elements_on_free_list;

                // BEST FIT
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

                // BEST FIT
                if (freeList->block_size > req_array[req_seq].largest_chunk) {
                    req_array[req_seq].largest_chunk = freeList->block_size;
                }
            }

        }

    }
    print_results("Best Fit", memorySize, req_array);
    fclose(file);
}

int allocate_best_fit(struct request *request) {

    // Free lists
    struct free_list *freeList = NULL;
    struct free_list *validList = NULL;
    int sizeDiff = 0;
    int leftover = 0;


    // Find the smallest block that fits
    int bFlag = TRUE;
    for (freeList = list_head.next; freeList; freeList = freeList->next) {
        if (request->size <= freeList->block_size) {
            sizeDiff = freeList->block_size - request->size;

            if (leftover >= sizeDiff) {
                leftover = sizeDiff;
                validList = freeList;
            }
            if (bFlag) leftover = sizeDiff;
            bFlag = FALSE;

        }
    }

    // Did we find stuff we can use
    if (validList != NULL) {
        /* Set request */
        request->is_allocated = TRUE;
        request->base_adr = validList->block_adr;
        request->next_boundary_adr = request->base_adr + request->size;

        // update
        total_free = total_free - request->size;
        request->memory_left = total_free;

        // If there is a perfect match
        if ((validList->block_size = validList->block_size - request->size) == 0) {
            validList->previous->next = validList->next;
            validList->next->previous = validList->previous;
            free(validList);
            return 0;
        }

        validList->block_adr = validList->block_adr + request->size;
        return 0;

    }

    // No valid space
    request->memory_left = total_free;
    return 0;
}
