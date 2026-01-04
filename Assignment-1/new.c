#include <stdio.h>
#include <pthread.h>

// Structure for student data
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Thread function
void* check_deans_list(void* arg) {
    Student* s = (Student*)arg;

    printf("\n--- Student Info ---\n");
    printf("ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    if (s->gpa >= 3.5)
        printf("Status: Dean's List ✅\n");
    else
        printf("Status: Not Eligible ❌\n");

    return NULL;
}

int main() {
    pthread_t threads[3];

    Student students[3] = {
        {101, "Alice Johnson", 3.8},
        {102, "Bob Smith", 3.2},
        {103, "Charlie Brown", 3.9}
    };

    // Create threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_deans_list, &students[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll students checked successfully!\n");
    return 0;
}