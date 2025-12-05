#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    char roll[20];
    char name[50];
    float marks;
    char grade;   // NEW FIELD
};

char currentRole[10];
char currentUser[50];

/* Function Declarations */
int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void sortStudents();

char calculateGrade(float marks);

/* ======================================
               MAIN
======================================*/
int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied! Exiting...\n");
    }
    return 0;
}

/* ======================================
            LOGIN SYSTEM
======================================*/
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];

    printf("===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ======================================
                MENUS
======================================*/

void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        guestMenu();
}

/* ----- ADMIN MENU ----- */
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students\n");
        printf("7. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 7: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ----- USER MENU ----- */
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Sort Students\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: sortStudents(); break;
            case 4: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ----- STAFF MENU ----- */
void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Sort Students\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: sortStudents(); break;
            case 5: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ----- GUEST MENU ----- */
void guestMenu() {
    int choice;
    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Sort Students\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: sortStudents(); break;
            case 3: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ======================================
        GRADE CALCULATION
======================================*/

char calculateGrade(float marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else return 'F';
}

/* ======================================
        STUDENT FILE OPERATIONS
======================================*/

void addStudent() {
    struct Student s;

    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll (letters allowed): ");
    scanf("%s", s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);

    fprintf(fp, "%s %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("\n==== Student Records ====\n");
    while (fscanf(fp, "%s %s %f %c", s.roll, s.name, &s.marks, &s.grade) == 4) {
        printf("Roll: %s | Name: %s | Marks: %.2f | Grade: %c\n",
               s.roll, s.name, s.marks, s.grade);
    }

    fclose(fp);
}

void searchStudent() {
    char roll[20];
    int found = 0;
    struct Student s;

    printf("Enter Roll to Search: ");
    scanf("%s", roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    while (fscanf(fp, "%s %s %f %c", s.roll, s.name, &s.marks, &s.grade) == 4) {
        if (strcmp(s.roll, roll) == 0) {
            printf("Record Found!\n");
            printf("Roll: %s | Name: %s | Marks: %.2f | Grade: %c\n",
                   s.roll, s.name, s.marks, s.grade);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    char roll[20];
    int found = 0;
    struct Student s;

    printf("Enter Roll to Update: ");
    scanf("%s", roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening files!\n");
        return;
    }

    while (fscanf(fp, "%s %s %f %c", s.roll, s.name, &s.marks, &s.grade) == 4) {
        if (strcmp(s.roll, roll) == 0) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            s.grade = calculateGrade(s.marks);
        }
        fprintf(temp, "%s %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Student Not Found!\n");
}

void deleteStudent() {
    char roll[20];
    int found = 0;
    struct Student s;

    printf("Enter Roll to Delete: ");
    scanf("%s", roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(fp, "%s %s %f %c", s.roll, s.name, &s.marks, &s.grade) == 4) {
        if (strcmp(s.roll, roll) == 0) {
            found = 1;
            continue;
        }
        fprintf(temp, "%s %s %.2f %c\n", s.roll, s.name, s.marks, s.grade);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}

/* ======================================
            SORTING STUDENTS
======================================*/

void sortStudents() {
    struct Student s[100];
    int count = 0, choice;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No records to sort!\n");
        return;
    }

    while (fscanf(fp, "%s %s %f %c", s[count].roll, s[count].name,
                  &s[count].marks, &s[count].grade) == 4) {
        count++;
    }
    fclose(fp);

    printf("\nSort Options:\n");
    printf("1. Sort by Roll (A–Z)\n");
    printf("2. Sort by Marks (High to Low)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {

            int swap = 0;

            if (choice == 1 && strcmp(s[i].roll, s[j].roll) > 0)
                swap = 1;

            else if (choice == 2 && s[i].marks < s[j].marks)
                swap = 1;

            if (swap) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n===== SORTED LIST =====\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %s | Name: %s | Marks: %.2f | Grade: %c\n",
               s[i].roll, s[i].name, s[i].marks, s[i].grade);
    }
}
