/*
    System  : ImageInn Radiology Clinic Employee 
    Business: ImageInn Radiology Clinic
    Category: Health & Medicine
    Service : Diagnostic Imaging and Scan Services
    
    Login Info:
        Username: imageinnadmin
        Password: ilovedoctors

    Files Used:
    - employee.csv
    - signinpassword.txt
    - payroll.csv
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.csv"
#define ROLE_COUNT 11

// ---- STRUCTS ----
struct Login
{
    char username[20];
    char password[20];
};

// ---- ALLOWED ROLES ----
const char *roles[ROLE_COUNT] = {
    "Radiologist", "Radiographer", "Sonographer", "Senior Radiographer",
    "Receptionist", "Biomedical Engineer", "Medical Records Clerk", 
    "Billing Clerk", "Clinic Administrator", "Sanitation Assistant", 
    "System Administrator"
};

// ---- ALLOWED STATUSES ----
const char *statuses[] = {
    "Active", "On Leave", "Terminated"
};

// ---- FUNCTION PROTOTYPES ----

//LOGIN FUNCTIONS
int adminSignIn(struct Login *stored);
int loginFileCheck(struct Login *stored);
int signInOptions();

//MENU FUNCTIONS
int adminOptions();

//EMPLOYEE MANAGEMENT FUNCTIONS
void addEmployee();
void deleteEmployee();
void findEmployee();
void listEmployees();
void updateEmployee();

//VALIDATION FUNCTIONS
int isDuplicateID(int id);
int isValidRole(char role[]);
int isValidStatus(char status[]);

//Main Code
int main()
{
    int adminChoice, running = 1, signInChoice;
    struct Login stored;

    if (!loginFileCheck(&stored))
    {
        return 1;
    }

    while (running)
    {
        
        signInChoice = signInOptions();

        switch(signInChoice){
                case 1: 
                    if (adminSignIn(&stored))
                    {
                        int adminRunning = 1;

                        while (adminRunning)
                        {
                            adminChoice = adminOptions();

                            switch(adminChoice)
                            {
                                case 1: 
                                    addEmployee(); 
                                    break;
                                case 2: 
                                    listEmployees(); 
                                    break;
                                case 3: 
                                    findEmployee(); 
                                    break;
                                case 4: 
                                    updateEmployee(); 
                                    break;
                                case 5: 
                                    deleteEmployee(); 
                                    break;
                                case 6:
                                    printf("\nAdmin Session Terminated. Redirecting to the Sign In Menu.\n");
                                    adminRunning = 0;
                                    break;
                            }
                        }
                    } break;
                case 2: 
                {
                    printf("\nThank You for Using Image Inn Radiology System. System Closing...\n");
                    running = 0;
                } break;
            }
    }

    return 0;
}


// ---- LOGIN FUNCTIONS ----

//Function Handling Login Validation
int adminSignIn(struct Login *stored)
{
    struct Login entered;

    while (1)
    {
        printf("\nUsername: ");
        scanf("%19s", entered.username);

        printf("Password: ");
        scanf("%19s", entered.password);

        if (strlen(entered.password) < 6)
        {
            printf("\nPassword must be at least 6 characters.\n");
            continue;
        }

        if (strcmp(entered.username, stored->username) == 0 &&
            strcmp(entered.password, stored->password) == 0)
        {
            printf("\nLogin Successful.\n");
            return 1;
        }
        else
        {
            printf("\nIncorrect Login. Please Try Again.\n");
        }
    }
}

//Function Handling .txt File Check
int loginFileCheck(struct Login *stored)
{
    FILE *passwordptr;
    passwordptr = fopen("signinpassword.txt", "r");

    if (passwordptr != NULL)
    {
        if (fscanf(passwordptr, "%19s %19s", stored->username, stored->password) != 2)
        {
            printf("\nError reading login data.\n");
            fclose(passwordptr);
            return 0;   
        }

        fclose(passwordptr);
        printf("\nSystem Boot Successful\n");
        return 1;  
    }
    else
    {
        printf("\nSystem Boot Unsuccessful\n");
        return 0;  
    }
}

//Function Handling the Sign In Menu
int signInOptions()
{
    
    int result;
    int signInChoice;
    
    do {
        printf(
        "\n--- ImageInn System Admin Sign In Menu ---\n"
        "\n1. Admin Sign In\n"
        "2. Exit Sign In Menu\n"
        "\nEnter the Number Corresponding with the Desired Menu Option:\n"
        );
        
        result = scanf("%d", &signInChoice);

        //Input Validation and Clearing Buffer
        if (result != 1) {
            printf("Invalid Input. Please Enter a Number.\n");
            while (getchar() != '\n');
        }

        else if (signInChoice < 1 || signInChoice > 2) {
            printf("Choice must be between 1 and 2.\n");
        }   
    } while (result != 1 || signInChoice < 1 || signInChoice > 2);
    
     return (signInChoice); 
}


// ---- MENU FUNCTIONS ----

// Function Handling the Admin Menu
int adminOptions()
{
    int admin_menu;
    int result;
    
    do {
    printf(
        "\n--- ImageInn System Admin Menu ---"
        "\n1. Add Employee\n"
        "2. List Employees\n"
        "3. Find Employee\n"
        "4. Update Employee\n"
        "5. Delete Employee\n"
        "6. Logout of System Admin Menu\n"
        "\nEnter the Number Corresponding with the Desired Menu Option:\n"
        );


    result = scanf("%d", &admin_menu);

    //Input Validation and Clearing Buffer
    if (result != 1)
        {
            printf("Invalid Input. Please Enter a Number.\n");
            while (getchar() != '\n');
        }
        else if (admin_menu < 1 || admin_menu > 6)
        {
            printf("Choice must be between 1 and 6.\n");
        }

    } while (result != 1 || admin_menu < 1 || admin_menu > 6);

    return (admin_menu);
}


// ---- EMPLOYEE FUNCTIONS ----

// Add Employee
void addEmployee() {
    FILE *fp;
    int id, result, roleChoice;
    char firstName[50], lastName[50], role[100], status[100];

    do {
        printf("Enter ID: ");
        result = scanf("%d", &id);
        
        //Input Validation and Clearing Buffer
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
        }
    } while (result != 1);

    if (isDuplicateID(id)) {
        printf("ID already exists!\n");
        return;
    }

    printf("Enter First Name: ");
    scanf(" %49[^\n]", firstName);

    printf("Enter Last Name: ");
    scanf(" %49[^\n]", lastName);

    printf("\n ---List of Roles--- \n");
    for (int i = 0; i < 11; i++) {
        printf("%d - %s\n", i + 1, roles[i]);
    }

    printf("\nEnter Role #: ");
    scanf("%d", &roleChoice);

    //Input Validation
    if (roleChoice < 1 || roleChoice > 11) {
    printf("Invalid choice!\n");
    return;
    }

    strcpy(role, roles[roleChoice- 1]);

    printf("Enter Status: ");
    scanf(" %[^\n]", status);

    if (!isValidStatus(status)) {
        printf("Invalid Status!\n");
        return;
    }

    fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%d,%s,%s,%s,%s\n", id, firstName, lastName, role, status);
    fclose(fp);

    printf("Employee Added Successfully!\n");
}

// Delete Employee (Sequential Rewrite)
void deleteEmployee() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");

    int id, searchID, found = 0, result;
    char firstName[50], lastName[50], role[100], status[100];

    do {
        printf("Enter ID to delete: ");
        result = scanf("%d", &searchID);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        }
    } while (result != 1);

    if (fp == NULL) {
        printf("No records found.\n");
        if (temp != NULL) fclose(temp);
        return;
    }

    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d,%49[^,],%49[^,],%99[^,],%99[^\n]\n",
                  &id, firstName, lastName, role, status) != EOF) {

        if (id == searchID) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d,%s,%s,%s,%s\n",
                id, firstName, lastName, role, status);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    if (found)
        printf("Employee Deleted!\n");
    else
        printf("Employee not found.\n");
}

// Find Employee
void findEmployee() {
    FILE *fp = fopen(FILE_NAME, "r");
    int id, searchID, found = 0, result;
    char firstName[50], lastName[50], role[100], status[100];

    do {
        printf("Enter ID to search: ");
        result = scanf("%d", &searchID);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        }
    } while (result != 1);

    if (fp == NULL) {
        printf("Employee file not found.\n");
        return;
    }

    while (fscanf(fp, "%d,%49[^,],%49[^,],%99[^,],%99[^\n]\n",
                  &id, firstName, lastName, role, status) != EOF) {
        if (id == searchID) {
            printf("Found: ID: %d | Name: %s %s | Role: %s | Status: %s\n",
                    id, firstName, lastName, role, status);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found.\n");

    fclose(fp);
}

// List Employees
void listEmployees(){

    FILE *fp = fopen(FILE_NAME, "r");
    int id, found = 0;
    char firstName[50], lastName[50], role[100], status[100];

    if (fp == NULL) {
        printf("Employee file not found.\n");
        return;
    }

    printf("\n                             ---------- Employee List ----------    \n");

    while (fscanf(fp, "%d,%49[^,],%49[^,],%99[^,],%99[^\n]\n",
                  &id, firstName, lastName, role, status) != EOF) {
        printf("ID: %-2d | Name:  %-12s  %-15s | Role:  %-23s |  Status: %s\n",
                id, firstName, lastName, role, status);
        found = 1;
    }

    if (!found) {
        printf("No employee records to display.\n");
    }

    fclose(fp);
}

// Update Employee
void updateEmployee(){
    FILE *fp = fopen(FILE_NAME, "r");
    

    int id, searchID, found = 0, result, updateResult;
    char firstName[50], lastName[50], role[100], status[100];

    do {
        printf("Enter ID to update: ");
        result = scanf("%d", &searchID);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        }
    } while (result != 1);

    if (fp == NULL) {
        printf("Employee file not found.\n");
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }
    
    while (fscanf(fp, "%d,%49[^,],%49[^,],%99[^,],%99[^\n]\n",
                  &id, firstName, lastName, role, status) != EOF) {

        if (id == searchID) {
            int updateChoice;
            int updating = 1;
            found = 1;

            while (updating) {
                do {
                    printf(
                        "\n1. Change First Name\n"
                          "2. Change Last Name\n"
                          "3. Change Role\n"
                          "4. Change Status\n"
                          "5. Finish\n"
                    );
                    updateResult = scanf("%d", &updateChoice);

                    if (updateResult != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    while (getchar() != '\n');
                    } 
                    else if (updateChoice < 1 || updateChoice > 5) {
                        printf("Choice must be between 1 and 5.\n");
                        updateResult = 0;
                        }
                } while (updateResult != 1);

                switch(updateChoice){
                    case 1:
                        printf("Enter new First Name: ");
                        scanf("%49s", firstName);
                        break;
                    
                    case 2:
                        printf("Enter new Last Name: ");
                        scanf("%49s", lastName);
                        break;

                    case 3:
                        do {
                            printf("Enter new Role: ");
                            scanf(" %[^\n]", role);

                            if (!isValidRole(role)) {
                            printf("Invalid Role! Please try again.\n");
                            }
                        } while (!isValidRole(role));
                        break;
                        
                    case 4:
                        do {
                            printf("Enter new Status: ");
                            scanf(" %[^\n]", status);

                            if (!isValidStatus(status)) {
                            printf("Invalid Status! Please try again.\n");
                            }
                        } while (!isValidStatus(status));
                        break;

                    case 5:
                        updating = 0;
                            break;

                        default:
                            printf("Invalid choice.\n");
                    }
                }
            }

        fprintf(temp, "%d,%s,%s,%s,%s\n", id, firstName, lastName, role, status);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    if (found)
        printf("Employee Updated!\n");
    else
        printf("Employee not found.\n");
}

// ---- VALIDATION FUNCTIONS ----

// Check if ID Already Exists
int isDuplicateID(int id) {
    FILE *fp = fopen(FILE_NAME, "r");
    int eid;
    char firstName[50], lastName[50], role[100], status[100];

    if (fp == NULL) return 0;

    while (fscanf(fp, "%d,%49[^,],%49[^,],%99[^,],%99[^\n]\n",
                  &eid, firstName, lastName, role, status) != EOF) {
        if (eid == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Function to Validate Role
int isValidRole(char role[]) {
    for (int i = 0; i < ROLE_COUNT; i++) {
        if (strcmp(role, roles[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to Validate Status
int isValidStatus(char status[]) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(status, statuses[i]) == 0)
            return 1;
    }
    return 0;
}


