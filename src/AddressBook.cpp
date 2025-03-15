#include "AddressBook.h"
#include "utils.h"
#include <format>
#include <iostream>
#include <stdexcept>

void AddressBook::addPerson(Person &p) {
    auto [iter, inserted] = book.insert(p);
    if (!inserted) {
        throw std::runtime_error("Cannot add duplicate person");
    }
}

void AddressBook::removePerson(Person &p) {
    auto iter = book.erase(p);
    if (!iter) {
        throw std::runtime_error("Cannot remove person that does not exist");
    }
}

void AddressBook::printAddressBook() const {
    if (book.empty()) {
        std::cout << "Address book is empty." << std::endl;
        return;
    }

    std::cout << "===== ADDRESS BOOK CONTENTS =====" << std::endl;

    for (const auto &p : book) {
        p.print();
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << std::format("Total contacts: {}", book.size()) << std::endl;
    std::cout << "=================================" << std::endl;
}

std::shared_ptr<std::vector<Person>> AddressBook::findByName(const std::string &name) {
    std::shared_ptr<std::vector<Person>> results = std::make_shared<std::vector<Person>>();
    for (const auto &person : book) {
        if (person.getFirstName() == name || person.getLastName() == name) {
            results->push_back(person);
        }
    }
    return results;
}

std::shared_ptr<std::vector<Person>> AddressBook::findByNumber(const std::string &number) {
    std::shared_ptr<std::vector<Person>> results = std::make_shared<std::vector<Person>>();
    for (const auto &person : book) {
        if (person.getPhoneNumber() == number) {
            results->push_back(person);
        }
    }
    return results;
}

std::shared_ptr<std::vector<Person>> AddressBook::findByemailAddress(const std::string &email) {
    std::shared_ptr<std::vector<Person>> results = std::make_shared<std::vector<Person>>();
    for (const auto &person : book) {
        if (person.getEmailAddress() == email) {
            results->push_back(person);
        }
    }
    return results;
}

std::shared_ptr<std::vector<Person>> AddressBook::findByTown(const std::string &town) {
    std::shared_ptr<std::vector<Person>> results = std::make_shared<std::vector<Person>>();
    for (const auto &person : book) {
        if (person.getAddress().town == town) {
            results->push_back(person);
        }
    }
    return results;
}

std::shared_ptr<std::vector<Person>> AddressBook::findByCountry(Country country) {
    std::shared_ptr<std::vector<Person>> results = std::make_shared<std::vector<Person>>();
    for (const auto &person : book) {
        if (person.getAddress().country == country) {
            results->push_back(person);
        }
    }
    return results;
}
