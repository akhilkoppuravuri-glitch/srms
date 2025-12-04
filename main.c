#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
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

int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied! Exiting...\n");
    }
    return 0;
}

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

        // FIXED: == instead of =
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

/* ======================================
                ADMIN MENU
======================================*/
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ======================================
                USER MENU
======================================*/
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ======================================
                STAFF MENU
    Staff can add & search, but NOT delete
======================================*/
void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ======================================
                GUEST MENU
======================================*/
void guestMenu() {
    int choice;
    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
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

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
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
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int roll, found = 0;
    struct Student s;

    printf("Enter Roll to Search: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            printf("Record Found!\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    int roll, found = 0;
    struct Student s;

    printf("Enter Roll to Update: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening files!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
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
    int roll, found = 0;
    struct Student s;

    printf("Enter Roll to Delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
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
