#include "Person.h"
#include "Address.h"
#include <format>
#include <iostream>
#include <ostream>
#include <string>

const std::string &Person::getFirstName() const { return this->firstName; }
const std::string &Person::getLastName() const { return this->lastName; }
const std::string &Person::getEmailAddress() const { return this->emailAddress; }
const std::string &Person::getPhoneNumber() const { return this->phoneNumber; }
const Address &Person::getAddress() const { return this->address; }

Person::Person(std::string firstName, std::string lastName, std::string emailAddress,
               std::string phoneNumber, Address address)
    : firstName{std::move(firstName)}, lastName{std::move(lastName)},
      emailAddress{std::move(emailAddress)}, phoneNumber{std::move(phoneNumber)},
      address{std::move(address)} {}

bool Person::operator<(const Person &other) const {
    if (lastName != other.lastName) {
        return lastName < other.lastName;
    }

    if (firstName != other.firstName) {
        return firstName < other.firstName;
    }

    if (emailAddress != other.emailAddress) {
        return emailAddress < other.emailAddress;
    }

    if (phoneNumber != other.phoneNumber) {
        return phoneNumber < other.phoneNumber;
    }

    return address < other.address;
}

bool Person::operator>(const Person &other) const { return other < *this; }

std::string Person::toString() const {
    return std::format("{} {} \n{} \n{} \n{}", firstName, lastName, phoneNumber, emailAddress,
                       address.toString());
}

void Person::print() const { std::cout << toString() << std::endl; }
void printPersonList(std::shared_ptr<std::vector<Person>> list) {
    for (const auto &p : *list) {
        p.print();
        std::cout << "------------------" << std::endl;
    }
}
