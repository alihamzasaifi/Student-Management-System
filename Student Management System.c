#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximum students or courses ko define krta hai
#define MAX_STUDENTS 100
#define MAX_SUBJECTS 6 // Number of subjects

// ye structure student information ko hold krta hai
struct Student {
    int id;
    char name[50];
    int age;
    char gender;
    float marks[MAX_SUBJECTS]; // Marks for 6 subjects
    float percentage; // Percentage based on marks
};

struct User {
    char username[50];
    char password[50];
};

// Declare an array of students
struct Student students[MAX_STUDENTS];
int student_count = 0;

// prototypes of functions
void add_student();
void display_students();
void update_student();
void delete_student();
void input_grades(struct Student* student);
void calculate_percentage(struct Student* student);
void detailed_report(struct Student* student);
void check_pass_status(struct Student* student);
void save_data();
void load_data();
void backup_data();
void print_reports();
void search_student();
void user_login();
void menu();

// default username or password batata hai or check bi krta hai
void user_login() {
    char admin_username[] = "admin";
    char admin_password[] = "adminpass";
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%s", input_username);
    printf("Enter password: ");
    scanf("%s", input_password);

    if (strcmp(input_username, admin_username) == 0 && strcmp(input_password, admin_password) == 0) {
        printf("Login successful as Admin.\n");
    } else {
        printf("Invalid username or password. Exiting...\n");
        exit(0);
    }
}

// menu
void menu() {
    int choice;
    do {
        printf("\n------ Student Management System ------\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Input Grades\n");
        printf("6. Calculate Percentage\n");
        printf("7. Detailed Report\n");
        printf("8. Check Pass Status\n");
        printf("9. Save Data\n");
        printf("10. Load Data\n");
        printf("11. Backup Data\n");
        printf("12. Print Reports\n");
        printf("13. Search Student\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {  // Check if input is valid
            printf("Invalid input. Please enter a valid number.\n");

            // Clear the input buffer
            while (getchar() != '\n');
            continue;  // Skip this iteration and prompt again
        }

        switch (choice) {
            case 1: add_student(); break;
            case 2: display_students(); break;
            case 3: update_student(); break;
            case 4: delete_student(); break;
            case 5: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    input_grades(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 6: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    calculate_percentage(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 7: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    detailed_report(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 8: {
                int id;
                printf("Enter student ID: ");
                scanf("%d", &id);
                if (id >= 0 && id < student_count)
                    check_pass_status(&students[id]);
                else
                    printf("Student not found!\n");
                break;
            }
            case 9: save_data(); break;
            case 10: load_data(); break;
            case 11: backup_data(); break;
            case 12: print_reports(); break;
            case 13: search_student(); break;
            case 14: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Please try again.\n"); break;
        }
    } while (choice != 14);
}

// student add krta hai
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }

    struct Student new_student;
    new_student.id = student_count;

    // input buffer clear krna hai name sy pahly
    while (getchar() != '\n');  // input buffer clear krta hai

    printf("Enter student name: ");
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;  // newline ko remove krta hai

    printf("Enter age: ");
    scanf("%d", &new_student.age);

    printf("Enter gender (M/F): ");
    getchar();  // leftover newline ko consume krta hai
    scanf("%c", &new_student.gender);

    // gender input ko check krta hai k male or female hai ya nhi
    if (new_student.gender != 'M' && new_student.gender != 'F') {
        printf("Invalid gender input. Please enter M or F.\n");
        return;
    }

    students[student_count++] = new_student;
    printf("Student added successfully.\n");
}

// all students ko display krta hai
void display_students() {
    if (student_count == 0) {
        printf("No students found.\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %c\n",
               students[i].id, students[i].name, students[i].age, students[i].gender);
    }
}

// grades input k liye
void input_grades(struct Student* student) {
    const char* subjects[] = {"Urdu", "English", "Science", "Math", "Pak Studies", "Islamiyat"};
    printf("Enter grades for %s (6 subjects, each out of 100):\n", student->name);
    
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        float grade;
        int valid_input = 0;
        
        while (!valid_input) {
            printf("Enter marks for %s (out of 100): ", subjects[i]);
            scanf("%f", &grade);
            
            // input check krta hai k marks 0-100 hi hain ya nhi
            if (grade < 0 || grade > 100) {
                printf("Error: Marks for %s cannot exceed 100. Please enter again.\n", subjects[i]);
            } else {
                student->marks[i] = grade;
                valid_input = 1;
            }
        }
    }
}

// percentage calculate krta hai
void calculate_percentage(struct Student* student) {
    float total_marks = 0;
    
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        total_marks += student->marks[i];
    }

    // Percentage calculate krta hai (formula) (6 subjects, each 100 marks)
    student->percentage = (total_marks / (MAX_SUBJECTS * 100)) * 100;
    printf("Percentage for %s: %.2f%%\n", student->name, student->percentage);
}

// student ka passing status check krta hai
void check_pass_status(struct Student* student) {
    if (student->percentage >= 50.0) {
        printf("%s has passed with a percentage of %.2f%%\n", student->name, student->percentage);
    } else {
        printf("%s has not passed. Percentage is %.2f%%\n", student->name, student->percentage);
    }
}

// aik detailed report display krta hai
void detailed_report(struct Student* student) {
    printf("\n------ Detailed Report for %s ------\n", student->name);
    printf("Student ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("Gender: %c\n", student->gender);

    // har subject k marks print krta hai
    const char* subjects[] = {"Urdu", "English", "Science", "Math", "Pak Studies", "Islamiyat"};
    printf("Marks:\n");
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("%s: %.2f\n", subjects[i], student->marks[i]);
    }

    // percentage print krta hai
    printf("Percentage: %.2f%%\n", student->percentage);
}

// student data ko file mai save krta hai
void save_data() {
    FILE *file = fopen("students_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving data.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d %s %d %c %.2f ", students[i].id, students[i].name, students[i].age,
                students[i].gender, students[i].percentage);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fprintf(file, "%.2f ", students[i].marks[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

// student data ko file sy load krta hai
void load_data() {
    FILE *file = fopen("students_data.txt", "r");
    if (!file) {
        printf("No file found to load data.\n");
        return;
    }

    student_count = 0;
    while (fscanf(file, "%d %s %d %c %f", 
                  &students[student_count].id, 
                  students[student_count].name, 
                  &students[student_count].age, 
                  &students[student_count].gender, 
                  &students[student_count].percentage) != EOF) {
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            fscanf(file, "%f", &students[student_count].marks[i]);
        }
        student_count++;
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

// student data ko backup krta hai
void backup_data() {
    FILE *source = fopen("students_data.txt", "r");
    if (source == NULL) {
        printf("Error opening source file for backup.\n");
        return;
    }

    FILE *destination = fopen("backup_students_data.txt", "w");
    if (destination == NULL) {
        printf("Error opening backup file.\n");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, destination);
    }

    fclose(source);
    fclose(destination);
    printf("Data backed up successfully.\n");
}

// all students ki reports ko print krta hai
void print_reports() {
    if (student_count == 0) {
        printf("No student reports available.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        detailed_report(&students[i]);
    }
}

// Search for a student by name
void search_student() {
    char name[50];
    printf("Enter student name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // newline remove krta hai

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Student found!\n");
            detailed_report(&students[i]);
            return; // student find k baad function exit krta gai
        }
    }

    printf("Student not found.\n");
}

// student information update krny k liye
void update_student() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Student not found!\n");
        return;
    }

    struct Student *student = &students[id];

    // name read sy pahlay buffer clear krat hai
    while (getchar() != '\n');  // Clear the buffer

    printf("Updating student: %s\n", student->name);
    printf("Enter new name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = 0;

    printf("Enter new age: ");
    scanf("%d", &student->age);

    printf("Enter new gender (M/F): ");
    getchar();  // consume leftover newline
    scanf("%c", &student->gender);

    // gender input check krta hai
    if (student->gender != 'M' && student->gender != 'F') {
        printf("Invalid gender input. Please enter M or F.\n");
    }

    printf("Student information updated successfully.\n");
}

// Function to delete a student's record
void delete_student() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Student not found!\n");
        return;
    }

    for (int i = id; i < student_count - 1; i++) {
        students[i] = students[i + 1]; // Shift students left
    }
    student_count--;
    printf("Student deleted successfully.\n");
}

int main() {
	load_data();  // student data load krta hai 
    user_login();  // Admin login
    menu();  // menu show krta hai

    return 0;
}
