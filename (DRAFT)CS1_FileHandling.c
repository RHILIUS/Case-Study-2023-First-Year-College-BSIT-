#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCT
typedef struct Employee {
  char num[20];
  char surname[10];
  char firstName[15];
  char middleName[10];
  char statusCode[8];
  int hoursWorked;
  float deductions;
  float basicSalary;
  float basicRate;
  float overTimeRate;
  float overTimePay;
  float netPay;
} Employee;

typedef struct Company {
  char name[20];
  char location[20];
} Company;

// MENU OPTIONS
void addEmployee(); 
void viewRecord();

// FUNCTIONS
char prompt(); // Function to get the option from the user
void capitalizeName(char *name);
void clearScreen();
void checkFile(FILE* file);
void printBorder();
void printInvalidInput();
int getFloatDigitCount(float num);
int getCenterPosition(int horizontalLength, int stringLength);
void printToCenter(char str[], int size, int horizontalLength);
void printHorizontalBorder(int horizontalLength);

// FORMS
void showMainMenu();

// GLOBAL DECLARATIONS
FILE *fptr; 
Company company = {"ABC COMPANY","Makati City"};

// MAIN
int main() {

  showMainMenu();
  char choice = prompt();
  
  switch(choice) {
    case '1':
      clearScreen();
      addEmployee();
      printf("Press any key to continue...");
      getch();
      clearScreen();
      main();
      break;
    case '2':
      clearScreen();
      viewRecord();
      printf("Press any key to continue...");
      getch();
      clearScreen();
      main();
      break;
    default:
      clearScreen();
      printInvalidInput();
      main();
  }
  getch();

}

char prompt() {
  char choice;
  printf("\nEnter: ");
  scanf(" %c", &choice);
  return choice; 
}

void capitalizeName(char *name) {
  int i = 0;

  // Capitalize the first letter of the name
  name[0] = toupper(name[0]);

  // Iterate through the name and capitalize the first letter of each word
  while (name[i] != '\0') {
    if (name[i] == ' ') {
      // If the current character is a space, capitalize the next character
      name[i + 1] = toupper(name[i + 1]);
    }
    i++;
  }
}

void clearScreen() {
  system("cls");
}

void checkFile(FILE* file) {
  if (file == NULL) {
    printf("Error opening the file!\n");
  }
}

void printBorder() {
  printf("-------------------------------\n");
}

void printInvalidInput() {
  printf("\033[0;31mInvalid Input!\033[0m\n");
}

int getFloatDigitCount(float num) {
  char floatStr[20];
  sprintf(floatStr, "%.2f", num);
  int digitCount = 0;
  for (int i = 0; floatStr[i] != '\0'; i++) {
    if (floatStr[i] != '.') {
      digitCount++;
    }
  }
  digitCount++;
  return digitCount;
}

int getCenterPosition(int horizontalLength, int stringLength) {
  
  int horizontalLength_median;
  int stringLength_median;
  int startPosition;
  
  // Get the median of the horizontalLength
  horizontalLength_median = horizontalLength/2;
  if (horizontalLength % 2 != 0) {
    horizontalLength_median++;
  }

  // Get the median of the stringLength
  stringLength_median = stringLength/2;
  if (stringLength % 2 != 0) {
    stringLength_median++;
  }

  // Get the startPosition
  startPosition = horizontalLength_median - stringLength_median;

  return startPosition;

}

void printToCenter(char str[], int size, int horizontalLength) {

  int startPosition = getCenterPosition(horizontalLength,size);
  for (int i = 0; i < horizontalLength; i++) {
    if (i == startPosition) {
      printf("%s", str);
      i = i+size-1;
    } else {
      printf(" ");
    }
  }
}

void printHorizontalBorder(int horizontalLength) {
  for (int i = 0; i < horizontalLength; i++) {
    printf("-");
  }
  printf("\n");
}

void showMainMenu() {
  printf("\
                ABC Company Payroll System\n\
                         MAIN MENU\n\n\
  1. Add Employee\n\
  2. View Record\n\
  3. Update Record\n\
  4. Delete Record\n\
  5. Exit\n");
}

void addEmployee() {

  // Create employee
  Employee employee;

  // Set the fields to NULL
  strcpy(employee.num,"");
  strcpy(employee.surname,"");
  strcpy(employee.firstName,"");
  strcpy(employee.middleName,"");
  strcpy(employee.statusCode,"");
  employee.hoursWorked = 0;
  employee.deductions = 0.00;
  employee.basicSalary = 0.00;
  employee.basicRate = 0.00;
  employee.overTimeRate = 0.00;
  employee.overTimePay = 0.00;
  employee.netPay = 0.00;

  // Input values to the employee
  printf("Employee Input Prompt\n");
  printBorder();
  printf("\n");
  printf("Please provide the following details for the month:\n\n");
  printf("Employee Number : ");
  scanf("%s", employee.num);

  printf("<Full Name>\n");
  printf("Surname         : ");
  scanf(" %[^\n]", employee.surname); // '%[^\n]' is done to include white spaces for names ex: 'De Leon', 'De Ocampo'
  capitalizeName(employee.surname);
  printf("First Name      : ");
  scanf(" %[^\n]", employee.firstName);
  capitalizeName(employee.firstName);
  printf("<'0' if not applicable>\n");
  printf("Middle Name     : ");
  scanf(" %[^\n]", employee.middleName);
  capitalizeName(employee.middleName);
  if (employee.middleName[0] == '0') {
    strcpy(employee.middleName,"");
  }

  statusCodePrompt:
  printf("<R for Regular, C for Casual>\n");
  printf("Status Code     : ");
  char statusCode;
  scanf(" %c", &statusCode); // white space before '%c' to disregard '\n' from the previous input 
  statusCode = toupper(statusCode); // statusCode is set to uppercase for consistency
  if (statusCode != 'R' && statusCode != 'C') { // input the value again if invalid
    clearScreen();
    printInvalidInput();
    goto statusCodePrompt;
  }
  if (statusCode == 'R') {
    strcpy(employee.statusCode,"Regular");
  } else {
    strcpy(employee.statusCode,"Casual");
  }
  printf("Hours Worked    : "); 
  scanf("%d", &employee.hoursWorked);
  printf("Deductions      : ");
  scanf("%f", &employee.deductions);

  // If statusCode is "Regular"
  if (stricmp(employee.statusCode,"Regular") == 0) {
    printf("Basic Salary    : ");
    scanf("%f", &employee.basicSalary);
    if (employee.hoursWorked > 160) {
      employee.basicRate = employee.basicSalary / 160;
      employee.overTimeRate = employee.basicRate * 1.5;
      employee.overTimePay = employee.overTimeRate * (employee.hoursWorked - 160);
    }
  }
  // If statusCode is "Casual"
  else {
    printf("Basic Rate      : ");
    scanf("%f",&employee.basicRate);
    employee.basicSalary = employee.hoursWorked * employee.basicRate;
    if (employee.hoursWorked > 160) {
      employee.basicSalary = employee.basicRate * 160;
      employee.overTimeRate = employee.basicRate * 1.5;
      employee.overTimePay = employee.overTimeRate * (employee.hoursWorked - 160);
    }

  }

  // Calculate Net Pay
  employee.netPay = employee.basicSalary + employee.overTimePay - employee.deductions;

  // Allow the user to review the entered details and provide an opportunity to abolish the data
  clearScreen();
  informationReview:
  printf("Information Review\n");
  printBorder();
  printf("\n");
  printf("Employee Number : %s\n", employee.num);
  printf("Surname         : %s\n", employee.surname);
  printf("First Name      : %s\n", employee.firstName);
  printf("Middle Name     : %s\n", employee.middleName);
  printf("Status Code     : %s\n", employee.statusCode);
  printf("Hours Worked    : %d\n", employee.hoursWorked);
  printf("Deductions      : %.2f\n", employee.deductions);
  if (stricmp(employee.statusCode,"Regular")==0) {
    printf("Basic Salary    : %.2f\n", employee.basicSalary);
  } else {
    printf("Basic Rate      : %.2f\n", employee.basicRate);
  }

  printf("\nAre you sure you want to proceed and save the entered details? (Y/N)");
  char choice = getch();
  printf("\n");
  switch (choice) {
    case 'Y':
    case 'y':
      break;
    case 'N':
    case 'n':
      clearScreen();
      main();
      break;
    default:
      clearScreen();
      printInvalidInput();
      goto informationReview;
  }
  
  // Append employee to the file
  fptr = fopen("database.bin","ab"); checkFile(fptr);
  fwrite(&employee, sizeof(Employee),1, fptr);
  fclose(fptr);
}

void viewRecord() {
  

  // Declare an employee struct
  Employee employee;
  
  // Determine the maximum output length per field to ensure even column spacing for display.
  fptr = fopen("database.bin","r"); checkFile(fptr);
  int i = 1;
  int numColLength = strlen("Employee Number");
  int nameColLength = strlen("Employee Name");
  int statusColLength = strlen("Status Code");
  int salaryColLength = strlen("Basic Salary");
  int overtimeColLength = strlen("Overtime Pay");
  int deductionsColLength = strlen("Deductions");
  int netpayColLength = strlen("Net Pay");

  while (fread(&employee,sizeof(Employee),1,fptr)) {
    // printf("%d)\n", i);
    // i++;
    // printf("Employee Number: %s%10d\n", employee.num, strlen(employee.num));
    // printf("Surname        : %s%10d\n", employee.surname, strlen(employee.surname));
    // printf("First Name     : %s%10d\n", employee.firstName, strlen(employee.firstName));
    // printf("Status Code    : %s%10d\n", employee.statusCode, strlen(employee.statusCode));
    // printf("Basic Salary   : %.2f%10d\n", employee.basicSalary,getFloatDigitCount(employee.basicSalary));
    // printf("Overtime Pay   : %.2f%10d\n", employee.overTimePay, getFloatDigitCount(employee.overTimePay));
    // printf("Deductions     : %.2f%10d\n", employee.deductions,getFloatDigitCount(employee.deductions));
    // printf("Net Pay        : %.2f%10d\n", employee.netPay, getFloatDigitCount(employee.netPay));
    // printBorder();

    if (strlen(employee.num) > numColLength) {
      numColLength = strlen(employee.num);
    }
    int employeeNameLength = strlen(employee.surname)+strlen(employee.firstName)+5;
    if (employeeNameLength > nameColLength) {
      nameColLength = employeeNameLength;
    }
    if (strlen(employee.statusCode) > statusColLength) {
      statusColLength = strlen(employee.statusCode);
    }
    if (getFloatDigitCount(employee.basicSalary) > salaryColLength) {
      salaryColLength = getFloatDigitCount(employee.basicSalary);
    }
    if (getFloatDigitCount(employee.overTimePay) > overtimeColLength) {
      overtimeColLength = getFloatDigitCount(employee.overTimePay);
    }
    if (getFloatDigitCount(employee.deductions) > deductionsColLength) {
      deductionsColLength = getFloatDigitCount(employee.deductions);
    }
    if (getFloatDigitCount(employee.netPay) > netpayColLength) {
      netpayColLength = getFloatDigitCount(employee.netPay);
    }
  }  

  // printf("Max Num : %d\n", numColLength);
  // printf("Max Name: %d\n", nameColLength);
  // printf("Max Status: %d\n", statusColLength);
  // printf("Max Salary: %d\n", salaryColLength);
  // printf("Max OT: %d\n", overtimeColLength);
  // printf("Max Deductions: %d\n", deductionsColLength);
  // printf("Max Netpay: %d\n", netpayColLength);
  // printBorder();
  fclose(fptr);

  // Print header
  int horizontalLength = numColLength+nameColLength+statusColLength+salaryColLength+overtimeColLength+deductionsColLength+netpayColLength + 8; // Add 8 for border lines

  printf("\
                                               ABC COMPANY\n\
                                               Makati City\n\
  \n\
                                                 Payroll\n\
  ---------------------------------------------------------------------------------------------\n\
  Employee             Employee            Status     Basic      Overtime  Deductions   Net Pay\n\
  Number               Name                           Salary     Pay\n");
  printBorder();
  // Print header row
  printToCenter(company.name,strlen(company.name),horizontalLength);
  printf("\n");
  printToCenter(company.location, strlen(company.location), horizontalLength);
  printf("\n\n");

  // print header row top border
  printHorizontalBorder(horizontalLength);

  printf("|");
  printToCenter("Employee Number", strlen("Employee Number"), numColLength); printf("|");
  printToCenter("Employee Name", strlen("Employee Name"), nameColLength); printf("|");
  printToCenter("Status Code", strlen("Status Code"), statusColLength); printf("|");
  printToCenter("Basic Salary", strlen("Basic Salary"), salaryColLength); printf("|");
  printToCenter("Overtime Pay", strlen("Overtime Pay"), overtimeColLength); printf("|");
  printToCenter("Deductions", strlen("Deductions"), deductionsColLength); printf("|");
  printToCenter("Net Pay", strlen("Net Pay"), netpayColLength); printf("|");
  printf("\n");

  // print header row bottom border
  printHorizontalBorder(horizontalLength);

  // Display employees and fields
  fptr = fopen("database.bin","rb");

  while (fread(&employee,sizeof(Employee),1,fptr)) {
    // Employee Number
    printf("|");
    printToCenter(employee.num, strlen(employee.num),numColLength);

    // Employee Name
    char fullname[50];
    char middleInitial = employee.middleName[0];
    char temp[2];

    temp[0] = middleInitial;
    temp[1] = '\0';

    strcpy(fullname, employee.surname);
    strcat(fullname, ", ");
    strcat(fullname, employee.firstName);
    strcat(fullname, " ");
    strcat(fullname, temp);

    printf("|");
    printToCenter(fullname,strlen(fullname),nameColLength);

    // Status Code
    printf("|");
    printToCenter(employee.statusCode,strlen(employee.statusCode),statusColLength);

    // Basic Salary
    char tempStr[20];

    printf("|");
    sprintf(tempStr,"%.2f",employee.basicSalary);
    printToCenter(tempStr,strlen(tempStr),salaryColLength);

    // Overtime Pay
    printf("|");
    sprintf(tempStr, "%.2f", employee.overTimePay);
    if (employee.overTimePay == 0) {
      printToCenter("N/A",strlen("N/A"),overtimeColLength);
    } else {
      printToCenter(tempStr,strlen(tempStr),overtimeColLength);
    }

    // Deductions
    printf("|");
    sprintf(tempStr, "%.2f", employee.deductions);
    if (employee.deductions == 0) {
      printToCenter("N/A",strlen("N/A"),deductionsColLength);
    } else {
      printToCenter(tempStr,strlen(tempStr),deductionsColLength);
    }

    // Net Pay
    printf("|");
    sprintf(tempStr, "%.2f", employee.netPay);
    printToCenter(tempStr,strlen(tempStr),netpayColLength);

    printf("|\n");

  }
  
  // Print foot bottom border
  printHorizontalBorder(horizontalLength);
  fclose(fptr);


  
  

  

  
}
