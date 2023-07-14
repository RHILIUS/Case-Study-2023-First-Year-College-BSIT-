#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
  time_t timeAdded;
} Employee;

typedef struct Company {
  char name[20];
  char location[20];
} Company;

// MENU OPTIONS
void addEmployee(); 
void viewRecord();
void updateRecord();
void deleteRecord();

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
void sortEmployees(Employee employees[], int count);
void sortEmployeesReverse(Employee employees[], int count);
void sortTime(Employee employees[], int count);
void sortTimeReverse(Employee employees[], int count);
void showRecord();
time_t getCurrentDateTime();
char* timeToStr(time_t time);

// FORMS
void showMainMenu();

// GLOBAL DECLARATIONS
FILE *mainFile, *tempFile; 
int recordIsSortedToProper = 0;
Employee employee;
Company company = {"ABC COMPANY","Makati City"};
int horizontalLength;

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
      clearScreen();
      main();
      break;
    case '4':
      clearScreen();
      deleteRecord();
      printf("Press any key to continue...");
      getch();
      clearScreen();
      main();
    case '5':
      clearScreen();
      printf("Thank you for using our program. Have a great day!\n");
      exit(0);
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

void sortEmployees(Employee employees[], int count) {
    int i;
    Employee temp;
    int switched = 1;

    while (switched) {
      switched = 0;
      for (int i = 0; i < count-1; i++) {
        if (strcmp(employees[i].surname,employees[i+1].surname) > 0) {
          temp = employees[i];
          employees[i] = employees[i+1];
          employees[i+1] = temp;
          switched = 1;
        }
      }
    }
}

void sortEmployeesReverse(Employee employees[], int count) {
    int i;
    Employee temp;
    int switched = 1;

    while (switched) {
      switched = 0;
      for (int i = 0; i < count-1; i++) {
        if (strcmp(employees[i].surname,employees[i+1].surname) < 0) {
          temp = employees[i];
          employees[i] = employees[i+1];
          employees[i+1] = temp;
          switched = 1;
        }
      }
    }
}

void sortTime(Employee employees[], int count) {
   int i;
    Employee temp;
    int switched = 1;

    while (switched) {
      switched = 0;
      for (int i = 0; i < count-1; i++) {
        if (employees[i].timeAdded > employees[i+1].timeAdded) {
          temp = employees[i];
          employees[i] = employees[i+1];
          employees[i+1] = temp;
          switched = 1;
        }
      }
    }
}

void sortTimeReverse(Employee employees[], int count) {
  int i;
    Employee temp;
    int switched = 1;

    while (switched) {
      switched = 0;
      for (int i = 0; i < count-1; i++) {
        if (employees[i].timeAdded < employees[i+1].timeAdded) {
          temp = employees[i];
          employees[i] = employees[i+1];
          employees[i+1] = temp;
          switched = 1;
        }
      }
    }
}

void showRecord() {
  // Determine the maximum output length per field to ensure even column spacing for display.
  mainFile = fopen("main.bin","r"); checkFile(mainFile);
  int i = 1;
  int countColLength = strlen("#");
  int numColLength = strlen("Employee Number");
  int nameColLength = strlen("Employee Name");
  int statusColLength = strlen("Status Code");
  int salaryColLength = strlen("Basic Salary");
  int overtimeColLength = strlen("Overtime Pay");
  int deductionsColLength = strlen("Deductions");
  int netpayColLength = strlen("Net Pay");
  int timeColLength = strlen("Date Modified");
  
  int count = 0;
  char strCount[10];
  while (fread(&employee,sizeof(Employee),1,mainFile)) {
    count++;
    sprintf(strCount, "%d", count);
    if (strlen(strCount) > countColLength) {
      countColLength = strlen(strCount);
    }
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
    if (strlen(timeToStr(employee.timeAdded)) > timeColLength) {
      timeColLength = strlen(timeToStr(employee.timeAdded));
    }
  }  

  // Add 2 spaces between the text for better spacing
  countColLength += 2;
  numColLength += 2;
  nameColLength += 2;
  statusColLength += 2;
  salaryColLength += 2;
  overtimeColLength += 2;
  deductionsColLength += 2;
  netpayColLength += 2;
  timeColLength += 2;

  fclose(mainFile);

  // Print header
  horizontalLength = countColLength+numColLength+nameColLength+statusColLength+salaryColLength+overtimeColLength+deductionsColLength+netpayColLength+timeColLength + 10; // Add 10 for border lines 

  // Print header row
  printToCenter(company.name,strlen(company.name),horizontalLength);
  printf("\n");
  printToCenter(company.location, strlen(company.location), horizontalLength);
  printf("\n\n");
  printToCenter("Payroll",strlen("Payroll"),horizontalLength);
  printf("\n\n");

  // print header row top border
  printHorizontalBorder(horizontalLength);

  printf("|");
  printToCenter("#", strlen("#"),countColLength); printf("|");
  printToCenter("Employee Number", strlen("Employee Number"), numColLength); printf("|");
  printToCenter("Employee Name", strlen("Employee Name"), nameColLength); printf("|");
  printToCenter("Status Code", strlen("Status Code"), statusColLength); printf("|");
  printToCenter("Basic Salary", strlen("Basic Salary"), salaryColLength); printf("|");
  printToCenter("Overtime Pay", strlen("Overtime Pay"), overtimeColLength); printf("|");
  printToCenter("Deductions", strlen("Deductions"), deductionsColLength); printf("|");
  printToCenter("Net Pay", strlen("Net Pay"), netpayColLength); printf("|");
  printToCenter("Date Modified", strlen("Date Modified"), timeColLength); printf("|");
  printf("\n");

  // print header row bottom border
  printHorizontalBorder(horizontalLength);

  // Display employees and fields
  mainFile = fopen("main.bin","rb"); checkFile(mainFile);

  count = 1;
  while (fread(&employee,sizeof(Employee),1,mainFile)) {
    // #
    sprintf(strCount,"%d",count);
    printf("|");
    printToCenter(strCount,strlen(strCount),countColLength);
    count++; 

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

    // Date Modified
    printf("|");
    printToCenter(timeToStr(employee.timeAdded),strlen(timeToStr(employee.timeAdded)),timeColLength);
    printf("|\n");

  }
  
  // Print foot bottom border
  printHorizontalBorder(horizontalLength);
  fclose(mainFile);
}

time_t getCurrentDateTime() {
    time_t currentTime = time(NULL); // Get the current time
    return currentTime;
}

char* timeToStr(time_t time) {
    struct tm* localTime = localtime(&time); // Convert to local time

    static char dateTimeStr[64]; // Allocate a static character array to store the formatted date and time string
    strftime(dateTimeStr, sizeof(dateTimeStr), "%Y-%m-%d %H:%M:%S", localTime); // Format the date and time string

    return dateTimeStr;
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
  printf("\033[0;32m%s\033[0m\n", "Employee Input Prompt\n");
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
  printHorizontalBorder(strlen("Please provide the following details for the month:"));
  printf("<'0' if not applicable>\n");
  printf("Middle Name     : ");
  scanf(" %[^\n]", employee.middleName);
  capitalizeName(employee.middleName);
  if (employee.middleName[0] == '0') {
    strcpy(employee.middleName,"");
  }

  statusCodePrompt:
  printHorizontalBorder(strlen("Please provide the following details for the month:"));
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
  printf("\033[0;32m%s\033[0m\n", "Information Review\n");
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
  
  // Add time current time to file
  employee.timeAdded = getCurrentDateTime();

  // Append employee to the file
  mainFile = fopen("main.bin","ab"); checkFile(mainFile);
  fwrite(&employee, sizeof(Employee),1, mainFile);
  fclose(mainFile);


}

void viewRecord() {
  
  clearScreen();
  showRecord();

  printf("1. Sort by name\n");
  printf("2. Sort by date\n");
  printf("Press other key to continue...");
  int choice = getch();
  printf("\n");
  
  // Set the employees to alphabetical order
  if (choice == '1') {
    Employee employees[100];

    // Put the data from temp.bin to employees[]
    int count = 0;
    mainFile = fopen("main.bin", "rb+"); checkFile(mainFile);
    while (fread(&employees[count], sizeof(Employee), 1, mainFile)) {
        count++;
    }

    // Sort the array based on the surname field
   
    if (recordIsSortedToProper) {
      sortEmployeesReverse(employees,count);
      recordIsSortedToProper = 0;
    } else {
      sortEmployees(employees,count);
      recordIsSortedToProper = 1;
    }

    // Write the array values back to temp.bin
    rewind(mainFile); 
    fwrite(employees, sizeof(Employee),count,mainFile);

    // Close File
    fclose(mainFile);

    // Recursion
    viewRecord();

  } else if (choice == '2') {
    Employee employees[100];

    // Put the data from temp.bin to employees[]
    int count = 0;
    mainFile = fopen("main.bin", "rb+"); checkFile(mainFile);
    while (fread(&employees[count], sizeof(Employee), 1, mainFile)) {
        count++;
    }

    // Sort the array based on the timeAdded field

    if (recordIsSortedToProper) {
      sortTime(employees,count);
      recordIsSortedToProper = 0;
    } else {
      sortTimeReverse(employees,count);
      recordIsSortedToProper = 1;
    }

    // Write the array values back to temp.bin
    rewind(mainFile); 
    fwrite(employees, sizeof(Employee),count,mainFile);

    // Close File
    fclose(mainFile);

    // Recursion
    viewRecord();
  } 
}

void deleteRecord() {
  showRecord();

  printf("Enter index to delete (0 to exit): ");
  int index;
  scanf("%d", &index);

  if (index == 0) {
    return; // Exit the function
  }

  // Open the main and temp files
  mainFile = fopen("main.bin", "rb"); checkFile(mainFile);
  tempFile = fopen("temp.bin", "wb"); checkFile(tempFile);

  // Copy all records except the one to be deleted from main file to temp file
  int count = 1; // Start count at 1
  while (fread(&employee, sizeof(Employee), 1, mainFile)) {
    if (count != index) {
      fwrite(&employee, sizeof(Employee), 1, tempFile);
    }
    count++;
  }

  // Close the files
  fclose(mainFile);
  fclose(tempFile);

  // Delete the main file
  remove("main.bin");

  // Rename the temp file as the new main file
  rename("temp.bin", "main.bin");

  clearScreen();
  printf("\033[0;32mRecord at index %d has been deleted.\033[0m\n", index);
  deleteRecord();

}

