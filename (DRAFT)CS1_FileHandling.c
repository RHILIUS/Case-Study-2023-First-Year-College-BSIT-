#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// STRUCT
typedef struct Employee {
  char num[20];
  char name[30];
  char statusCode;
  float hoursWorked;
  float deductions;
  float basicSalary;
  float basicRate;
  float overtimePay;
  float basicPay;

} Employee;

// FUNCTION
void createEmployee();
void displayInfo();


int main() {
  system("cls");
  // createEmployee();
  Employee employee;
  strcpy(employee.num, "2022");
  strcpy(employee.name, "Rhian");
  employee.statusCode = 'C';
  employee.hoursWorked = 160;
  employee.deductions = 50;
  displayInfo(employee);

  return 0;
}

void createEmployee() {

  Employee newEmployee;

  printf("Enter employee number: ");
  gets(newEmployee.num);
  printf("Enter employee name: ");
  gets(newEmployee.name);
  printf("Enter status code (R for Regular, C for Casual): ");
  scanf("%c", &newEmployee.statusCode);
  printf("Enter hours worked: ");
  scanf("%f", &newEmployee.hoursWorked);
  printf("Enter deductions: ");
  scanf("%f", &newEmployee.deductions);
  
}

void displayInfo(Employee employee) {
  printf("                             PROGRIZZ COMPANY\n");
  printf("                                Quezon City\n\n");
  printf("                                   Payroll\n");
  printf("Employee    Employee    Status    Basic    Overtime    Deductions    Net\n");
  printf("Number      Name                  Salary   Pay                       Pay\n\n");
  printf("%-12s%-12s%-10c%-9.2f%-12.2f%-14.2f%.2f", employee.num,employee.name,employee.statusCode,employee.basicSalary,employee.overtimePay, employee.deductions,0.00); 

}



