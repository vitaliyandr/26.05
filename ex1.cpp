#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

const int MAX_EMPLOYEES = 100;

struct Employee {
    std::string lastName;
    std::string firstName;
    int age;
};

void saveEmployeesToFile(Employee employees[], int count, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < count; i++) {
            file << employees[i].lastName << "," << employees[i].firstName << "," << employees[i].age << "\n";
        }
        file.close();
        std::cout << "Employee list saved to file: " << filename << std::endl;
    }
    else {
        std::cout << "Failed to open file for saving employees: " << filename << std::endl;
    }
}

int main() {
    std::string filename = "employees.txt";
    Employee employees[MAX_EMPLOYEES];
    int count = 0;

    // Load employee list from file
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::string lastName, firstName;
            int age;
            size_t commaPos1 = line.find(',');
            size_t commaPos2 = line.find(',', commaPos1 + 1);
            lastName = line.substr(0, commaPos1);
            firstName = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            age = std::stoi(line.substr(commaPos2 + 1));
            employees[count] = { lastName, firstName, age };
            count++;
        }
        file.close();
        std::cout << "Employee list loaded from file: " << filename << std::endl;
    }
    else {
        std::cout << "Failed to open file for loading employees: " << filename << std::endl;
    }

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add employee" << std::endl;
        std::cout << "2. Edit employee data" << std::endl;
        std::cout << "3. Delete employee" << std::endl;
        std::cout << "4. Search employee by last name" << std::endl;
        std::cout << "5. Print information about employees of a certain age" << std::endl;
        std::cout << "6. Print information about employees whose last name starts with a specific letter" << std::endl;
        std::cout << "7. Exit program" << std::endl;
        std::cout << "Enter option number: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string lastName, firstName;
            int age;
            std::cout << "Enter last name: ";
            std::cin >> lastName;
            std::cout << "Enter first name: ";
            std::cin >> firstName;
            std::cout << "Enter age: ";
            std::cin >> age;

            if (count < MAX_EMPLOYEES) {
                employees[count] = { lastName, firstName, age };
                count++;
                std::cout << "Employee added" << std::endl;
            }
            else {
                std::cout << "Maximum number of employees reached" << std::endl;
            }
        }
        else if (choice == 2) {
            int index;
            std::cout << "Enter index of employee to edit: ";
            std::cin >> index;
            if (index >= 0 && index < count) {
                std::string lastName, firstName;
                int age;
                std::cout << "Enter new last name: ";
                std::cin >> lastName;
                std::cout << "Enter new first name: ";
                std::cin >> firstName;
                std::cout << "Enter new age: ";
                std::cin >> age;

                employees[index].lastName = lastName;
                employees[index].firstName = firstName;
                employees[index].age = age;

                std::cout << "Employee data updated" << std::endl;
            }
            else {
                std::cout << "Invalid employee index" << std::endl;
            }
        }
        else if (choice == 3) {
            int index;
            std::cout << "Enter index of employee to delete: ";
            std::cin >> index;
            if (index >= 0 && index < count) {
                for (int i = index; i < count - 1; i++) {
                    employees[i] = employees[i + 1];
                }
                count--;
                std::cout << "Employee deleted" << std::endl;
            }
            else {
                std::cout << "Invalid employee index" << std::endl;
            }
        }
        else if (choice == 4) {
            std::string searchLastName;
            std::cout << "Enter last name to search for: ";
            std::cin >> searchLastName;

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (employees[i].lastName == searchLastName) {
                    std::cout << "Found employee:" << std::endl;
                    std::cout << "Last Name: " << employees[i].lastName << std::endl;
                    std::cout << "First Name: " << employees[i].firstName << std::endl;
                    std::cout << "Age: " << employees[i].age << std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "No employees found with last name: " << searchLastName << std::endl;
            }
        }
        else if (choice == 5) {
            int searchAge;
            std::cout << "Enter age to search for: ";
            std::cin >> searchAge;

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (employees[i].age == searchAge) {
                    std::cout << "Employee:" << std::endl;
                    std::cout << "Last Name: " << employees[i].lastName << std::endl;
                    std::cout << "First Name: " << employees[i].firstName << std::endl;
                    std::cout << "Age: " << employees[i].age << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No employees found with age: " << searchAge << std::endl;
            }
        }
        else if (choice == 6) {
            char searchLetter;
            std::cout << "Enter the letter to search for: ";
            std::cin >> searchLetter;

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (employees[i].lastName[0] == std::tolower(searchLetter) || employees[i].lastName[0] == std::toupper(searchLetter)) {
                    std::cout << "Employee:" << std::endl;
                    std::cout << "Last Name: " << employees[i].lastName << std::endl;
                    std::cout << "First Name: " << employees[i].firstName << std::endl;
                    std::cout << "Age: " << employees[i].age << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No employees found with last name starting with the letter: " << searchLetter << std::endl;
            }
        }
        else if (choice == 7) {
            saveEmployeesToFile(employees, count, filename);
            break;
        }
        else {
            std::cout << "Invalid option number. Please try again." << std::endl;
        }
    }

    return 0;
}
