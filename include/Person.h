#pragma once
#include "Address.h"

#include <memory>
#include <string>
#include <vector>
class Person {
  public:
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getEmailAddress() const;
    const std::string &getPhoneNumber() const;
    const Address &getAddress() const;
    Person(std::string firstName, std::string lastName, std::string emailAddress,
           std::string phoneNumber, Address address);
    bool operator<(const Person &other) const;
    bool operator>(const Person &other) const;
    std::string toString() const;
    void print() const;

  private:
    std::string firstName;
    std::string lastName;
    std::string emailAddress;
    std::string phoneNumber;
    Address address;
};

void printPersonList(std::shared_ptr<std::vector<Person>> list);

namespace std {

template <> struct hash<Person> {
    size_t operator()(const Person &person) const noexcept {
        size_t hashValue = 0;

        hashValue += hash<string>{}(person.getFirstName());
        hashValue += hash<string>{}(person.getLastName());

        const auto &address = person.getAddress();
        hashValue += hash<string>{}(address.street);
        hashValue += hash<string>{}(address.postCode);
        hashValue += hash<int>{}(address.houseNumber);

        return hashValue;
    }
};
} // namespace std
