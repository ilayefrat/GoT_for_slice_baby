#pragma once

#define PAGE_SIZE (4096)

// Cache properties.
#define LLC_CACHE_SIZE (8*1024*1024)
#define CACHE_ASSOCIATIVITY (16)
#define CACHE_SLICES (8)
#define CACHE_LINE_SIZE (64)
#define DOUBLE_CACHE_LINE_SIZE (128)
#define L2_CACHE_SIZE (256*1024)
#define L2_CACHE_ASSOCIATIVITY (4)

// ASCII colors
//Regular text
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
//Reset
#define RST "\e[0m"
