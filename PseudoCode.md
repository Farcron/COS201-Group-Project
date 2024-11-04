### Pseudocode for Student Record System (SRS)

1. **Display Welcome Message and Greet User:**

    - Start
    - Display "Welcome to the Student Record System"
    - Ask the user to enter their name
        - **Error handling:** Ensure the name input is not empty, contains only alphabetic characters
    - Display "Hello, [user_name]!"

2. **Data Storage:**

    - Define a `struct` to store student information:
        - Name (string)
        - Roll number (int)
        - Marks (float)

3. **Input and Output (with Error Handling):**

    - Define a function to input student marks:
        - Input roll number, name, and marks
            - **Error handling:** Ensure valid data types (e.g., roll number is an integer, marks are a valid float)
        - If marks > 40, display "Student has passed"
        - Else, display "Student has failed"
        - **Error handling:** If marks are out of range (e.g., negative or greater than 100), display an error message

4. **Student Records Management:**

    - Create an array or dynamically allocated array to store multiple student records
    - Loop for inputting information for multiple students until the user exits
        - Implement functions for:
            - Adding a student:
                - **Error handling:** Check if student record already exists (based on roll number)
            - Removing a student:
                - **Error handling:** Ensure the student exists before attempting to remove
            - Modifying a student:
                - **Error handling:** Check if the student exists before modifying

5. **Memory Management:**

    - Use `malloc` or `realloc` for dynamic memory allocation
        - **Error handling:** Check if memory allocation is successful (i.e., `malloc` doesn’t return `NULL`)
    - Ensure `free()` is called to release memory when no longer needed

6. **File Operations (with Error Handling):**

    - Define functions to save student records to a text file:
        - Open file in write mode
            - **Error handling:** Check if file opens successfully
        - Write name, roll number, and marks for each student
        - Close the file
    - Define functions to load student records from a text file:
        - Open file in read mode
            - **Error handling:** Check if file opens successfully
        - Read and store data into student record array
        - **Error handling:** Ensure data is correctly formatted in the file

7. **Search Functionality:**

    - Implement a search function to find a student by roll number:
        - **Error handling:** Display "Student not found" if the roll number doesn’t exist

8. **Calculations and Sorting (with Error Handling):**
    - Implement a function to calculate and display the average marks for all students
        - **Error handling:** Ensure the student list is not empty before calculating average
    - Provide an option to sort student records by marks (ascending or descending)
        - **Error handling:** Ensure sorting is applied only when there are student records
