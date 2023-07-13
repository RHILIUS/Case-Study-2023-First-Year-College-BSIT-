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

// FORMS
void showMainMenu();

// GLOBAL DECLARATIONS
FILE *fptr; 

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
      main();
      break;
    case '2':
      clearScreen();
      viewRecord();
      printf("Press any key to continue...");
      getch();
      main();
      break;
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
  printf("---------------------\n");
}

void printInvalidInput() {
  printf("\033[0;31mInvalid Input!\033[0m\n");
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
  printf("Middle Name     : ");
  scanf(" %[^\n]", employee.middleName);
  capitalizeName(employee.middleName);
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

  // Allow the user to review the entered details and provide an opportunity to make modifications if needed.
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
  switch (choice) {
    case 'Y':
    case 'y':
      break;
    case 'N':
    case 'n':
      clearScreen();
      addEmployee();
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
  // Open the file in read mode
  fptr = fopen("database.bin", "rb");
  if (fptr == NULL) {
    printf("Error opening the file!\n");
    return;
  }

  // Check the file size to determine the number of records
  fseek(fptr, 0, SEEK_END);
  long fileSize = ftell(fptr);
  rewind(fptr);
  
  // Calculate the number of records based on the file size
  int numRecords = fileSize / sizeof(Employee);

  if (numRecords == 0) {
    printf("No records found!\n");
    fclose(fptr);
    return;
  }

  // Print the header
  printf("                                ABC COMPANY\n");
  printf("                                Makati City\n\n");
  printf("                                  Payroll\n\n");
  printf("Employee\tEmployee\tStatus\t\tBasic\t\tOvertime\tDeductions\tNet\n");
  printf("Number\t\tName\t\t\tSalary\t\tPay\t\t\tPay\n");

  // Print the table header
  printf("-----------------------------------------------------------------------------\n");

  // Read and print each employee record
  Employee employee;
  for (int i = 1; i <= numRecords; i++) {
    fread(&employee, sizeof(Employee), 1, fptr);
    printf("%-15s%-25s%-15s%-15.2f%-15.2f%-15.2f%.2f\n",
           employee.num,
           strcat(strcat(strcat(employee.surname, " "), employee.firstName), strcat(" ", employee.middleName)),
           employee.statusCode,
           employee.basicSalary,
           employee.overTimePay,
           employee.deductions,
           employee.netPay);
  }

  // Print the table footer
  printf("-----------------------------------------------------------------------------\n");

  // Close the file
  fclose(fptr);
}
