#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 100

// Equipment structure
typedef struct Equipment {
    int id;
    char name[MAX_NAME_LEN];
    struct Equipment* next;
} Equipment;

// Function to create a new equipment record
Equipment* createEquipment(int id, const char* name) {
    Equipment* newEquipment = (Equipment*)malloc(sizeof(Equipment));
    newEquipment->id = id;
    strncpy(newEquipment->name, name, MAX_NAME_LEN);
    newEquipment->next = NULL;
    return newEquipment;
}

// Function to add equipment to the list
void addEquipment(Equipment** head, int id, const char* name) {
    Equipment* newEquipment = createEquipment(id, name);
    newEquipment->next = *head;
    *head = newEquipment;
}

// Function to delete equipment by ID
void deleteEquipment(Equipment** head, int id) {
    Equipment* current = *head;
    Equipment* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Equipment with ID %d not found.\n", id);
        return;
    }

    if (previous == NULL) {
        *head = current->next; // Deleting the head
    } else {
        previous->next = current->next; // Bypass the current
    }

    free(current);
    printf("Deleted equipment with ID %d.\n", id);
}

// Function to search equipment by name
void searchEquipment(Equipment* head, const char* name) {
    Equipment* current = head;
    while (current != NULL) {
        if (strcasecmp(current->name, name) == 0) {
            printf("Found equipment: ID=%d, Name=%s\n", current->id, current->name);
            return;
        }
        current = current->next;
    }
    printf("Equipment with name %s not found.\n", name);
}

// Function to display all equipment records (can be commented out if not needed)
void displayEquipment(Equipment* head) {
    if (head == NULL) {
        printf("No equipment records found.\n");
        return;
    }
    Equipment* current = head;
    while (current != NULL) {
        printf("ID: [%d] || NAME: [%s]\n", current->id, current->name);
        current = current->next;
    }
}

// Function to save equipment records to a file
void saveToFile(Equipment* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Equipment* current = head;
    while (current != NULL) {
        fprintf(file, "ID: [%d] || NAME: [%s]\n", current->id, current->name);
        current = current->next;
    }
    fclose(file);
    printf("Equipment records saved successfully.\n"); // Confirmation message only
}

// Function to load equipment records from a file
void loadFromFile(Equipment** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int id;
    char name[MAX_NAME_LEN];
    while (fscanf(file, "ID: [%d] || NAME: [%99[^\n]]\n", &id, name) == 2) {
        addEquipment(head, id, name);
    }
    fclose(file);
    printf("Equipment records loaded successfully.\n"); // Confirmation message only
}

// Main function
int main() {
    Equipment* labEquipment = NULL;
    int choice, id;
    char name[MAX_NAME_LEN];

    while (1) {
        printf("\nLab Management System\n");
        printf("1. Add Equipment\n");
        printf("2. Delete Equipment\n");
        printf("3. Search Equipment\n");
        printf("4. Display All Equipment\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %[^\n]", name); // Read string with spaces
                addEquipment(&labEquipment, id, name);
                printf("Added equipment: ID=%d, Name=%s\n", id, name); // Confirmation message
                break;
            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteEquipment(&labEquipment, id);
                break;
            case 3:
                printf("Enter Name to search: ");
                scanf(" %[^\n]", name);
                searchEquipment(labEquipment, name);
                break;
            case 4:
                displayEquipment(labEquipment); // Show all equipment if needed
                break;
            case 5:
                saveToFile(labEquipment, "equipment.txt");
                break;
            case 6:
                loadFromFile(&labEquipment, "equipment.txt");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

   return 0;
}