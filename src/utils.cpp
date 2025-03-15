#include "utils.h"
#include "Address.h"
#include "AddressBook.h"
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

Country parseCountry(const std::string &countryStr) {
    if (countryStr == "UK" || countryStr == "uk")
        return Country::UK;
    if (countryStr == "FRANCE" || countryStr == "France" || countryStr == "france")
        return Country::FRANCE;
    if (countryStr == "SPAIN" || countryStr == "Spain" || countryStr == "spain")
        return Country::SPAIN;
    throw std::runtime_error("Invalid country. Must be UK, France, or Spain");
}

void removePerson(AddressBook &book, const std::string &name) {
    auto matches = book.findByName(name);

    if (matches->empty()) {
        std::cout << "No matching entries found.\n";
        return;
    }

    if (matches->size() > 1) {
        std::cout << "Found " << matches->size() << " matching entries:\n";
        for (size_t i = 0; i < matches->size(); i++) {
            std::cout << "\n[" << i + 1 << "]\n";
            (*matches)[i].print();
        }

        std::cout << "\nEnter the number of the person to remove (1-" << matches->size()
                  << ") or 0 to cancel: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice <= 0 || choice > static_cast<int>(matches->size())) {
            std::cout << "Removal canceled.\n";
            return;
        }

        try {
            Person &selectedPerson = (*matches)[choice - 1];
            book.removePerson(selectedPerson);
            std::cout << "Successfully removed " << selectedPerson.getFirstName() << " "
                      << selectedPerson.getLastName() << " from the address book.\n";
        } catch (const std::exception &e) {
            std::cout << "Error removing person: " << e.what() << std::endl;
        }
    } else {
        try {
            Person &selectedPerson = (*matches)[0];
            std::cout << "Found person to remove:\n";
            selectedPerson.print();

            std::cout << "\nAre you sure you want to remove this person? (y/n): ";
            std::string confirmation;
            std::getline(std::cin, confirmation);

            if (confirmation == "y" || confirmation == "Y") {
                book.removePerson(selectedPerson);
                std::cout << "Successfully removed " << selectedPerson.getFirstName() << " "
                          << selectedPerson.getLastName() << " from the address book.\n";
            } else {
                std::cout << "Removal canceled.\n";
            }
        } catch (const std::exception &e) {
            std::cout << "Error removing person: " << e.what() << std::endl;
        }
    }
}

AddressBook readAddressBookFromFile(const std::string &filePath) {
    std::ifstream file("../books/" + filePath);
    if (!file.is_open()) {
        return AddressBook();
    }

    AddressBook addressBook;
    std::string line;

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName, phoneNumber, email;
        std::string street, town, postCode, countryStr;
        std::string houseNumStr;

        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        std::getline(ss, houseNumStr, ',');
        std::getline(ss, street, ',');
        std::getline(ss, town, ',');
        std::getline(ss, postCode, ',');
        std::getline(ss, countryStr);

        int houseNumber = std::stoi(houseNumStr);

        Country country = parseCountry(countryStr);

        Address address(street, town, postCode, houseNumber, country);
        Person person(firstName, lastName, email, phoneNumber, address);

        // Add to address book
        addressBook.addPerson(person);
    }

    return addressBook;
}

void writeAddressBookToFile(const std::string &filePath, const AddressBook &addressBook) {
    std::ofstream file("../books/" + filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath);
    }

    file << "FirstName,LastName,PhoneNumber,Email,HouseNumber,Street,Town,PostCode,Country\n";

    for (const auto &person : addressBook.book) {
        const Address &address = person.getAddress();

        file << person.getFirstName() << "," << person.getLastName() << ","
             << person.getPhoneNumber() << "," << person.getEmailAddress() << ","
             << address.getHouseNumber() << "," << address.getStreet() << "," << address.getTown()
             << "," << address.getPostCode() << "," << countryToString(address.getCountry())
             << "\n";
    }
}

void exportContact(AddressBook book, std::string &name) {

    std::shared_ptr<std::vector<Person>> people = book.findByName(name);

    if (people->empty()) {
        throw std::runtime_error("Contact does not exist");
    }

    std::ofstream file("../books/contacts/" + name + ".txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + name);
    }

    for (const auto &person : *people) {
        const Address &address = person.getAddress();

        file << person.getFirstName() << "," << person.getLastName() << ","
             << person.getPhoneNumber() << "," << person.getEmailAddress() << ","
             << address.getHouseNumber() << "," << address.getStreet() << "," << address.getTown()
             << "," << address.getPostCode() << "," << countryToString(address.getCountry())
             << "\n";
    }
}

void importContact(AddressBook book, std::string &name) {
    std::ifstream file("../books/" + name);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot find person to import");
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName, phoneNumber, email;
        std::string street, town, postCode, countryStr;
        std::string houseNumStr;

        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        std::getline(ss, houseNumStr, ',');
        std::getline(ss, street, ',');
        std::getline(ss, town, ',');
        std::getline(ss, postCode, ',');
        std::getline(ss, countryStr);

        int houseNumber = std::stoi(houseNumStr);

        Country country = parseCountry(countryStr);

        Address address(street, town, postCode, houseNumber, country);
        Person person(firstName, lastName, email, phoneNumber, address);

        // Add to address book
        book.addPerson(person);
    }
}

void printHelp() {
    std::cout << "\nAvailable commands:\n"
              << "  add                    - Add a new person\n"
              << "  remove name X          - Remove a person (will show matches first)\n"
              << "  find name X            - Find people by first or last name\n"
              << "  find phone X           - Find person by phone number\n"
              << "  find email X           - Find person by email address\n"
              << "  find town X            - Find people by town\n"
              << "  find country X         - Find people by country (UK/France/Spain)\n"
              << "  print                  - Display all entries\n"
              << "  save filename          - Save address book to file\n"
              << "  load filename          - Load address book from file\n"
              << "  export name            - Export person to address book\n"
              << "  import name            - import person to address book\n"
              << "  help                   - Show this help message\n"
              << "  exit                   - Exit the program\n"
              << std::endl;
}

void addPersonInteractive(AddressBook &book) {
    std::string firstName, lastName, email, phone;
    std::string street, town, postCode, countryStr;
    int houseNumber;

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);

    std::cout << "Enter house number: ";
    std::cin >> houseNumber;
    std::cin.ignore();

    std::cout << "Enter street: ";
    std::getline(std::cin, street);
    std::cout << "Enter town: ";
    std::getline(std::cin, town);
    std::cout << "Enter post code: ";
    std::getline(std::cin, postCode);
    std::cout << "Enter country (UK/France/Spain): ";
    std::getline(std::cin, countryStr);

    try {
        Country country = parseCountry(countryStr);
        Address address(street, town, postCode, houseNumber, country);
        Person person(firstName, lastName, email, phone, address);
        book.addPerson(person);
        std::cout << "Person added successfully!\n";
    } catch (const std::exception &e) {
        std::cout << "Error adding person: " << e.what() << std::endl;
    }
}

void processCommand(const std::string &command, std::string args, AddressBook &book) {
    if (command == "help") {
        printHelp();
    } else if (command == "add") {
        addPersonInteractive(book);
    } else if (command == "remove") {
        std::string type, name;
        std::stringstream ss(args);
        ss >> type >> name;

        if (type != "name" || name.empty()) {
            std::cout << "Invalid remove command. Use 'remove name <name>' to remove a person.\n";
            return;
        }
        removePerson(book, name);
    } else if (command == "print") {
        book.printAddressBook();
    } else if (command == "find") {
        std::string type;
        std::string value;
        std::stringstream ss(args);
        ss >> type >> value;

        std::shared_ptr<std::vector<Person>> results;

        if (type == "name") {
            results = book.findByName(value);
        } else if (type == "phone") {
            results = book.findByNumber(value);
        } else if (type == "email") {
            results = book.findByemailAddress(value);
        } else if (type == "town") {
            results = book.findByTown(value);
        } else if (type == "country") {
            try {
                Country country = parseCountry(value);
                results = book.findByCountry(country);
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
                return;
            }
        } else {
            std::cout << "Invalid find command. Use 'help' for usage.\n";
            return;
        }

        if (results->empty()) {
            std::cout << "No matching entries found.\n";
        } else {
            std::cout << "Found " << results->size() << " matching entries:\n";
            printPersonList(results);
        }
    } else if (command == "save") {
        try {
            writeAddressBookToFile(args, book);
            std::cout << "Address book saved to " << args << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Error saving file: " << e.what() << std::endl;
        }
    } else if (command == "load") {
        try {
            book = readAddressBookFromFile(args);
            std::cout << "Address book loaded from " << args << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Error loading file: " << e.what() << std::endl;
        }
    } else if (command == "export") {
        try {
            exportContact(book, args);
            std::cout << "Contact " << args << " exported" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Error exporting person " << e.what() << std::endl;
        }
    }

    else {
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

void runAddressBookRepl(AddressBook &addressBook) {
    std::cout << "Welcome to Address Book Manager!\n";
    printHelp();

    while (true) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            writeAddressBookToFile("AddressBook.txt", addressBook);
            break;
        }

        std::stringstream ss(input);
        std::string command;
        ss >> command;

        std::string remaining;
        std::getline(ss, remaining);
        if (!remaining.empty() && remaining[0] == ' ') {
            remaining = remaining.substr(1);
        }

        processCommand(command, remaining, addressBook);
    }

    std::cout << "Goodbye!\n";
}
