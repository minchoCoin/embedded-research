#include "memory_log.h"
void get_heap_size_info(size_t* total_size, size_t* free_size){
    *total_size = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    *free_size = heap_caps_get_free_size(MALLOC_CAP_8BIT);
}
void print_heap_size_info(){
    size_t heap_total_size=0;
    size_t heap_free_size=0;
    get_heap_size_info(&heap_total_size,&heap_free_size);
    ESP_LOGI("log","heap total size: %zu",heap_total_size);
    ESP_LOGI("log","Heap free size: %zu(%g%% used)",heap_free_size,float(heap_total_size - heap_free_size)/float(heap_total_size)*100.0f);
}