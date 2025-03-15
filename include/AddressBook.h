#pragma once
#include "Person.h"
#include <memory>
#include <set>
#include <vector>

class AddressBook {
  public:
    std::set<Person> book;

    void addPerson(Person &p);
    void removePerson(Person &p);
    void printAddressBook() const;
    std::shared_ptr<std::vector<Person>> findByName(const std::string &name);
    std::shared_ptr<std::vector<Person>> findByNumber(const std::string &number);
    std::shared_ptr<std::vector<Person>> findByemailAddress(const std::string &email);
    std::shared_ptr<std::vector<Person>> findByTown(const std::string &town);
    std::shared_ptr<std::vector<Person>> findByCountry(Country country);
};
