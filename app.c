#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Define a struct to store student information
struct Student {
    char name[50]; // Student's name
    int rollNumber; // Student's roll number (ID)
    float marks; // Student's marks
};

#define MAX_STUDENTS 100  // Define the maximum number of students

// Function to check if the input contains only alphabetic characters
int isValidName(char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        // Allow spaces and alphabetic characters only
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0;  // Invalid character found
        }
    }
    return 1;  // All characters are valid
}

// Function to display welcome message and greet user
void greetUser(char *userName) {
    // Display welcome message with space
    printf("\nWelcome to the Student Record System (SRS)\n\n");

    // Loop to ask for name until it's valid (not empty and contains only alphabetic characters)
    while (1) {
        printf("Please enter your name (alphabetic characters only): ");
        fgets(userName, 50, stdin);  // Get name from user input
        userName[strcspn(userName, "\n")] = '\0'; // Remove newline

        // Error handling: Ensure the name is not empty and contains only valid characters
        if (strlen(userName) == 0) {
            printf("Error: Name cannot be empty. Please try again.\n\n");
        } else if (!isValidName(userName)) {
            printf("\nError: Name must contain only alphabetic characters and spaces. Please try again.\n\n");
        } else {
            // Greet the user and break out of the loop if name is valid
            printf("\nHello, %s! Let's register some student data.\n\n", userName);
            break; // Valid name entered
        }
    }
}

// Function to check if a roll already exists
int isDuplicateRollNumber(int rollNumber, struct Student students[], int count) {
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            return 1; // Duplicate roll number found
        }
    }
    return 0; // No duplicate roll number
}

// Function to display a predefined student record
void displayStudentExample() {
    // Example of creating a student record
    struct Student student1;

    // Assign values to the student1 record
    strcpy(student1.name, "John Wick");
    student1.rollNumber = 001;
    student1.marks = 100;

    // Display the student information
    printf("\nExample of Student Record:\n");
    printf("Name: %s\n", student1.name);
    printf("Roll Number: %d\n", student1.rollNumber);
    printf("Marks: %.2f\n\n", student1.marks);
}

// Function to input student details with error handing
void inputStudentDetails(struct Student *student, struct Student students[], int count ) {
    // Input student name
    while (1) {
        printf("Enter student's name: ");
        fgets(student->name, sizeof(student->name), stdin);
        student->name[strcspn(student->name, "\n")] = '\0'; // Remove newline

        if (strlen(student->name) == 0) {
            printf("\nError: Name cannot be empty. Please try again.\n\n");
        } else if (!isValidName(student->name)) {
            printf("\nError: Name must contain only alphabetic characters. Please try again.\n\n");
        } else {
            break; // Valid student name entered
        }
    }

    // Input roll number (integer) with error handing and check for duplicates
    while (1) {
        printf("Enter student's roll number: ");
        if (scanf("%d", &student->rollNumber) != 1) {
            printf("\nError: Invalid roll number, Please enter an integer. \n\n");
            while (getchar() != '\n'); // Clear the input buffer
        } else if (student->rollNumber <= 0) {
            printf("\nError: Roll number must be a positive integer.\n\n");
        } else if (isDuplicateRollNumber(student->rollNumber, students, count)) {
            printf("\nError: Roll number already exists. Please enter a different roll number.\n\n");
        } else {
            break; // Valid roll number entered
        }
    }

    // Input marks (float) with error handing
    while (1) {
        printf("Enter student's marks (0-100): ");
        if(scanf("%f", &student->marks) != 1) {
            printf("\nError: Invalid marks. Please enter a number.\n\n");
            while (getchar() != '\n'); // Clear the input buffer
        } else  if (student->marks < 0 || student->marks > 100) {
            printf("\nError: Marks must be between 0 and 100.\n\n");
        } else {
            break; // Valid marks entered
        }
    }

    // Clear input buffer after marks entry
    while (getchar() != '\n');
}

// Function to save student records to a file 
void saveStudentRecords(struct Student students[], int count) {
    FILE *file = fopen("student_records.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    // Adding header at the top of the file
    fprintf(file, "Name\t\tRoll Number\tMarks\n");
    fprintf(file, "--------------------------------------\n");


    for (int i = 0; i < count; i++) {
        fprintf(file, "%-15s\t%d\t\t%.2f\n", students[i].name, students[i].rollNumber,students[i].marks);
    }

    fclose(file);
    printf("Student records saved successfully\n");
}

// Function to open file in the system's default text editor
void openFileInViewMode() {
    #ifdef _WIN32
        system("start student_records.txt"); // Windows command to open file
    #elif __APPLE__
        system("open student_records.txt"); // macos command to open file
    #else
        system("xdg-open student_records.txt"); // Linus command to open file
    #endif
}

// Load student records from a file and open in view mode
void loadStudentRecords(struct Student students[], int *count) {
    FILE *file = fopen("student_records.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for loading.\n");
        return;
    }
    *count = 0;
    while (fscanf(file, "%49[^,],%d,%f\n", students[*count].name, &students[*count].rollNumber, &students[*count].marks) == 3) {
        (*count)++;
    }
    fclose(file);
    printf("Student records loaded successfully.\n");

    // Open the file in view mode on local machine
    openFileInViewMode();
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu Options:\n");
    printf("1. Add new student records\n");
    printf("2. Remove student records\n");
    printf("3. Modify student records\n");
    printf("4. View student marks\n");
    printf("5. Search student records\n");
    printf("6. Save records to file\n");
    printf("7. Load records from file\n");
    printf("8. Calculate average marks\n");
    printf("9. Sort student records\n");
    printf("10. Exit\n");
    printf("Enter your choice: ");
}

// Function to remove a student record based on roll number or name
void removeStudent(struct Student students[], int *count) {
    if (*count == 0) {
        printf("\nNo student records available to remove.\n");
        return;
    }

    char searchName[50];
    int searchRollNumber;
    int foundIndex = -1;
    char choice;

    printf("\nEnter 'r' to search by roll number or 'n' to search by name: ");
    scanf(" %c", &choice);
    getchar();  // Clear the input buffer

    if (choice == 'r' || choice == 'R') {
        // Search by roll number
        printf("Enter roll number of the student to remove: ");
        scanf("%d", &searchRollNumber);
        getchar();  // Clear the input buffer

        // Find the student with the roll number
        for (int i = 0; i < *count; i++) {
            if (students[i].rollNumber == searchRollNumber) {
                foundIndex = i;
                break;
            }
        }
    } else if (choice == 'n' || choice == 'N') {
        // Search by name
        printf("Enter the name of the student to remove: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0'; // Remove the newline character

        // Find the student with the name
        for (int i = 0; i < *count; i++) {
            if (strcmp(students[i].name, searchName) == 0) {
                foundIndex = i;
                break;
            }
        }
    } else {
        printf("\nError: Invalid input.\n");
        return;
    }

    if (foundIndex == -1) {
        printf("\nError: Student not found.\n");
        return;
    }

    // Confirm removal
    printf("\nStudent found: %s, Roll Number: %d, Marks: %.2f\n", students[foundIndex].name, students[foundIndex].rollNumber, students[foundIndex].marks);
    printf("Are you sure you want to remove this student? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();  // Clear the input buffer

    if (confirm == 'y' || confirm == 'Y') {
        // Shift the records to remove the student
        for (int i = foundIndex; i < *count - 1; i++) {
            students[i] = students[i + 1];  // Shift each student one position to the left
        }
        (*count)--;  // Decrease the student count
        printf("\nStudent record removed successfully!\n");
    } else {
        printf("\nStudent record removal canceled.\n");
    }
}

// Function to modify a student record
void modifyStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available to modify.\n");
        return;
    }

    char searchName[50];
    int searchRollNumber;
    int foundIndex = -1;
    char choice;

    printf("\nEnter 'r' to search by roll number or 'n' to search by name: ");
    scanf(" %c", &choice);
    getchar();  // Clear the input buffer

    if (choice == 'r' || choice == 'R') {
        // Search by roll number
        printf("Enter roll number of the student to modify: ");
        scanf("%d", &searchRollNumber);
        getchar();  // Clear the input buffer

        // Find the student with the roll number
        for (int i = 0; i < count; i++) {
            if (students[i].rollNumber == searchRollNumber) {
                foundIndex = i;
                break;
            }
        }
    } else if (choice == 'n' || choice == 'N') {
        // Search by name
        printf("Enter the name of the student to modify: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0'; // Remove the newline character

        // Find the student with the name
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, searchName) == 0) {
                foundIndex = i;
                break;
            }
        }
    } else {
        printf("\nError: Invalid input.\n");
        return;
    }

    if (foundIndex == -1) {
        printf("\nError: Student not found.\n");
        return;
    }

    // Display the student details found
    printf("\nStudent found: %s, Roll Number: %d, Marks: %.2f\n", students[foundIndex].name, students[foundIndex].rollNumber, students[foundIndex].marks);

    // Confirm modification
    printf("Do you want to modify this student record? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();  // Clear the input buffer

    if (confirm == 'y' || confirm == 'Y') {
        // Modify student details
        char newName[50];
        int newRollNumber;
        float newMarks;

        // Input new student details
        printf("Enter new name (leave blank to keep current name): ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';  // Remove newline character

        // Update name only if it's not empty
        if (strlen(newName) > 0) {
            strcpy(students[foundIndex].name, newName);
        }

        printf("Enter new roll number (or enter -1 to keep current roll number): ");
        scanf("%d", &newRollNumber);
        getchar();  // Clear the input buffer

        // Check if the new roll number already exists
        if (newRollNumber != -1) {
            for (int i = 0; i < count; i++) {
                if (students[i].rollNumber == newRollNumber && i != foundIndex) {
                    printf("\nError: Another student with roll number %d already exists.\n", newRollNumber);
                    return;
                }
            }
            students[foundIndex].rollNumber = newRollNumber; // Update roll number
        }

        printf("Enter new marks (0-100) (or enter -1 to keep current marks): ");
        scanf("%f", &newMarks);
        getchar();  // Clear the input buffer

        // Validate and update marks
        if (newMarks >= 0 && newMarks <= 100) {
            students[foundIndex].marks = newMarks;
        } else if (newMarks != -1) {
            printf("\nError: Invalid marks. Please enter a value between 0 and 100.\n");
            return;
        }

        printf("\nStudent record modified successfully!\n");
    } else {
        printf("\nStudent record modification canceled.\n");
    }
}

// Function to view a student's marks by name or roll number
void viewStudentMarks(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available to view.\n");
        return;
    }

    char searchName[50];
    int searchRollNumber;
    int foundIndex = -1;
    char choice;

    printf("\nEnter 'r' to search by roll number or 'n' to search by name: ");
    scanf(" %c", &choice);
    getchar();  // Clear the input buffer

    if (choice == 'r' || choice == 'R') {
        // Search by roll number
        printf("Enter roll number of the student: ");
        scanf("%d", &searchRollNumber);
        getchar();  // Clear the input buffer

        // Find the student with the roll number
        for (int i = 0; i < count; i++) {
            if (students[i].rollNumber == searchRollNumber) {
                foundIndex = i;
                break;
            }
        }
    } else if (choice == 'n' || choice == 'N') {
        // Search by name
        printf("Enter the name of the student: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';  // Remove the newline character

        // Find the student with the name
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, searchName) == 0) {
                foundIndex = i;
                break;
            }
        }
    } else {
        printf("\nError: Invalid input.\n");
        return;
    }

    if (foundIndex == -1) {
        printf("\nError: Student not found.\n");
        return;
    }

    // Display student details if found
    printf("\nStudent found:\n");
    printf("Name: %s\n", students[foundIndex].name);
    printf("Roll Number: %d\n", students[foundIndex].rollNumber);
    printf("Marks: %.2f\n", students[foundIndex].marks);

    // Display pass or fail
    if (students[foundIndex].marks > 40) {
        printf("Status: Passed\n");
    } else {
        printf("Status: Failed\n");
    }
}

// Function to search for a student by roll number or name
void searchStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available to search.\n");
        return;
    }

    char searchName[50];
    int searchRollNumber;
    int foundIndex = -1;
    char choice;

    // Ask user how they want to search
    printf("\nEnter 'r' to search by roll number or 'n' to search by name: ");
    scanf(" %c", &choice);
    getchar();  // Clear the input buffer

    if (choice == 'r' || choice == 'R') {
        // Search by roll number
        printf("Enter the roll number of the student: ");
        scanf("%d", &searchRollNumber);
        getchar();  // Clear the input buffer

        // Find student by roll number
        for (int i = 0; i < count; i++) {
            if (students[i].rollNumber == searchRollNumber) {
                foundIndex = i;
                break;
            }
        }
    } else if (choice == 'n' || choice == 'N') {
        // Search by name
        printf("Enter the name of the student: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';  // Remove newline character

        // Find student by name
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, searchName) == 0) {
                foundIndex = i;
                break;
            }
        }
    } else {
        printf("\nError: Invalid choice.\n");
        return;
    }

    // Display student details if found
    if (foundIndex != -1) {
        printf("\nStudent found:\n");
        printf("Name: %s\n", students[foundIndex].name);
        printf("Roll Number: %d\n", students[foundIndex].rollNumber);
        printf("Marks: %.2f\n", students[foundIndex].marks);
    } else {
        printf("\nError: Student not found.\n");
    }
}

// Calculate and display the average marks of all students
void calculateAverageMarks(struct Student students[], int count) {
    if (count == 0) {
        printf("No student available to calculate the average.\n");
        return;
    }

    float totalMarks = 0.0;
    for (int i = 0; i < count; i++) {
        totalMarks += students[i].marks;
    }
    float averageMarks = totalMarks / count;
    printf("The average marks of all students %.2f\n", averageMarks);
}

// Compare function for ascending order
int comparAsc(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return (studentA->marks > studentB->marks) - (studentA->marks < studentB->marks);
}

// Compare function for descending order
int compareDesc(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return (studentB->marks > studentA->marks) - (studentB->marks < studentA->marks);
}

// Sort student records by marks in ascending or descending order
void sortStudentRecords(struct Student students[], int count, int ascending) {
    if (count == 0) {
        printf("No student records available to sort.\n");
        return;
    }

    if (ascending) {
        qsort(students, count, sizeof(struct Student), comparAsc);
        printf("\nStudent records sorted by marks in ascending order.\n");
    } else {
        qsort(students, count, sizeof(struct Student), compareDesc);
        printf("\nStudent records sorted by marks in descending order.\n");
    }

    // Display sorted records 
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %2f\n", students[i].name, students[i].rollNumber, students[i].marks);
    }
}

int main() {
    char userName[50];  // Buffer to store user's name
    struct Student students[MAX_STUDENTS];  // Array to store up to 100 students
    int studentCount = 0;  // To track the number of students
    int choice;

    // Greet the user and capture their name
    greetUser(userName);

    // Call the function to display the example student record
    displayStudentExample();

    // Initial phase: adding at least one student before showing the menu
    while (1) {
        inputStudentDetails(&students[studentCount], students, studentCount);
        studentCount++;
        printf("\nStudent record added successfully!\n");

        // Ask if the user wants to add more students
        char addMore;
        printf("\nDo you want to add another student? (y/n): ");
        scanf(" %c", &addMore);
        getchar();  // Clear the input buffer

        if (addMore == 'n' || addMore == 'N') {
            break;  // Exit the student-adding loop and proceed to the menu
        }
    }

    // Now display the menu for further actions after adding the first student
    while (1) {
        // Display menu and get user's choice
        displayMenu();
        scanf("%d", &choice);
        getchar();  // Clear the input buffer

        switch (choice) {
            case 1:  // Add new student
                // Allow user to continue adding students after menu is displayed
                while (1) {
                    inputStudentDetails(&students[studentCount], students, studentCount);
                    studentCount++;
                    printf("\nStudent record added successfully!\n");

                    // Ask if the user wants to add more students
                    char addMore;
                    printf("\nDo you want to add another student? (y/n): ");
                    scanf(" %c", &addMore);
                    getchar();  // Clear the input buffer

                    if (addMore == 'n' || addMore == 'N') {
                        break;  // Exit the student-adding loop and return to menu
                    }
                }
                break;

            case 2:  // Remove student record
                removeStudent(students, &studentCount);
                break;

            case 3:  // Modify student record
                modifyStudent(students, studentCount);
                break;

            case 4:  // View student marks
                viewStudentMarks(students, studentCount);
                break;

            case 5:  // Search student record
                searchStudent(students, studentCount);
                break;

            case 6:  // Save records to file
                saveStudentRecords(students, studentCount);
                break;

            case 7:  // Load records from file
                loadStudentRecords(students, &studentCount);
                break;

            case 8:  // Calculate average marks
                calculateAverageMarks(students, studentCount);
                break;

            case 9:  // Sort records
                printf("Choose sorting order (1 for ascending, 0 for descending):");
                int order;
                scanf("%d", &order);
                sortStudentRecords(students, studentCount, order);
                break;

            case 10:  // Exit
                printf("\nExiting the program %s, Goodbye!\n", userName);
                return 0;

            default:
                printf("\nError: Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
