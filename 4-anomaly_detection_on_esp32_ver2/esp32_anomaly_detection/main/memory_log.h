#ifndef MEMORY_LOG_H
#define MEMORY_LOG_H
#include "esp_heap_caps.h"
#include "esp_log.h"
void get_heap_size_info(size_t* total_size, size_t* free_size);
void print_heap_size_info();
#endif