
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


void addFacultySchedule();
void menu();
int createAccount();
void loginAccount();
void forgotPassword();
void inputPassword(char *pass);
void loadingScreen();
void clear_stdin();
void generateId(const char* role, const char* department, char* idNumber);
void deleteAllUserData();

void BSCS1_Regular_Schedule();
void BSOA_Regular_Schedule();
void EDUC_Regular_Schedule();

void enrollmentForm();
void aboutUs(struct Account *acc);
void registrarDash(struct Account *acc);
void studentDashboard(struct Account *acc);
void facultyDashboard(struct Account *acc);
void adminDashboard(struct Account *acc);


void viewTeachingSchedule(struct Account *acc);
void FacultList();
void viewAttendance();
void showStudentProfile(struct Account *acc);
void showFacultyProfile(struct Account *acc);
void editProfile(struct Account *acc);
int updateAccountInFile(struct Account *acc); 
int changePasswordAccount(struct Account *acc);
void viewAllAccounts();
void invalid_StudentID_Display();
void invalid_Display();
void usernotfound();
void noaccfound();
void invalidUser();
void invalid_Option();



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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                 Loading: ");
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
    int randomNum = rand() % 900000 + 100000; 

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
    } else if (strcmp(role, "Admin")==0){
    	if (strstr(department, "Registrar") || strstr(department, "RGR"))
    	sprintf(idNumber,"ADM-RGR-%06d", randomNum);
	}else 
        sprintf(idNumber, "ADM-%06d", randomNum % 999999);
    }




void menu() {
    char choice;
    while (1) {
        system("cls");
        printf("\033[36;5m");
      system("color E9");
    printf("                  [-]********************************************************************************************************************[-]\n");
    printf("                  [-]                                                                                                                    [-]\n");
    printf("                  [-]                                           P   H   I   L   T   E   C   H                                            [-]\n");
    printf("                  [-]                                                                                                                    [-]\n");
    printf("                  [-]====================================================================================================================[-]\n");
    printf("                  [-]||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]====================================================================================================================[-]\n");
    printf("                  [-]********************************************************************************************************************[-]\n");    
    printf("                  [-]                                                                                                                    [-]\n");
	printf("                  [-]                          ++_________________________________________________________++                             [-]\n");
	printf("                  [-]                          ++                                                         ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]  [1]   CREATE ACCOUNT      [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [2]   LOGIN              [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [3]   FORGET PASSWORD    [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [4]   DELETE ALL DATA    [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
    printf("                  [-]                          ++             [-]                          [-]            ++                             [-]\n");
 	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");
	printf("                  [-]                          ++      ++   [-]   [5]   EXIT               [-]    ++      ++                             [-]\n");    
	printf("                  [-]                          ++      ++   [-]                            [-]    ++      ++                             [-]\n");    
	printf("                  [-]                          ++      ++=========================================++      ++                             [-]\n");    
	printf("                  [-]                          ++      +++++++++++++++++++++++++++++++++++++++++++++      ++                             [-]\n");    
	printf("                  [-]                          ++                                                         ++                             [-]\n");    
	printf("                  [-]                          ++_________________________________________________________++                             [-]\n");    
	printf("                  [-]                                                                                                                    [-]\n");    
    printf("                  [-]                                                                                                                    [-]\n");
	printf("                  [-]********************************************************************************************************************[-]\n");
	printf("                  [-]====================================================================================================================[-]\n");
	 printf("Enter your choice: ");
        choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1': createAccount(); break;
            case '2': loginAccount(); break;
            case '3': forgotPassword(); break;
            case '4':  deleteAllUserData(); break;
            case '5':
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
            	system("cls");
                invalid_Display();
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
        printf("\033[36;5m");
       printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
       printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
        printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
        printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
        printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
        printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
       printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
        printf("\033[36;5m");
        printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
printf("                                                                   Personal Information\n\n");

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
        printf("\033[36;5m");
        printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
printf("                                                                   Personal Information\n\n");

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
        printf("\n                                  Confirm Password: \n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
        
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
        printf("\033[36;5m");
       printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                               P   H   I   L   T   E   C   H       G   A   T   E                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Personal Information                                                                                      ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Account information                                                                                       ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                Position                                                                                                  ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||                                                                                                                          ||\n");
printf("          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
printf("                                                                   Personal Information\n\n");

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
        	printf("\033[36;5m");
        	printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]           S   E   L   E   C   T     D   E   P   A   R   T   M   E   N   T             [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n"); 
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [C] COMPUTER SCIENCE                                              [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [O] OFFICE ADMIN                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [T] TEACHER EDUCATION                                             [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                                                                                       [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            printf("                                  ======================================================\n");
            char ch = getch();
            if (ch == 'c' || ch == 'C') strcpy(department, "COMPUTER SCIENCE DEPARTMENT");
            else if (ch == 'o' || ch == 'O') strcpy(department, "OFFICE ADMINISTRATION DEPARTMENT");
            else if (ch == 't' || ch == 'T') strcpy(department, "TEACHER EDUCATION DEPARTMENT");
            else continue;
            strcpy(course, "-");
        } else if (strcmp(role, "Student") == 0) {
        	printf("\033[36;5m");
        	printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                    S   E   L   E   C   T     C   O  U   R   S   E                      [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n"); 
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] BSCS                                                          [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] BSOA                                                          [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [3] BTVTED                                                        [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                                                                                       [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            char ch = getch();
            if (ch == '1') strcpy(course, "BSCS");
            else if (ch == '2') strcpy(course, "BSOA");
            else if (ch == '3') strcpy(course, "BSVTVTED");
            else continue;
            strcpy(department, "-");
        } else if (strcmp(role, "Admin") == 0) {
            printf("\033[36;5m");
            printf("                  [-]***************************************************************************************[-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]           S   E   L   E   C   T     D   E   P   A   R   T   M   E   N   T             [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]=======================================================================================[-]\n");
            printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
            printf("                  [-]=======================================================================================[-]\n");
            printf("                  [-]***************************************************************************************[-]\n");
            printf("                  [-]                                                                                       [-]\n"); 
            printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                     [A] Administration                                               [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                     [R] Registrar                                                    [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
            printf("                  [-]                                                                                       [-]\n");
            printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
            char ch = getch();
            if (ch == 'a' || ch == 'A') strcpy(department, "Administration");
            else if (ch == 'r' || ch == 'R') strcpy(department, "Registrar");
            else continue;
            strcpy(course, "-");
        }
        break;
    }

 
    sanitize_for_csv(address);
    sanitize_for_csv(email);

 
    generateId(role, (strcmp(role, "Student") == 0) ? course : department, idNumber);
    system("cls");
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

getch(); 

return 1;  
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
        usernotfound();

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
    printf("\033[36;5m");
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
    printf("\033[36;5m");
      system("color E9");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]             S   T   U   D   E   N   T     P   R   O   F   I   L   E                   [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
    printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       NAME    : %s %s\n", acc->firstName, acc->lastName);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       USERNAME: %s\n", acc->username);                  
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       EMAIL   : %s\n", acc->email);                     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       COURSE  : %s\n", acc->course);  
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       DEPARTMENT: %s\n", acc->Department);     
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                          ID   : %s\n", acc->idNumber);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                                       ADDRESS : %s\n", acc->address);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                   ROLE    : %s\n", acc->role);
	printf("                  [-]                                                                                       [-]\n");
    printf("                              ++      ++=========================================++      ++             \n");
 	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]                                                                                       [-]\n");    
	printf("                  [-]                                                                                       [-]\n");   
	printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");    
    getch();
}

void showFacultyProfile(struct Account *acc) {
    system("cls");
    printf("\033[36;5m");
    system("color E9");
      printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]             F   A   C   U   L   T   Y     P   R   O   F   I   L   E                   [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");    
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Name    : %s %s\n", acc->firstName, acc->lastName);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Username: %s\n", acc->username);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]           Email   : %s\n", acc->email);
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]           Department: %s\n", acc->Department);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]            ID      : %s\n", acc->idNumber);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]           Address : %s\n", acc->address);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]            Role    : %s\n", acc->role);
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
    getch();
}

 

void studentDashboard(struct Account *acc) {
    char ch;
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
     printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]          S   T   U   D   E   N   T     D   A   S   H   B   O   A   R   D              [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]           Welcome: %s %s   /n", acc->firstName, acc->lastName);
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]            Course : %s     /n", acc->course);
    printf("                  [-]                                                                                       [-]\n");    
	printf("                  [-]             ID     : %s     /n",  acc->idNumber);
	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [1] VIEW SCHEDULE                                                 [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [2] VIEW PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [3] EDIT PROFILE                                                  [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
	printf("                  [-]                     [4] ABOUT US                                                      [-]\n");
	printf("                  [-]                                                                                       [-]\n");
	printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [5] CHANGE PASSWORD                                               [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [6] CHANGE PASSWORD                                               [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
    printf("                  [-]                     [7] LOGOUT                                                        [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
   	printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
   	printf("                  [-]                                                                                       [-]\n");
    printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");  
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            system("cls");
            if (strcmp(acc->course, "BSCS") == 0) {
                
               
                BSCS1_Regular_Schedule();
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
        } else if (ch == '4'){
        	aboutUs(acc);
		}else if (ch == '5') {
            changePasswordAccount(acc);
        }else if (ch == '6'){
        	 enrollmentForm();
        	
		} else if (ch == '7') {
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else {
        	system("cls");
             invalid_Option();
            getch();
        }
    }
}






void facultyDashboard(struct Account *acc) {
    char ch;
    time_t time_in, time_out;  // Variables to store login and logout times
    
    // Record time in (login time) at the start of the function
    time(&time_in);
    
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        printf("                  [-]***************************************************************************************[-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         F   A   C   U   L   T   Y     D   A   S   H   B   O   A   R   D               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]***************************************************************************************[-]\n");    
        printf("                  [-]          Welcome Admin: %s %s                                                         [-]\n", acc->firstName, acc->lastName);
        printf("                  [-]            Department: %s                                                             [-]\n" , acc->Department);
        printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [1] VIEW TEACHING SCHEDULE                                        [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [2] VIEW PROFILE                                                  [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [3] EDIT PROFILE                                                  [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [4] ABOUT US                                                      [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [5] CHANGE PASSWORD                                               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [6] LOGOUT                                                        [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n"); 
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewTeachingSchedule(acc);
        } else if (ch == '2') {
            showFacultyProfile(acc);
        } else if (ch == '3') {
            editProfile(acc);
        } else if (ch == '4'){
            aboutUs(acc);
        } else if (ch == '5') {
            changePasswordAccount(acc);
        } else if (ch == '6') {
            // Record time out (logout time)
            time(&time_out);
            
            // Save time in and time out to a log file (e.g., time_log.txt)
            // This appends to the file; you can change the filename or path as needed
            FILE *fp = fopen("time_log.txt", "a");
            if (fp != NULL) {
                // Use ctime to convert time_t to a readable string
                // ctime includes a newline, so we trim it for better formatting
                char *time_in_str = ctime(&time_in);
                char *time_out_str = ctime(&time_out);
                if (time_in_str[strlen(time_in_str) - 1] == '\n') time_in_str[strlen(time_in_str) - 1] = '\0';
                if (time_out_str[strlen(time_out_str) - 1] == '\n') time_out_str[strlen(time_out_str) - 1] = '\0';
                
                fprintf(fp, "ID: %s, Time In: %s, Time Out: %s\n", acc->idNumber, time_in_str, time_out_str);
                fclose(fp);
            } else {
                // Optional: Handle file open error (e.g., print a message)
                printf("Error: Could not open time log file.\n");
            }
            
            printf("Logging out...\n");
            Sleep(600);
            return;

        } else {
            system("cls");
            invalid_Option();
            getch();
        }
    }
}

// New function to view teaching schedule for the logged-in faculty
void viewTeachingSchedule(struct Account *acc) {
    char line[256];
    char facultyName[100];
    int found = 0;
    
    // Construct faculty name (assuming handle is firstName + " " + lastName)
    sprintf(facultyName, "%s %s", acc->firstName, acc->lastName);
    
    system("cls");
    printf("Your Teaching Schedule\n");
    printf("======================\n");
    
    FILE *fp = fopen("faculty_schedule.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open faculty_schedule.txt. No schedules found.\n");
        printf("Press any key to return...\n");
        getch();
        return;
    }
    
    while (fgets(line, sizeof(line), fp)) {
        // Check if the line contains the faculty's handle
        if (strstr(line, facultyName) != NULL) {
            // Parse and display the schedule details
            char subject[100], handle[100], time[100], room[100];
            if (sscanf(line, "Subject: %[^,], Handle: %[^,], Time: %[^,], Room: %s", subject, handle, time, room) == 4) {
                printf("Subject: %s\n", subject);
                printf("Time: %s\n", time);
                printf("Room: %s\n", room);
                printf("------------------------\n");
                found = 1;
            }
        }
    }
    fclose(fp);
    
    if (!found) {
        printf("No teaching schedules found for you (%s).\n", facultyName);
    }
    
    printf("Press any key to return to the dashboard...\n");
    getch();
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
    printf("\033[36;5m");
    printf("=====================================================\n");
    printf("|                  ALL ACCOUNTS                      |\n");
    printf("=====================================================\n");
    printf("No.  Username    |     Role   |   Course   | ID\n");
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
    time_t time_in, time_out;  // Variables to store login and logout times
    
    // Record time in (login time) at the start of the function
    time(&time_in);
    
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        printf("                  [-]***************************************************************************************[-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]                A   D   M   I   N     D   A   S   H   B   O   A   R   D                [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]***************************************************************************************[-]\n");    
        printf("                  [-]          Welcome Admin: %s %s                                                         [-]\n", acc->firstName, acc->lastName);                     
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);                                                                
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [1] VIEW ALL ACOOUNT                                              [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [2] CHANGE PASSWORD                                               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [3] LOGOUT                                                        [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [4] VIEW ATTENDANCE                                               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [5] ABOUT                                                         [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [6] FACULTY LIST                                                  [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewAllAccounts();
        } else if (ch == '2') {
            changePasswordAccount(acc);
        } else if (ch == '3') {
            // Record time out (logout time)
            time(&time_out);
            
            // Save time in and time out to a log file (e.g., time_log.txt)
            // This appends to the file; you can change the filename or path as needed
            FILE *fp = fopen("time_log.txt", "a");
            if (fp != NULL) {
                // Use ctime to convert time_t to a readable string
                // ctime includes a newline, so we trim it for better formatting
                char *time_in_str = ctime(&time_in);
                char *time_out_str = ctime(&time_out);
                if (time_in_str[strlen(time_in_str) - 1] == '\n') time_in_str[strlen(time_in_str) - 1] = '\0';
                if (time_out_str[strlen(time_out_str) - 1] == '\n') time_out_str[strlen(time_out_str) - 1] = '\0';
                
                fprintf(fp, "ID: %s, Time In: %s, Time Out: %s\n", acc->idNumber, time_in_str, time_out_str);
                fclose(fp);
            } else {
                // Optional: Handle file open error (e.g., print a message)
                printf("Error: Could not open time log file.\n");
            }
            
            printf("Logging out...\n");
            Sleep(600);
            return;
        } else if (ch == '4') {
            viewAttendance();
        }else if (ch == '5'){
        	aboutUs(acc);
		} else if (ch == '6'){
			void FacultList();
		} else {
            system("cls");
            invalid_Option();
            getch();
        }
    }
}


 

void BSOA_Regular_Schedule() {
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|                                              WEEKLY SCHEDULE                                                   |×|\n");
	printf("                     |×|                                              COURSE: BSOA FIRST YEAR                                           |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|          ⌇     ⌇     ⌇     ⌇     ⌇     ⌇     ⌇     ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇   |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    7:00-8:00    |              |               |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    8:00-8:45    |              |               |               |               |               |  NSTP1 404-   |×|\n");
    printf("                     |×|                 |              |               |               |               |               |  ROOM  MAIN   |×|\n");   
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    8:45-9:00    |                                  BREAK TIME                                                  |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|   9:00-10:00    |              |               |               |               |               |  NSTP1 404-   |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×  ROOM MAIN    |×|\n");
    printf("                     |×|   10;00-10:45   |              |               |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|   10:45-11:15   |                                  LUNCH BREAK                                                 |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|   11:15-12:00   |              |               |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×  GE104 104-   ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×  GE101 404-   |×|\n");
	printf("                     |×|    12:00-1:00   |              |               |  ANNEX        |               |               |  MAIN.        |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×               ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×               |×|\n");
	printf("                     |×|    1:00-2:00    |              | QACC102LEC    |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~× 411-MAIN      |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    2:00-2:45    |              |               | PATHFIT 104   |               |               |               |×|\n");
    printf("                     |×|                 |              |               | ANNEX         |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    2:45-3:00    |                                  BREAK TIME                                                  |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    3:00-4:00    |  PLS 102     |               | PATHFIT 104   |               |               |               |×|\n");
    printf("                     |×|                 |  ANNEX       | QACc102LEC    | ANNEX         |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~× CL2-MAIN      ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    4:00-4:45    | QACC101 102- |               | GE2 104       |               |               |               |×|\n");
    printf("                     |×|                 | ANNEX        |               | ANNEX         |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    4:45-5:15    |                                  BREAK TIME                                                  |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    5:15-6:00    | QACC101 102- | QACC102LEC    | GE2 104       |               |               |               |×|\n");
    printf("                     |×|                 | ANNEX        | ANNEX         | ANNEX         |               |               |               |×|\n");
    printf("                     |×|    6:00-7:00    |              |               |               |               |               |               |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|×|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");


    
    
    
    
    
    }
    

void EDUC_Regular_Schedule() {
	printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|                                              WEEKLY SCHEDULE                                                   |×|\n");
	printf("                     |×|                                              COURSE: EDUC SECOND YEAR                                          |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|          ⌇     ⌇     ⌇     ⌇     ⌇     ⌇     ⌇     ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇      ⌇   |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~~~×~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    7:00-8:00    |              |               |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~| TLE104 405    |×|\n");
	printf("                     |×|    8:00-8:45    |              |               |               |               |               | MAIN          |×|\n");
    printf("                     |×|                 |              |               |               |               |               |               |×|\n");   
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    8:45-9:00    |                                  BREAK TIME                                                  |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|   9:00-10:00    |              |               |               |               |               | TLE104 405    |×|\n");
    printf("                     |×|                 |              |               |               |               |               | MAIN          |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|   10;00-10:45   |              |               |               |               |               | GEE2 405      |×|\n");
    printf("                     |×|                 |              |               |               |               |               | MAIN          |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|   10:45-11:15   |                                  LUNCH BREAK                                                 |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|   11:15-12:00   |              |               |               |               |               |               |×|\n");
    printf("                     |×|                 |              |               |               |               |               | GEE2 405      |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~× PCK105 402    ×~~~~~~~~~~~~~~~× MAIN          |×|\n");
	printf("                     |×|    12:00-1:00   |              |               |               | MAIN          |               |               |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×               ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    1:00-2:00    |              | PCK104 104    |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~× ANNEX         |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~| GEE1 405      |×|\n");
	printf("                     |×|    2:00-2:45    | MAJOR2 LAB HE|               |               | PCK103 402    |               | MAIN          |×|\n");
    printf("                     |×|                 | RM1- ANNEX   |               |               | MAIN          |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    2:45-3:00    |                                  BREAK TIME                                                  |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    3:00-4:00    | MAJOR2 LAB   | PCK104 104    |               |               |               | GEE1 405      |×|\n");
    printf("                     |×|                 | HE RM 1      | ANNEX         |               | PCK103 402    |               | MAIN          |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~× ANNEX        ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~× MAIN          ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    4:00-4:45    |              | FCC104 104    |               |               |               |               |×|\n");
    printf("                     |×|                 |              | ANNEX         |               |               |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|    4:45-5:15    |                                  BREAK TIME                                                  |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    5:15-6:00    | PATHFIT 3     |               |               | MAJOR 2 LEC   |               |               |×|\n");
    printf("                     |×|~~~~~~~~~~~~~~~~~× 104           × FCC104 104    ×~~~~~~~~~~~~~~~× 402 MAIN      ×~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~~|×|\n");
    printf("                     |×|    6:00-7:00    | ANNEX        | ANNEX         |               |               |               |               |×|\n");
	printf("                     |×|~~~~~~~~~~~~~~~~~×~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|×|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");




    
}


void BSCS1_Regular_Schedule() {
	
printf("\n                   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|                                              WEEKLY SCHEDULE                                                   |Ã—|\n");
	printf("                     |Ã—|                                              COURSE: BSCS1M1                                                   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|          ?     ?     ?     ?     ?     ?     ?     ?      ?      ?      ?      ?      ?      ?      ?      ?   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|      TIME       |     MONDAY   |    TUESDAY    |   WEDNESDAY   |   THURSDAY    |     FRIDAY    |    SATURDAY   |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    7:00-8:00    |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:00-8:45    |              |               |               |               |               |  NSTP1 404    |Ã—|\n");
    printf("                     |Ã—|                 |              |               |               |               |               |    MAIN       |Ã—|\n");   
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    8:45-9:00    |                      B    R    E   A   R   K   T   I   M   E                                 |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |A-|                                |               |               |               |               |               |A-|\n");
    printf("                     |Ã—|   9:00-10:00    |              |               |               |               |               |  NSTP1 404    |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|     MAIN      |Ã—|\n");
    printf("                     |Ã—|   10;00-10:45   |              |               |               |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|   10:45-11:15   |                    L   U   N   C   H   B   R   E   A   R   K                                 |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|                 | CC111  LEC   |               |               |               |               |               |Ã—|\n"); 
    printf("                     |Ã—|   11:15-12:00   |  406-MAIN    |               |               |  CC112 LEC    |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|               |~~~~~~~~~~~~~~~|  405-MAIN     |  GE111 404    |Ã—|\n");
	printf("                     |Ã—|    12:00-1:00   |              |               |  GE113 104    |               |               |     MAIN      |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~|              |~~~~~~~~~~~~~~~|    ANNEX      |~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|               |Ã—|\n");
	printf("                     |Ã—|                 |  CC112 CL1   |               |               |               | CC111 LEC     |               |Ã—|\n"); 
    printf("                     |Ã—|    1:00-2:00    |    MAIN      |               |               |               |  406-MAIN     |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|              |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    2:00-2:45    |              |               |  PATHFIT 1    |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |  104-ANNEX    |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    2:45-3:00    |                        B   R   E   A   K   T   I   M   E                                     |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    3:00-4:00    |   PLS 102    |               |  PATHFIT 1    |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |    MAIN      |               |  104-ANNEX    |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    4:00-4:45    |              |               |  GE112 104    |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |   ANNEX       |               |               |               |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |Ã—|    4:45-5:15    |                                  BREAK TIME                                                  |Ã—|\n");
    printf("                     |Ã—|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|Ã—|\n");
    printf("                     |Ã—|    5:15-6:00    |              |               |  GE112 104    |               |               |               |Ã—|\n");
    printf("                     |Ã—|                 |              |               |   ANNEX       |               |               |               |Ã—|\n");
    printf("                     |Ã—|    6:00-7:00    |              |               |               |               |               |               |Ã—|\n");
	printf("                     |Ã—|~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~|Ã—|\n");
	printf("                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");





}




void invalid_StudentID_Display() {
	printf("\033[36;5m");
	printf("                                               __-----_---__-----__-_---_-__----_-__--_-__---___-----__--_\n");
    printf("                                              |  _______________________________________________________  |\n");
    printf("                                              |:|                       ERROR!!!!!                      |:|\n");
    printf("                                              |:|        > Student ID not found! Please try again <     |:|\n");
    printf("                                              |:|_______________________________________________________|:|\n");
    printf("                                              |__-_-_---___----__--_--__-_____----___--___-----__--___--__|\n");
    printf("\033[0m");
    
}


void invalid_Display() {
	printf("\033[36;5m");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
	printf("                                                      |  _______________________________________  |\n");
	printf("                                                      |:|           INVALID INPUTT!!!!!         |:|\n");
	printf("                                                      |:|   > Please select a valid option. <   |:|\n");
	printf("                                                      |:|_______________________________________|:|\n");
	printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
	printf("\033[0m");
}




void usernotfound(){
	printf("\033[36;5m");
	
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    >       USERNAME NOT FOUND     <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}

void invalid_Option(){
	printf("\033[36;5m");
	
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    >       Invalid Option         <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}




void invalidUser(){
	printf("\033[36;5m");
	
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    > INVALID USERNAME OR PASSWORD <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
        
}




void noaccfound() {
		printf("\033[36;5m");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
        printf("                                                       __-----_---__-----__-_---_-__----_-__--_-__\n");
        printf("                                                      |  _______________________________________  |\n");
        printf("                                                      |:|               INVALID!!!!             |:|\n");
        printf("                                                      |:|    > INVALID USERNAME OR PASSWORD <   |:|\n");
        printf("                                                      |:|_______________________________________|:|\n");
        printf("                                                      |__-_-_---___----__--_--__-_____----___--___|\n");
        printf("\033[0m");
}



void loginAccount() {
    struct Account acc;
    char username[50], password[100], inputId[50];
    FILE *fp;
    int attempts = 0;

    while (attempts < 3) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        fp = fopen(ACC_FILE, "r");
        if (fp == NULL) {
            printf("\n(System): No accounts found. Please create one first.\n");
            getch();
            return;
        }

        printf("                  +=======================================================================================================================*\n");
        printf("                  [[                                                   PHILTECH GATEWAY                                                   [[\n");
        printf("                  [[=====================================================================================================================[[\n");
        printf("                  [[                                         ACCOUNT LOGIN SECTION                                                        [[\n");
        printf("                  [[======================================================================================================================[[\n");

        printf("\n\n                                  Enter Username:\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("                                 |                                                                                          |\n");
        printf("                                  ------------------------------------------------------------------------------------------\n");
        printf("\n                                  Type here: ");
       
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
            system("cls");
            usernotfound();
            attempts++;
        } else if (!passwordMatch) {
            system("cls");
            usernotfound();
            attempts++;
        } else if (!idMatch) {
            system("cls");
            invalid_StudentID_Display();
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
            } else if (strcmp (acc.role, "Admin")== 0){ 
                registrarDash(&acc);
            }else {
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





void aboutUs(struct Account *acc) {
	char user;
	char Department, Admin;
	system("cls"); 
	printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  |                                                                                                                      |\n");
    printf("                  |                                                   P H I L T E C H                                                    |\n");
    printf("                  |                                                                                                                      |\n");
    printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  | Name: %s %s A B O U T   U S                                         [ 9 ] Back |\n", acc->firstName, acc->lastName);
    printf("                  +----------------------------------------------------------------------------------------------------------------------+\n");
    printf("                  |__-____--____-----___--____------___----_____---_---_---____-____-____--____------__--____-----___----_____---____--__|\n\n");
    
	printf("                   +---+--------------------------------------------------+(----)+---------------------------------------------------+---+\n");
    printf("                   || .|                                                  |  ||  |                                                   |.  |\n");
    printf("                   |  .|--------------------------------------------------|  ||  |---------------------------------------------------|.| |\n");
    printf("                   | |.| 1. BRIEF HISTORY OF PHILTECH                     |  ||  |  Educational Services                             |.| |\n");
    printf("                   | |.|                                                  |  ||  |                                                   |.  |\n");
    printf("                   |  .| Philippine Technological Institute of Science    |  ||  |  Additional programs accredited by the Technical  || ||\n");
    printf("                   | |.| Arts and Trade Inc. was founded in 2010 as a     |  ||  |  Education and Skills Development Authority -     |. ||\n");
    printf("                   || .| non-stock non-profit non-sectarian private       |  ||  |  Rizal. The first batch of graduates marched      |.| |\n");
    printf("                   | |.| Educational Institution to blaze the trail in    |  ||  |  onto their commencement exercises on April 5,    |.| |\n");
    printf("                   |  .| the field of technical education. Its eleven     |  ||  |  2013 with no less than the TESDA Rizal           |.  |\n");
    printf("                   | |.| founders were a mixture of engineers, a          |  ||  |  Provincial Office Director Velma A. Salazar as   |.| |\n");
    printf("                   | |.| scientist/inventor and practitioner in the IT    |  ||  |  their graduation guest of honor.                 |. ||\n");
    printf("                   |  .| industry, school administrators, managers, and   |  ||  |                                                   |. ||\n");
    printf("                   |  || academic professionals in both public and        |  ||  |  By November of 2012, the negotiation for         |.  |\n");
    printf("                   |  || private institutions. Today, the school is more  |  ||  |  additional branches went underway. The Board of  |.  |\n");
    printf("                   || .| popularly known as PHILTECH.                     |  ||  |  Trustees resolved that two new PHILTECH branches |.| |\n");
    printf("                   |  .|                                                  |  ||  |  should be established and operated in Sta. Rosa, |.| |\n");
    printf("                   | |.| The first school was established in November     |  ||  |  Laguna and General Mariano Alvarez, Cavite.      |.  |\n");
    printf("                   | |.| of 2010 and is presently located at F.T.         |  ||  |  Both branches opened in the first semester of    |. ||\n");
    printf("                   || .| Catapusan St. in Tanay, Rizal. In June 2011,     |  ||  |  school year 2013-2014.                           |.| |\n");
    printf("                   |  .| Philippine Technological Institute of Science    |  ||  |                                                   |.| |\n");
    printf("                   |  .| Arts and Trade Inc. opened and offered two-year  |  ||  |  With Tanay (560 students), Sta. Rosa branch (350 |.  |\n");
    printf("                   || .| programs in Information technology, hotel and    |  ||  |  students), and GMA branch (250 students), school |.| |\n");
    printf("                   | |.| restaurant services, and business outsourcing    |  ||  |  year 2013-2014 totaled at least 1160 students.   |. ||\n");
    printf("                   |  .| management.                                      |  ||  |                                                   |.  |\n");
    printf("                   | |.|                                                  |  ||  |  PHILTECH never tires from helping our Filipino   |.  |\n");
    printf("                   | |.| With every member of the Board of Trustees       |  ||  |  youth. It is patriotic. As educators, it is      || ||\n");
    printf("                   |  .| going out of their way to promote the school     |  ||  |  always fulfilling to mold young minds into       ||  |\n");
    printf("                   || .| and its program offerings, the first semester    |  ||  |  productive citizens. Indeed, it is always a      |.  |\n");
    printf("                   | |.| of school year 2011-2012 continued to provide    |  ||  |  blessing.                                        |.| |\n");
    printf("                   || .| the same.                                        |  ||  |                                                   |.| |\n");
    printf("                   |   +--------------------------------------------------+(----)+---------------------------------------------------+   |\n");
    printf("                   [__-___--__--____-----______---_________--------___________--________--___---______------____--____----____--__--___-_]");
    
    getch();
    
 	
}





void viewAttendance() {
    system("cls");
    printf("\033[36;5m");
    system("color E9");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                          A T T E N D A N C E   R E C O R D S                          [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    
    FILE *fp = fopen("time_log.txt", "r");
    if (fp != NULL) {
        char line[256];
        int recordCount = 0;
        while (fgets(line, sizeof(line), fp)) {
            printf("                  [-] %s", line);  
            recordCount++;
        }
        fclose(fp);
        if (recordCount == 0) {
            printf("                  [-] No attendance records found.                                                         [-]\n");
        }
    } else {
        printf("                  [-] Error: Could not open time log file.                                                 [-]\n");
    }
    
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-] Press any key to return to the dashboard...                                          [-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    getch();  
}



void viewEnrolledStudents() {
    system("cls");
    printf("\033[36;5m");
    printf("                  [-]***************************************************************************************[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                    V I E W   E N R O L L E D   S T U D E N T S                       [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    
    FILE *fp = fopen(ACC_FILE, "r");
    if (fp == NULL) {
        printf("                  [-] Error: Could not open accounts file.                                                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-] Press any key to return...                                                           [-]\n");
        printf("                  [-]***************************************************************************************[-]\n");
        getch();
        return;
    }
    
    struct Account acc;
    int count = 0;
    printf("                  [-] No. | Name                  | ID Number       | Course      | Department              [-]\n");
    printf("                  [-]-----+-----------------------+-----------------+-------------+-------------------------[-]\n");
    
    while (fscanf(fp, "%49[^,],%99[^,],%19[^,],%49[^,],%49[^,],%49[^,],%99[^,],%29[^,],%99[^,],%199[^\n]\n",
                  acc.username, acc.password, acc.role, acc.course, acc.firstName,
                  acc.lastName, acc.Department, acc.idNumber, acc.email, acc.address) == 10) {
        if (strcmp(acc.role, "Student") == 0) {
            count++;
          
            char nameBuffer[25]; 
            char tempName[50];
            sprintf(tempName, "%s %s", acc.firstName, acc.lastName);
            if (strlen(tempName) <= 21) {
                strcpy(nameBuffer, tempName);
            } else {
               
                strncpy(nameBuffer, acc.firstName, 18);
                nameBuffer[18] = '\0';
                strcat(nameBuffer, "...");
            }
            
            printf("                  [-] %-3d | %-21s | %-15s | %-11s | %-23s [-]\n",
                   count, nameBuffer, acc.idNumber, acc.course, acc.Department);
        }
    }
    fclose(fp);
    
    if (count == 0) {
        printf("                  [-] No enrolled students found.                                                         [-]\n");
    }
    
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-] Total Enrolled Students: %d                                                           [-]\n", count);
    printf("                  [-] Press any key to return to the dashboard...                                          [-]\n");
    printf("                  [-]***************************************************************************************[-]\n");
    getch();
}

// The rest of the code remains the same, but replace the placeholder viewEnrolledStudents() with this implementation.

void viewPendingEnrollments() {
  
    printf("no pending enrollments...\n");

    getch();
}

void viewBalances() {
  
    printf("no balances...\n");

    getch();
}

void registrarDash(struct Account *acc) {
    char ch;
    time_t time_in, time_out;  
    
   
    time(&time_in);
    
    while (1) {
        system("cls");
        printf("\033[36;5m");
        system("color E9");
        printf("                  [-]***************************************************************************************[-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]               R E G I S T R A R      D   A   S   H   B   O   A   R   D                [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]***************************************************************************************[-]\n");    
        printf("                  [-]          Welcome Registrar: %s %s                                                     [-]\n", acc->firstName, acc->lastName);                     
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]            ID: %s                                                                     [-]\n" , acc->idNumber);                                                                
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [1] VIEW ALL ACCOUNT                                              [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [2] CHANGE PASSWORD                                               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [3] LOGOUT                                                        [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [4] VIEW ATTENDANCE                                               [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [5] STUDENT RECORD                                                [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [6] ADD FACULTY SCHEDULE                                          [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");   
        printf("Enter choice: ");
        ch = getch();
        printf("%c\n", ch);
        if (ch == '1') {
            viewAllAccounts();
        } else if (ch == '2') {
            changePasswordAccount(acc);
        } else if (ch == '3') {
          
            time(&time_out);
            
            
            
            FILE *fp = fopen("time_log.txt", "a");
            if (fp != NULL) {
              
              
                char *time_in_str = ctime(&time_in);
                char *time_out_str = ctime(&time_out);
                if (time_in_str[strlen(time_in_str) - 1] == '\n') time_in_str[strlen(time_in_str) - 1] = '\0';
                if (time_out_str[strlen(time_out_str) - 1] == '\n') time_out_str[strlen(time_out_str) - 1] = '\0';
                
                fprintf(fp, "ID: %s, Time In: %s, Time Out: %s\n", acc->idNumber, time_in_str, time_out_str);
                fclose(fp);
            } else {
     
                printf("Error: Could not open time log file.\n");
            }
            
            printf("Logging out...\n");
            loadingScreen();
            Sleep(600);
            return;
        } else if (ch == '4') {
            viewAttendance();
        } else if (ch == '5') {
         
            while (1) {
                system("cls");
                printf("\033[36;5m");
                printf("                  [-]***************************************************************************************[-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]                    S   T   U   D   E   N   T     R   E   C   O   R   D                [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]=======================================================================================[-]\n");
                printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
                printf("                  [-]=======================================================================================[-]\n");
                printf("                  [-]***************************************************************************************[-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
                printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
                printf("                  [-]                     [1] VIEW ENROLLED STUDENTS                                       [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
                printf("                  [-]                     [2] VIEW PENDING ENROLLMENTS                                     [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
                printf("                  [-]                     [3] VIEW BALANCES                                                 [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
                printf("                  [-]                     [4] BACK TO MAIN MENU                                            [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
                printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
                printf("                  [-]                                                                                       [-]\n");
                printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");
                printf("Enter choice: ");
                ch = getch();
                printf("%c\n", ch);
                if (ch == '1') {
                    viewEnrolledStudents();
                } else if (ch == '2') {
                    viewPendingEnrollments();
                } else if (ch == '3') {
                    viewBalances();
                } else if (ch == '4') {
                    break;  
                } else {
                    system("cls");
                    invalid_Option();
                    getch();
                }
            }
        } else if (ch == '6') {
            addFacultySchedule();
        } else {
            system("cls");
            invalid_Option();
            getch();
        }
    }
}


// Function to add faculty schedule
void addFacultySchedule() {
    char subject[100], handle[100], timeSchedule[100], room[100];
    
    system("cls");  // Clear screen for input prompts
    printf("Add Faculty Schedule\n");
    printf("====================\n");
    
    printf("Enter subject: ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = '\0';  // Remove trailing newline
    
    printf("Enter handle (teacher name/identifier): ");
    fgets(handle, sizeof(handle), stdin);
    handle[strcspn(handle, "\n")] = '\0';
    
    printf("Enter time schedule (e.g., Monday 9:00 AM - 10:00 AM): ");
    fgets(timeSchedule, sizeof(timeSchedule), stdin);
    timeSchedule[strcspn(timeSchedule, "\n")] = '\0';
    
    printf("Enter room assignment: ");
    fgets(room, sizeof(room), stdin);
    room[strcspn(room, "\n")] = '\0';
    
    // Save to file
    FILE *fp = fopen("faculty_schedule.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Subject: %s, Handle: %s, Time: %s, Room: %s\n", subject, handle, timeSchedule, room);
        fclose(fp);
        printf("\nSchedule added successfully to faculty_schedule.txt.\n");
    } else {
        printf("\nError: Could not open faculty_schedule.txt for writing.\n");
    }
    
    printf("Press any key to return to the dashboard...\n");
    getch();
}



void enrollmentForm() {
    char name[100];
    char id[20];
    char role[20];
    char course[50] = "-";
    char department[100] = "-";
    int age;

    
    system("cls");  

    printf("\033[36;5m");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]                    E   N   R   O   L   L   M   E   N   T     F   O   R   M            [-]\n");
    printf("                  [-]                                                                                       [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-][-]\n");


    printf("                  [-] Enter Full Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    printf("                  [-] Enter ID: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    printf("                  [-] Enter Age: ");
    scanf("%d", &age);
    getchar();  

    printf("                  [-] Enter Role (Student): ");
    fgets(role, sizeof(role), stdin);
    role[strcspn(role, "\n")] = 0;

   if (strcmp(role, "Student") == 0) {
  
        printf("\n                [-]=======================================================================================[-]\n");
        printf("                  [-]                    S   E   L   E   C   T     C   O  U   R   S   E                     [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[-]\n");
        printf("                  [-]=======================================================================================[-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [1] BSCS                                                          [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [2] BSOA                                                          [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                     [3] BTVTED                                                        [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         ++      ++=========================================++      ++                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-]         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                 [-]\n");
        printf("                  [-]                                                                                       [-]\n");
        printf("                  [-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]\n");
        char ch = getch();
        if (ch == '1') strcpy(course, "BSCS");
        else if (ch == '2') strcpy(course, "BSOA");
        else if (ch == '3') strcpy(course, "BTVTED");
        else {
            printf("Invalid choice. Enrollment cancelled.\n");
            return;
        }
        strcpy(department, "-");
    } else {
        printf("Invalid role. Enrollment cancelled.\n");
        return;
    }


    printf("\n\n                  [-]=======================================================================================[-]\n");
    printf("                  [-]                            E N R O L L M E N T   S U M M A R Y                      [-]\n");
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-] Name: %s\n", name);
    printf("                  [-] ID: %s\n", id);
    printf("                  [-] Age: %d\n", age);
    printf("                  [-] Role: %s\n", role);
    printf("                  [-] Department: %s\n", department);
    printf("                  [-] Course: %s\n", course);
    printf("                  [-]=======================================================================================[-]\n");
    printf("                  [-] Enrollment Successful! Press any key to continue...\n");
    getch();
}



void FacultList(){
	while (1){
		char ch;
		
		
		   
   	printf("                     |×|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|×|\n");
	printf("                     |×|                                                                                                           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------+-----------------+-----------------|×|\n");
	printf("                     |×|                                        COLLEGE DEPARTMENT PROFESSOR                                       |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×| NO. |                                 NAME                                  |          SCHEDULE           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|:|\n");
	printf("                     |×|  1  |      MS. ARCEÑO, KIM                                                  |         FULL-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  2  |      MR. ATIENZA, MICHAEL                                             |         FULL-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  3  |      MR. GORDON, RAIVEN                                               |         FULL-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  4  |      MR. JIMINEZ, CARL JOSEPH                                         |         FULL-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  5  |      MR. NORI, LACERNA                                                |         FULL-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  6  |      MR. RAMIZARES, JOHN                                              |         PART-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  7  |      MR. RODRIGUEZ, JUDE                                              |         PART-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  8  |      MR. ROSALES, PAUL                                                |         PART-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  9  |      MR. PATALEN, FRANCIS JUN                                         |         PART-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  10 |      MR. VELE, ALLAN                                                  |         PART-TIME           |×|\n");
	printf("                     |×|-----------------------------------------------------------------------------------------------------------|×|\n");
	printf("                     |×|  11 |      MS. YABUT, EDITH                                                 |         FULL-TIME           |×|\n");
	printf("                     |×|___________________________________________________________________________________________________________|×|\n");
	printf("                     |_______________________________________________________________________________________________________________|\n");
		
		getch();
		
	
	
	
	}
	
	
	
	
	
	
}





















