#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double data;
} Record;

void demonstrate_malloc() {
    printf("=== malloc() demonstration ===\n");
    
    int* numbers = (int*)malloc(5 * sizeof(int));
    if (numbers == NULL) {
        perror("malloc failed");
        exit(1);
    }
    
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    free(numbers);
    printf("\n");
}

void demonstrate_calloc() {
    printf("=== calloc() demonstration ===\n");
    
    int* zeros = (int*)calloc(5, sizeof(int));
    if (zeros == NULL) {
        perror("calloc failed");
        exit(1);
    }
    
    printf("Initialized with zeros:\n");
    for (int i = 0; i < 5; i++) {
        printf("zeros[%d] = %d\n", i, zeros[i]);
    }
    
    free(zeros);
    printf("\n");
}

void demonstrate_realloc() {
    printf("=== realloc() demonstration ===\n");
    
    int* arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        exit(1);
    }
    
    for (int i = 0; i < 3; i++) {
        arr[i] = i + 1;
    }
    
    printf("Original array (size 3):\n");
    for (int i = 0; i < 3; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    // Resize to 6 elements
    arr = (int*)realloc(arr, 6 * sizeof(int));
    if (arr == NULL) {
        perror("realloc failed");
        exit(1);
    }
    
    for (int i = 3; i < 6; i++) {
        arr[i] = i + 1;
    }
    
    printf("Resized array (size 6):\n");
    for (int i = 0; i < 6; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    free(arr);
    printf("\n");
}

void demonstrate_struct_allocation() {
    printf("=== Structure allocation demonstration ===\n");
    
    Record* record = (Record*)malloc(sizeof(Record));
    if (record == NULL) {
        perror("malloc failed");
        exit(1);
    }
    
    record->id = 101;
    snprintf(record->name, sizeof(record->name), "Sample Record");
    record->data = 3.14159;
    
    printf("Record ID: %d\n", record->id);
    printf("Record Name: %s\n", record->name);
    printf("Record Data: %.5f\n", record->data);
    
    free(record);
    printf("\n");
}

int main() {
    printf("Memory Management Examples\n");
    printf("===========================\n\n");
    
    demonstrate_malloc();
    demonstrate_calloc();
    demonstrate_realloc();
    demonstrate_struct_allocation();
    
    printf("All memory operations completed successfully\n");
    printf("Run with valgrind to verify no memory leaks\n");
    
    return 0;
}
