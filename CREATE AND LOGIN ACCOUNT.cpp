#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#define ACC_FILE "accounts.txt"
#define TEMP_FILE "accounts_tmp.txt"

struct Account {
    char username[50];
    char password[100];
    char role[20];
    char course[50];
    char firstName[50];
    char lastName[50];
    char Department[100];
    char idNumber[30];
    char email[100];
    char address[200];
};


void menu();
int createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *pass);
void loadingScreen();
void clear_stdin();
void generateId(const char* role, const char* department, char* idNumber);
void deleteAllUserData();

void BSOA_Regular_Schedule();
void EDUC_Regular_Schedule();


void studentDashboard(struct Account *acc);
void facultyDashboard(struct Account *acc);
void adminDashboard(struct Account *acc);


void showStudentProfile(struct Account *acc);
void showFacultyProfile(struct Account *acc);
void editProfile(struct Account *acc);
int updateAccountInFile(struct Account *acc); 
int changePasswordAccount(struct Account *acc);
void viewAllAccounts();


void sanitize_for_csv(char *s);

int main() {
    menu();
    return 0;
}



void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while ((ch = getch()) != 13) { 
        if (ch == 8 && i > 0) { 
            printf("\b \b");
            i--;
        } else if (ch >= 32 && ch <= 126 && i < 99) {
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
    for (i = 0; i <= 40; i++) {
        printf("%c", 219);
        Sleep(20);
    }
    printf(" 100%%\n");
}

void sanitize_for_csv(char *s) {
  
    for (int i = 0; s[i]; ++i) {
        if (s[i] == ',') s[i] = ';';
    }
}



void generateId(const char* role, const char* department, char* idNumber) {
    static int seeded = 0;
    if (!seeded) { srand((unsigned int)time(NULL)); seeded = 1; }
    int randomNum = rand() % 900000 + 100000; // six-digit

    if (strcmp(role, "Student") == 0) {
        if (strstr(department, "BSCS") || strstr(department, "COMPUTER") || strstr(department, "CS"))
            sprintf(idNumber, "STU-CS-%06d", randomNum);
        else if (strstr(department, "BSOA") || strstr(department, "OFFICE") || strstr(department, "OA"))
            sprintf(idNumber, "STU-OA-%06d", randomNum);
        else if (strstr(department, "BSVTVTED") || strstr(department, "ED") || strstr(department, "TEACH"))
            sprintf(idNumber, "STU-ED-%06d", randomNum);
        else
            sprintf(idNumber, "STU-GEN-%06d", randomNum);
    } else if (strcmp(role, "Faculty") == 0) {
        if (strstr(department, "COMPUTER") || strstr(department, "CS"))
            sprintf(idNumber, "FAC-CS-%06d", randomNum);
        else if (strstr(department, "OFFICE") || strstr(department, "OA"))
            sprintf(idNumber, "FAC-OA-%06d", randomNum);
        else if (strstr(department, "TEACHER") || strstr(department, "ED"))
            sprintf(idNumber, "FAC-ED-%06d", randomNum);
        else
            sprintf(idNumber, "FAC-GEN-%06d", randomNum);
    } else { // Admin
        sprintf(idNumber, "ADM-%06d", randomNum % 999999);
    }
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
        printf("|           [4]DeleteAllData                        |\n");
        printf("|           [5] Exit                                |\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice: ");
        choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1': createAccount(); break;
            case '2': loginAccount(); break;
            case '3': forgotPassword(); break;
            case '4': void deleteAllUserData(); break;
            case '5':
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\n? Invalid input! Please press any key to try again.\n");
                getch();
                continue;
        }

        printf("\nPress any key to return to main menu...");
        getch();
    }
}



int createAccount() {
    char firstName[50], lastName[50], birthD[20], sex[10], address[200], email[100];
    char username[50], password[100], confirmPassword[100];
    char role[20], course[50], department[100];
    char idNumber[30];
    FILE *fp;

 
    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                       * --------------------- / ---------------- /                       [ 9 ] Back  |\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter firstname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", firstName) != 1) { clear_stdin(); continue; }

        if (strcmp(firstName, "9") == 0) return 0;

        if (strlen(firstName) < 2) {
            printf("\n(System): Firstname too short! Try again.\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter lastname:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", lastName) != 1) { clear_stdin(); continue; }
        if (strcmp(lastName, "9") == 0) return 0;
        if (strlen(lastName) < 2) {
            printf("\n(System): Lastname too short! Try again.\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Date of Birth (DD/MM/YYYY):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", birthD) != 1) { clear_stdin(); continue; }
        if (strcmp(birthD, "9") == 0) return 0;
        if (strlen(birthD) != 10 || birthD[2] != '/' || birthD[5] != '/') {
            printf("\n(System): Invalid date format! Use DD/MM/YYYY\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Sex at Birth (Male/Female):\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", sex) != 1) { clear_stdin(); continue; }
        if (strcmp(sex, "9") == 0) return 0;
        sex[0] = toupper(sex[0]);
        for (int i = 1; sex[i]; i++) sex[i] = tolower(sex[i]);
        if (strcmp(sex, "Male") != 0 && strcmp(sex, "Female") != 0) {
            printf("\n(System): Please enter either 'Male' or 'Female'\n");
            getch();
            continue;
        }
        break;
    }


    clear_stdin();
    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Home Address:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = 0;
        if (strcmp(address, "9") == 0) return 0;
        if (strlen(address) < 3) {
            printf("\n(System): Address too short!\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Personal Information\n\n");

        printf("\n\n                                  Enter Email:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", email) != 1) { clear_stdin(); continue; }
        if (strcmp(email, "9") == 0) return 0;
        if (!strchr(email, '@') || !strchr(email, '.')) {
            printf("\n(System): Invalid email format!\n");
            getch();
            continue;
        }
        break;
    }


    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Account Information\n\n");

        printf("\n\n                                  Create Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (scanf(" %[^\n]", username) != 1) { clear_stdin(); continue; }
        if (strcmp(username, "9") == 0) return 0;
        if (strlen(username) < 4) {
            printf("\n(System): Username too short!\n");
            getch();
            continue;
        }

        fp = fopen(ACC_FILE, "r");
        if (fp) {
            struct Account tmp;
            int exists = 0;
            while (fscanf(fp,
                "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
                tmp.username, tmp.password, tmp.role, tmp.course, tmp.firstName,
                tmp.lastName, tmp.Department, tmp.idNumber, tmp.email, tmp.address) == 10) {
                if (strcmp(tmp.username, username) == 0) { exists = 1; break; }
            }
            fclose(fp);
            if (exists) {
                printf("\n(System): Username already exists!\n");
                getch();
                continue;
            }
        }
        break;
    }

 
    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Account Information\n\n");

        printf("\n\n                                  Create Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);
        if (strlen(password) < 4) {
            printf("\n(System): Password too short!\n");
            getch();
            continue;
        }
        printf("\n                                  Confirm Password: ");
        inputPassword(confirmPassword);
        if (strcmp(password, confirmPassword) != 0) {
            printf("\n(System): Passwords do not match!\n");
            getch();
            continue;
        }
        break;
    }

 
    while (1) {
        system("cls");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                              Personal Information     Account information     Position                               |\n");
        printf("                  +======================================================================================================================+\n\n");
        printf("                                                                   Position Selection\n\n");

        printf("\n\n                                  Role (Student/Faculty/Admin): ");
        if (scanf(" %[^\n]", role) != 1) { clear_stdin(); continue; }
        if (strcmp(role, "9") == 0) return 0;
        role[0] = toupper(role[0]);
        for (int i = 1; role[i]; i++) role[i] = tolower(role[i]);

        if (strcmp(role, "Student") != 0 && strcmp(role, "Faculty") != 0 && strcmp(role, "Admin") != 0) {
            printf("\n(System): Please enter 'Student', 'Faculty', or 'Admin'.\n");
            getch();
            continue;
        }

        if (strcmp(role, "Faculty") == 0) {
            printf("\nSelect Department:\n[C] COMPUTER SCIENCE\n[O] OFFICE ADMIN\n[T] TEACHER EDUCATION\n");
            char ch = getch();
            if (ch == 'c' || ch == 'C') strcpy(department, "COMPUTER SCIENCE DEPARTMENT");
            else if (ch == 'o' || ch == 'O') strcpy(department, "OFFICE ADMINISTRATION DEPARTMENT");
            else if (ch == 't' || ch == 'T') strcpy(department, "TEACHER EDUCATION DEPARTMENT");
            else continue;
            strcpy(course, "-");
        } else if (strcmp(role, "Student") == 0) {
            printf("\nSelect Course:\n[1] BSCS\n[2] BSOA\n[3] BSVTVTED\n");
            char ch = getch();
            if (ch == '1') strcpy(course, "BSCS");
            else if (ch == '2') strcpy(course, "BSOA");
            else if (ch == '3') strcpy(course, "BSVTVTED");
            else continue;
            strcpy(department, "-");
        } else {
            strcpy(course, "-");
            strcpy(department, "-");
        }
        break;
    }

 
    sanitize_for_csv(address);
    sanitize_for_csv(email);

 
    generateId(role, (strcmp(role, "Student") == 0) ? course : department, idNumber);
    loadingScreen();

    fp = fopen(ACC_FILE, "a");
    if (!fp) {
        printf("\n(System): Error opening file for writing!\n");
        return 0;
    }

 
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            username, password, role, course, firstName, lastName,
            department, idNumber, email, address);
    fclose(fp);

    printf("\n(System): Account created and saved successfully!\n");
    printf("Username: %s\nRole: %s\nGenerated ID: %s\n", username, role, idNumber);
    printf("\nPress any key to continue...");
    getch();
    return 0;
}

 

void loginAccount() {
    struct Account acc;
    char username[50], password[100], inputId[50];
    FILE *fp;
    int attempts = 0;

    while (attempts < 3) {
        system("cls");
        fp = fopen(ACC_FILE, "r");
        if (fp == NULL) {
            printf("\n(System): No accounts found. Please create one first.\n");
            getch();
            return;
        }

        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                                   PHILTECH GATEWAY                                                   |\n");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("                  |                                         ACCOUNT LOGIN SECTION                                                        |\n");
        printf("                  +======================================================================================================================+\n");

        printf("\n\n                                  Enter Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        clear_stdin();
        if (!fgets(username, sizeof(username), stdin)) username[0] = '\0';
        username[strcspn(username, "\n")] = 0;

        printf("\n\n                                  Enter Password:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        inputPassword(password);

        printf("\n\n                                  Enter Generated ID:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        if (!fgets(inputId, sizeof(inputId), stdin)) inputId[0] = '\0';
        inputId[strcspn(inputId, "\n")] = 0;

        int foundUser = 0, passwordMatch = 0, idMatch = 0;
        rewind(fp);
        while (fscanf(fp,
            "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
            acc.username, acc.password, acc.role, acc.course, acc.firstName,
            acc.lastName, acc.Department, acc.idNumber, acc.email, acc.address) == 10) {

            if (strcmp(username, acc.username) == 0) {
                foundUser = 1;
                if (strcmp(password, acc.password) == 0)
                    passwordMatch = 1;
                if (strcmp(inputId, acc.idNumber) == 0)
                    idMatch = 1;
                break;
            }
        }
        fclose(fp);

        if (!foundUser) {
            printf("\n(System): Username not found!\n");
            attempts++;
        } else if (!passwordMatch) {
            printf("\n(System): Incorrect password!\n");
            attempts++;
        } else if (!idMatch) {
            printf("\n(System): Invalid or incorrect ID!\n");
            attempts++;
        } else {
     
            printf("\n(System): Logging in...");
            Sleep(700);
            system("cls");
            loadingScreen();
            system("cls");

            if (strcmp(acc.role, "Student") == 0) {
                studentDashboard(&acc);
            } else if (strcmp(acc.role, "Faculty") == 0) {
                facultyDashboard(&acc);
            } else { // Admin
                adminDashboard(&acc);
            }
            return;
        }

        if (attempts < 3) {
            printf("\nAttempts left: %d\n", 3 - attempts);
            printf("Press any key to try again...");
            getch();
        } else {
            printf("\nToo many failed attempts. Returning to main menu...");
            Sleep(1200);
            return;
        }
    }
}

 

void forgotPassword() {
    struct Account acc;
    char username[50];
    int found = 0;
    FILE *fp = fopen(ACC_FILE, "r");

    if (fp == NULL) {
        printf("\n(System): No accounts found.\n");
        getch();
        return;
    }

    printf("\nEnter your username to recover password: ");
    clear_stdin();
    if (!fgets(username, sizeof(username), stdin)) username[0] = '\0';
    username[strcspn(username, "\n")] = 0;

    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        acc.username, acc.password, acc.role, acc.course, acc.firstName,
        acc.lastName, acc.Department, acc.idNumber, acc.email, acc.address) == 10) {
        if (strcmp(username, acc.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
        printf("\n(System): Your password is: %s\n", acc.password);
    else
        printf("\n(System): Username not found.\n");

    printf("Press any key to return...");
    getch();
}

  
  
int updateAccountInFile(struct Account *acc) {
    FILE *fp = fopen(ACC_FILE, "r");
    FILE *tmp = fopen(TEMP_FILE, "w");
    int replaced = 0;
    if (!tmp) return 0;
    if (!fp) {
        fclose(tmp);
        return 0;
    }

    struct Account tmpAcc;
    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        tmpAcc.username, tmpAcc.password, tmpAcc.role, tmpAcc.course, tmpAcc.firstName,
        tmpAcc.lastName, tmpAcc.Department, tmpAcc.idNumber, tmpAcc.email, tmpAcc.address) == 10) {

        if (strcmp(tmpAcc.username, acc->username) == 0) {
            
            sanitize_for_csv(acc->address);
            sanitize_for_csv(acc->email);
            fprintf(tmp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                acc->username, acc->password, acc->role, acc->course,
                acc->firstName, acc->lastName, acc->Department, acc->idNumber,
                acc->email, acc->address);
            replaced = 1;
        } else {
         
            sanitize_for_csv(tmpAcc.address);
            sanitize_for_csv(tmpAcc.email);
            fprintf(tmp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                tmpAcc.username, tmpAcc.password, tmpAcc.role, tmpAcc.course,
                tmpAcc.firstName, tmpAcc.lastName, tmpAcc.Department, tmpAcc.idNumber,
                tmpAcc.email, tmpAcc.address);
        }
    }

    fclose(fp);
    fclose(tmp);

    if (!replaced) {
      
        remove(TEMP_FILE);
        return 0;
    } else {
        // replace original file
        remove(ACC_FILE);
        rename(TEMP_FILE, ACC_FILE);
        return 1;
    }
}

 
 
int changePasswordAccount(struct Account *acc) {
    char oldpass[100], newpass[100], confirm[100];
    printf("Enter current password: ");
    inputPassword(oldpass);
    if (strcmp(oldpass, acc->password) != 0) {
        printf("\n(System): Current password incorrect.\n");
        getch();
        return 0;
    }
    while (1) {
        printf("Enter new password: ");
        inputPassword(newpass);
        if (strlen(newpass) < 4) {
            printf("(System): New password too short (min 4 chars).\n");
            getch();
            continue;
        }
        printf("Confirm new password: ");
        inputPassword(confirm);
        if (strcmp(newpass, confirm) != 0) {
            printf("(System): Passwords do not match. Try again.\n");
            getch();
            continue;
        }
        break;
    }
    
    strcpy(acc->password, newpass);
    if (updateAccountInFile(acc)) {
        printf("\n(System): Password changed successfully.\n");
        getch();
        return 1;
    } else {
        printf("\n(System): Failed to update password in file.\n");
        getch();
        return 0;
    }
}

 
void editProfile(struct Account *acc) {
    char newEmail[100], newAddress[200];
    system("cls");
    printf("=====================================================\n");
    printf("|                 EDIT PROFILE                      |\n");
    printf("=====================================================\n");
    printf("Current Email  : %s\n", acc->email);
    printf("Current Address: %s\n", acc->address);
    printf("-----------------------------------------------------\n");
    printf("Enter new email (or press enter to keep): ");
    clear_stdin();
    if (!fgets(newEmail, sizeof(newEmail), stdin)) newEmail[0] = '\0';
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Enter new address (or press enter to keep): ");
    if (!fgets(newAddress, sizeof(newAddress), stdin)) newAddress[0] = '\0';
    newAddress[strcspn(newAddress, "\n")] = 0;

    if (strlen(newEmail) > 0) {
        if (!strchr(newEmail, '@') || !strchr(newEmail, '.')) {
            printf("\n(System): Invalid email format. No changes made.\n");
            getch();
            return;
        }
        strncpy(acc->email, newEmail, sizeof(acc->email)-1);
        acc->email[sizeof(acc->email)-1] = '\0';
    }
    if (strlen(newAddress) > 0) {
        strncpy(acc->address, newAddress, sizeof(acc->address)-1);
        acc->address[sizeof(acc->address)-1] = '\0';
    }

    
    sanitize_for_csv(acc->email);
    sanitize_for_csv(acc->address);
    if (updateAccountInFile(acc)) {
        printf("\n(System): Profile updated successfully.\n");
    } else {
        printf("\n(System): Failed to update profile in file.\n");
    }
    printf("Press any key to return...");
    getch();
}

 

void showStudentProfile(struct Account *acc) {
    system("cls");
    printf("=====================================================\n");
    printf("|                 STUDENT PROFILE                   |\n");
    printf("=====================================================\n");
    printf("Name    : %s %s\n", acc->firstName, acc->lastName);
    printf("Username: %s\n", acc->username);
    printf("Email   : %s\n", acc->email);
    printf("Course  : %s\n", acc->course);
    printf("Department: %s\n", acc->Department);
    printf("ID      : %s\n", acc->idNumber);
    printf("Address : %s\n", acc->address);
    printf("Role    : %s\n", acc->role);
    printf("-----------------------------------------------------\n");
    printf("Press any key to return...");
    getch();
}

void showFacultyProfile(struct Account *acc) {
    system("cls");
    printf("=====================================================\n");
    printf("|                 FACULTY PROFILE                   |\n");
    printf("=====================================================\n");
    printf("Name    : %s %s\n", acc->firstName, acc->lastName);
    printf("Username: %s\n", acc->username);
    printf("Email   : %s\n", acc->email);
    printf("Department: %s\n", acc->Department);
    printf("ID      : %s\n", acc->idNumber);
    printf("Address : %s\n", acc->address);
    printf("Role    : %s\n", acc->role);
    printf("-----------------------------------------------------\n");
    printf("Press any key to return...");
    getch();
}

 

void studentDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|                  STUDENT DASHBOARD                 |\n");
        printf("=====================================================\n");
        printf("Welcome: %s %s\n", acc->firstName, acc->lastName);
        printf("Course : %s\n", acc->course);
        printf("ID     : %s\n", acc->idNumber);
        printf("-----------------------------------------------------\n");
        printf("[1] View Schedule\n");
        printf("[2] View Profile\n");
        printf("[3] Edit Profile\n");
        printf("[4] Change Password\n");
        printf("[5] Logout\n");
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            system("cls");
            if (strcmp(acc->course, "BSCS") == 0) {
                
                printf("Showing BSCS schedule...\n\n");
                EDUC_Regular_Schedule();
            } else if (strcmp(acc->course, "BSOA") == 0) {
                BSOA_Regular_Schedule();
            } else if (strcmp(acc->course, "BSVTVTED") == 0) {
                EDUC_Regular_Schedule();
            } else {
                printf("No schedule available for %s\n", acc->course);
            }
            printf("\nPress any key to return to dashboard...");
            getch();
        } else if (ch == '2') {
            showStudentProfile(acc);
        } else if (ch == '3') {
            editProfile(acc);
        } else if (ch == '4') {
            changePasswordAccount(acc);
        } else if (ch == '5') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
            printf("Invalid option. Press any key to try again...");
            getch();
        }
    }
}

void facultyDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|                 FACULTY DASHBOARD                  |\n");
        printf("=====================================================\n");
        printf("Welcome: %s %s\n", acc->firstName, acc->lastName);
        printf("Department: %s\n", acc->Department);
        printf("ID     : %s\n", acc->idNumber);
        printf("-----------------------------------------------------\n");
        printf("[1] View Teaching Schedule\n");
        printf("[2] View Profile\n");
        printf("[3] Edit Profile\n");
        printf("[4] Change Password\n");
        printf("[5] Logout\n");
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            system("cls");
            printf("Teaching schedule (sample):\n");
            printf("- Monday 8:00-10:00  COMP101 (Main)\n");
            printf("- Wednesday 10:00-12:00  COMP102 (Annex)\n");
            printf("- Friday 1:00-3:00  LAB (Main)\n");
            printf("\nPress any key to return...");
            getch();
        } else if (ch == '2') {
            showFacultyProfile(acc);
        } else if (ch == '3') {
            editProfile(acc);
        } else if (ch == '4') {
            changePasswordAccount(acc);
        } else if (ch == '5') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
            printf("Invalid option. Press any key to try again...");
            getch();
        }
    }
}

void viewAllAccounts() {
    FILE *fp = fopen(ACC_FILE, "r");
    if (!fp) {
        printf("\n(System): No accounts file found!\n");
        getch();
        return;
    }
    struct Account tmp;
    int idx = 0;
    system("cls");
    printf("=====================================================\n");
    printf("|                  ALL ACCOUNTS                      |\n");
    printf("=====================================================\n");
    printf("No.  Username         Role      Course    ID\n");
    printf("-----------------------------------------------------\n");
    while (fscanf(fp,
        "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
        tmp.username, tmp.password, tmp.role, tmp.course, tmp.firstName,
        tmp.lastName, tmp.Department, tmp.idNumber, tmp.email, tmp.address) == 10) {
        idx++;
        printf("%-4d %-16s %-9s %-8s %s\n", idx, tmp.username, tmp.role, tmp.course, tmp.idNumber);
        if (idx % 20 == 0) {  
            printf("\nPress any key to continue...");
            getch();
            system("cls");
        }
    }
    fclose(fp);
    if (idx == 0) printf("No accounts found.\n");
    printf("\nPress any key to return...");
    getch();
}
void deleteAllUserData() {
    FILE *fp = fopen("accounts.txt", "w");
    if (!fp) {
        printf("\n(System): Failed to open accounts file.\n");
        getch();
        return;
    }
    fclose(fp);
    printf("\n(System): All user data deleted successfully!\n");
    getch();
}

void adminDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("=====================================================\n");
        printf("|                   ADMIN DASHBOARD                  |\n");
        printf("=====================================================\n");
        printf("Welcome Admin: %s %s\n", acc->firstName, acc->lastName);
        printf("ID: %s\n", acc->idNumber);
        printf("-----------------------------------------------------\n");
        printf("[1] View All Accounts\n");
        printf("[2] Change Password\n");
        printf("[3] Logout\n");
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewAllAccounts();
        } else if (ch == '2') {
            changePasswordAccount(acc);
        } else if (ch == '3') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
            printf("Invalid option. Press any key to try again...");
            getch();
        }
    }
}

 

void BSOA_Regular_Schedule() {
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|                                              WEEKLY SCHEDULE                                                   |Ã—|\n");
	printf("                     |Ã—|                                             COURSE: BSOA SECOND YEAR                                           |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|          âŒ‡     âŒ‡     âŒ‡     âŒ‡     âŒ‡     âŒ‡     âŒ‡     âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡      âŒ‡   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    7:00-8:00    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:00-8:45    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |               |               |               |               |Ã—|\n");   
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:45-9:00    |                                  BREAK TIME                                                  |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|   9:00-10:00    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              | QACC215 402-  |               |               |               |               |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã— MAIN          Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|   10;00-10:45   |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|   10:45-11:15   |                                  LUNCH BREAK                                                 |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|   11:15-12:00   |              |  QACC215 402- |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |  MAIN         |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    12:00-1:00   |              |               |               |               |               |               |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—               Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    1:00-2:00    |              | GE5 403-      |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã— MAIN          |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~| CSME1 403     |~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    2:00-2:45    |              |               | QACC104 403   |               | MAIN          |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               | MAIN          |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    2:45-3:00    |                                  BREAK TIME                                                  |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    3:00-4:00    |              |               |               |               |  CSME1 403    |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |               |               |  MAIN         |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã— QACC104 403   Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    4:00-4:45    |              |               | MAIN          |               |  GE6 403      |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |               |               |  MAIN         |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    4:45-5:15    |                                  BREAK TIME                                                  |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    5:15-6:00    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã— PATHFIT3 405  Ã— VAL 403       Ã—~~~~~~~~~~~~~~~Ã—  GE6 403      Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    6:00-7:00    |              | MAIN.         | MAIN          |               |  MAIN         |               |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");


    
    
    
    
    }
    

void EDUC_Regular_Schedule() {
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|                                              WEEKLY SCHEDULE                                                   |Ã—|\n");
	printf("                     |Ã—|                                              COURSE: BSOA                                                      |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|          ?     ?     ?     ?     ?     ?     ?     ?      ?      ?      ?      ?      ?      ?      ?      ?      ?   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~~~Ã—~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    7:00-8:00    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:00-8:45    |              |               |               |               |               |  NSTP1 404-   |Ã—|\n");
    printf("                     |Ã—|                 |              |               |               |               |               |  ROOM  MAIN   |Ã—|\n");   
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:45-9:00    |                                  BREAK TIME                                                  |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|   9:00-10:00    |              |               |               |               |               |  NSTP1 404-   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—  ROOM MAIN    |Ã—|\n");
    printf("                     |Ã—|   10;00-10:45   |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|   10:45-11:15   |                                  LUNCH BREAK                                                 |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|   11:15-12:00   |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—  GE104 104-   Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—  GE101 404-   |Ã—|\n");
	printf("                     |Ã—|    12:00-1:00   |              |               |  ANNEX        |               |               |  MAIN.        |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—               Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—               |Ã—|\n");
	printf("                     |Ã—|    1:00-2:00    |              | QACC102LEC    |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã— 411-MAIN      |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    2:00-2:45    |              |               | PATHFIT 104   |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               | ANNEX         |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    2:45-3:00    |                                  BREAK TIME                                                  |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    3:00-4:00    |  PLS 102     |               | PATHFIT 104   |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |  ANNEX       | QACc102LEC    | ANNEX         |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã— CL2-MAIN      Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    4:00-4:45    | QACC101 102- |               | GE2 104       |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 | ANNEX        |               | ANNEX         |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    4:45-5:15    |                                  BREAK TIME                                                  |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    5:15-6:00    | QACC101 102- | QACC102LEC    | GE2 104       |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 | ANNEX        | ANNEX         | ANNEX         |               |               |               |Ã—|\n");
    printf("                     |Ã—|    6:00-7:00    |              |               |               |               |               |               |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~Ã—~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}



