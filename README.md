# COS-201 Group Project: Student Record System (SRS)

## Project Overview
The **Student Record System (SRS)** is a simple C program that manages student information efficiently. It allows users to add, modify, and search for student records and perform calculations like determining average marks and sorting records. The system is built with several key functionalities that enhance usability and maintainability.

## Features
The system currently supports the following features:

1. **greetUser**: Greets the user with a personalized message. This feature can be customized for a better user experience.

2. **addStudent**: Allows users to input student details, including:
   - First name
   - Last name
   - Roll number (ID number)
   - Marks

3. **modifyStudent**: Enables modification of student records, specifically updating the roll number (ID number) of a student.

4. **displayStudents**: Displays all student records and indicates whether each student has passed or failed based on a predefined passing threshold (e.g., marks above 40).

5. **saveStudentsToFile**: Saves student information (first name, last name, roll number, and marks) to a file. The system supports adding, removing, and modifying student records in memory, which can then be saved for future use.

6. **loadStudentsFromFile**: Loads student records from a file. (Note: This feature is currently in development and not fully implemented.)

7. **searchStudent**: Allows users to search for a student by roll number and displays the corresponding information.

8. **calculateAverageMarks**: Calculates and displays the average marks of all students. This feature builds on previous C programming exercises related to student calculations.

9. **compareMarksAsc**: Compares and sorts student marks in ascending order.

10. **compareMarksDesc**: Compares and sorts student marks in descending order.

11. **sortStudents**: Sorts student records based on marks, with the option to sort in either ascending or descending order.

## Usage
The system is designed to behave similarly to how users load data onto their phones, offering a smooth and intuitive experience. Users can easily add, modify, search, and sort student records, as well as calculate the average marks of the entire class.
