#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>   // For Sleep()

struct Account {
    char username[50];
    char password[50];
    char role[20];
    char course[20];
};

void menu();
void createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *pass);
void loadingScreen();

int main() {
    menu();
    return 0;
}

void menu() {
    char choice;

    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|          PHILTECH SCHOOL MANAGEMENT SYSTEM        |\n");
        printf("=====================================================\n");
        printf("|           [1] Create Account                      |\n");
        printf("|           [2] Login                               |\n");
        printf("|           [3] Forgot Password                     |\n");
        printf("|           [4] Exit                                |\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice: ");
        choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1': createAccount(); break;
            case '2': loginAccount(); break;
            case '3': forgotPassword(); break;
            case '4':
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\n❌ Invalid input! Please press any key to try again.\n");
                getch();
                continue;
        }

        printf("\nPress any key to return to main menu...");
        getch();
    }
}

void createAccount() {
    struct Account acc;
    FILE *fp;
    char roleChoice, courseChoice;

    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|                 CREATE ACCOUNT                    |\n");
        printf("|===================================================|\n");
        printf("|          [1] Student                              |\n");
        printf("|          [2] Teacher                              |\n");
        printf("|          [3] Admin (Registrar, Administrator)     |\n");
        printf("|          [4] Back to Menu                         |\n");
        printf("=====================================================\n");
        printf("Select role: ");
        roleChoice = getch();
        printf("%c\n", roleChoice);

        if (roleChoice == '4') return;

        switch (roleChoice) {
            case '1': 
                strcpy(acc.role, "Student");

                while (1) {
                    printf("============================================");
                    printf("\n|           Select your course             |\n");
                    printf("|         [1] BSCS                         |\n");
                    printf("|         [2] BSOA                         |\n");
                    printf("|         [3] BTVTED                       |\n");
                    printf("--------------------------------------------\n");
                    printf("Enter course: ");
                    courseChoice = getch();
                    printf("%c\n", courseChoice);

                    if (courseChoice == '1') strcpy(acc.course, "BSCS");
                    else if (courseChoice == '2') strcpy(acc.course, "BSOA");
                    else if (courseChoice == '3') strcpy(acc.course, "BTVTED");
                    else {
                        printf("\n❌ Invalid course! Try again.\n");
                        getch();
                        continue;
                    }
                    break;
                }
                break;

            case '2':
                strcpy(acc.role, "Teacher");
                strcpy(acc.course, "N/A");
                break;

            case '3':
                strcpy(acc.role, "Admin");
                strcpy(acc.course, "N/A");
                break;

            default:
                printf("\n❌ Invalid role! Try again.\n");
                getch();
                continue;
        }

        printf("\nEnter username: ");
        fgets(acc.username, sizeof(acc.username), stdin);
        acc.username[strcspn(acc.username, "\n")] = 0;

        printf("Enter password: ");
        inputPassword(acc.password);

        fp = fopen("accounts.txt", "a");
        if (fp == NULL) {
            printf("\nError opening file!\n");
            return;
        }

        fprintf(fp, "%s,%s,%s,%s\n", acc.username, acc.password, acc.role, acc.course);
        fclose(fp);

        printf("\nSaving your account...\n");
        loadingScreen();

        printf("\n✅ Account created successfully!\n");
        break;
    }
}

void loginAccount() {
    struct Account acc;
    char username[50], password[50];
    int foundUser = 0, passwordMatch = 0, attempts = 0;
    FILE *fp;

    while (attempts < 3) {
        system("cls");
        fp = fopen("accounts.txt", "r");
        if (fp == NULL) {
            printf("\n⚠ No accounts found. Please create one first.\n");
            return;
        }

        printf("=====================================================\n");
        printf("|                    LOGIN ACCOUNT                  |\n");
        printf("=====================================================\n");

        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Enter password: ");
        inputPassword(password);

        foundUser = 0;
        passwordMatch = 0;

        while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%19[^\n]\n",
                      acc.username, acc.password, acc.role, acc.course) == 4) {
            if (strcmp(username, acc.username) == 0) {
                foundUser = 1;
                if (strcmp(password, acc.password) == 0) {
                    passwordMatch = 1;
                }
                break;
            }
        }
        fclose(fp);

        if (!foundUser) {
            printf("\n❌ Username not found. Please try again.\n");
            attempts++;
        } else if (!passwordMatch) {
            printf("\n❌ Incorrect password. Please try again.\n");
            attempts++;
        } else {
            printf("\nLogging in...\n");
            loadingScreen();
            printf("\n✅ Login successful! Welcome, %s (%s)", acc.username, acc.role);
            if (strcmp(acc.role, "Student") == 0)
                printf(" - %s", acc.course);
            printf("\n");
            return;
        }

        if (attempts < 3) {
            printf("\nAttempts left: %d\n", 3 - attempts);
            printf("Press any key to try again...");
            getch();
        } else {
            printf("\n🚫 Too many failed attempts. Returning to main menu...\n");
            Sleep(2000);
            return;
        }
    }
}

void forgotPassword() {
    struct Account acc;
    char username[50];
    int found = 0;
    FILE *fp = fopen("accounts.txt", "r");

    if (fp == NULL) {
        printf("\n⚠ No accounts found.\n");
        return;
    }

    printf("\nEnter your username to recover password: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    while (fscanf(fp, "%49[^,],%49[^,],%19[^,],%19[^\n]\n",
                  acc.username, acc.password, acc.role, acc.course) == 4) {
        if (strcmp(username, acc.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("\n🔑 Your password is: %s\n", acc.password);
    else
        printf("\n❌ Username not found.\n");
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) { // Enter key
        if (ch == 8 && i > 0) {    // Backspace
            printf("\b \b");
            i--;
        } else if (ch != 8) {
            pass[i++] = ch;
            printf("*");
        }
    }
    pass[i] = '\0';
    printf("\n");
}


void loadingScreen() {
    int i;
    printf("Loading: ");
    for (i = 0; i <= 20; i++) {
        printf("%c", 219); 	
        Sleep(100);        
    }
    printf(" 100%%\n");
}
