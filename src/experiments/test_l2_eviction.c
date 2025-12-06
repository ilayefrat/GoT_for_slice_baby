#include "consts.h"
#include "ev/ev.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int test_l2_eviction(int argc, char *argv[]) {
  printf("Starting L2 eviction set test...\n");

  // Allocate a buffer to pick a target from
  size_t buffer_size = 4096 * 10; // 10 pages
  void *buffer = NULL;
  initialize_allocation(&buffer, buffer_size);

  // Pick a target address in the middle
  uintptr_t target = (uintptr_t)buffer + 4096 * 5 + 64; // Some offset

  printf("Target address: %p\n", (void *)target);
  print_cache_bucket2(target);
  printf("Target phys: %p\n",(void *)virt_to_physical(target));
  printf("Target cacheset: %lu\n",physical_to_cacheset2(virt_to_physical(target)));

  for (int i = 0; i < 10; i++) {
    printf("\nIteration %d:\n", i + 1);

    eviction_set l2_set = {0};
    if (populate_eviction_set_l2_cheat(&l2_set, target)) {
      printf("Found L2 eviction set of size %d:\n", l2_set.length);
      for (uint32_t j = 0; j < l2_set.length; j++) {
        uint64_t ilay = physical_to_cacheset2(virt_to_physical(l2_set.arr[j]));
        printf("  %p\n", (void *)l2_set.arr[j]);
        print_cache_bucket2(l2_set.arr[j]);
        printf(" and the phisical is %p\n", (void *)virt_to_physical(l2_set.arr[j]));
        printf(" and the CACHESET is %lu\n", ilay);
      }

      // Verify size matches L2 associativity
      if (l2_set.length == L2_CACHE_ASSOCIATIVITY) {
        printf("SUCCESS: Eviction set size matches L2 associativity.\n");
      } else {
        printf("WARNING: Eviction set size (%d) does not match L2 "
               "associativity (%d).\n",
               l2_set.length, L2_CACHE_ASSOCIATIVITY);
      }

      // Free allocated array
      if (l2_set.arr) {
        free(l2_set.arr);
      }
    } else {
      printf("FAILED to populate L2 eviction set.\n");
    }
  }

  return 0;
}
