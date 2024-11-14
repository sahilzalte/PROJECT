#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a student node
struct Student
{
    int rollNo;
    char name[100];
    char course[100];
    float marks;
    struct Student *next; // Pointer to the next student
};

// Structure for managing the student database
struct StudentDatabase
{
    struct Student *head; // Head of the linked list
};

// Function to create a new student
struct Student *createStudent(int rollNo, const char *name, const char *course, float marks)
{
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (newStudent == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newStudent->rollNo = rollNo;
    strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0'; // Ensure null termination
    strncpy(newStudent->course, course, sizeof(newStudent->course) - 1);
    newStudent->course[sizeof(newStudent->course) - 1] = '\0'; // Ensure null termination
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}

// Function to initialize the student database
void initDatabase(struct StudentDatabase *db)
{
    db->head = NULL;
}

// Function to add a new student
void addStudent(struct StudentDatabase *db, int rollNo, const char *name, const char *course, float marks)
{
    struct Student *newStudent = createStudent(rollNo, name, course, marks);
    if (!db->head)
    {
        db->head = newStudent;
    }
    else
    {
        struct Student *temp = db->head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    printf("Student added successfully.\n");
}

// Function to display all students
void displayStudents(const struct StudentDatabase *db)
{
    if (!db->head)
    {
        printf("No records found.\n");
        return;
    }
    printf("Student Records:\n");
    struct Student *temp = db->head;
    while (temp)
    {
        printf("Roll No: %d, Name: %s, Course: %s, Marks: %.2f\n", temp->rollNo, temp->name, temp->course, temp->marks);
        temp = temp->next;
    }
}

// Function to search for a student by roll number
void searchStudent(const struct StudentDatabase *db, int rollNo)
{
    struct Student *temp = db->head;
    while (temp)
    {
        if (temp->rollNo == rollNo)
        {
            printf("Student Found: Roll No: %d, Name: %s, Course: %s, Marks: %.2f\n", temp->rollNo, temp->name, temp->course, temp->marks);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

// Function to delete a student by roll number
void deleteStudent(struct StudentDatabase *db, int rollNo)
{
    if (!db->head)
    {
        printf("No records found to delete.\n");
        return;
    }
    if (db->head->rollNo == rollNo)
    {
        struct Student *temp = db->head;
        db->head = db->head->next;
        free(temp);
        printf("Student deleted successfully.\n");
        return;
    }
    struct Student *current = db->head;
    struct Student *previous = NULL;
    while (current && current->rollNo != rollNo)
    {
        previous = current;
        current = current->next;
    }
    if (!current)
    {
        printf("Student not found.\n");
        return;
    }
    previous->next = current->next;
    free(current);
    printf("Student deleted successfully.\n");
}

// Function to save student records to a file
void saveToFile(const struct StudentDatabase *db, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file)
    {
        struct Student *temp = db->head;
        while (temp)
        {
            fprintf(file, "%d\n%s\n%s\n%.2f\n", temp->rollNo, temp->name, temp->course, temp->marks);
            temp = temp->next;
        }
        fclose(file);
        printf("Data saved to file successfully.\n");
    }
    else
    {
        printf("Error opening file for saving!\n");
    }
}

// Function to load student records from a file
void loadFromFile(struct StudentDatabase *db, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        while (1)
        {
            int rollNo;
            char name[100], course[100];
            float marks;

            // Read each record
            if (fscanf(file, "%d\n", &rollNo) != 1)
                break; // Read roll number
            fgets(name, sizeof(name), file);
            name[strcspn(name, "\n")] = 0; // Remove newline character
            fgets(course, sizeof(course), file);
            course[strcspn(course, "\n")] = 0; // Remove newline character
            if (fscanf(file, "%f\n", &marks) != 1)
                break; // Read marks

            addStudent(db, rollNo, name, course, marks);
        }
        fclose(file);
        printf("Data loaded from file successfully.\n");
    }
    else
    {
        printf("File not found.\n");
    }
}

// Function to free memory
void freeDatabase(struct StudentDatabase *db)
{
    struct Student *current = db->head;
    while (current)
    {
        struct Student *next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    struct StudentDatabase db;
    initDatabase(&db);

    // Load existing data from file at startup
    loadFromFile(&db, "STUDENT.TXT");

    int choice;
    do
    {
        printf("\nStudent Database Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Save to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int rollNo;
            char name[100], course[100];
            float marks;
            printf("Enter Roll No: ");
            scanf("%d", &rollNo);
            getchar(); // Clear the input buffer
            printf("Enter Name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; // Remove newline character
            printf("Enter Course: ");
            fgets(course, sizeof(course), stdin);
            course[strcspn(course, "\n")] = 0; // Remove newline character
            printf("Enter Marks: ");
            scanf("%f", &marks);

            addStudent(&db, rollNo, name, course, marks);
            break;
        }
        case 2:
            displayStudents(&db);
            break;
        case 3:
        {
            int rollNo;
            printf("Enter Roll No to search: ");
            scanf("%d", &rollNo);
            searchStudent(&db, rollNo);
            break;
        }
        case 4:
        {
            int rollNo;
            printf("Enter Roll No to delete: ");
            scanf("%d", &rollNo);
            deleteStudent(&db, rollNo);
            break;
        }
        case 5:
            saveToFile(&db, "STUDENT.TXT");
            break;
        case 6:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    freeDatabase(&db);
    return 0;
}
