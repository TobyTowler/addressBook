#pragma once
#include <string>

enum class Country { UK, SPAIN, FRANCE };

class Address {
  public:
    Address() = default;

    Address(std::string street, std::string town, std::string postCode, int houseNumber,
            Country country);

    bool operator<(const Address &other) const;
    bool operator>(const Address &other) const;

    const std::string &getStreet() const { return street; }
    const std::string &getTown() const { return town; }
    const std::string &getPostCode() const { return postCode; }
    int getHouseNumber() const { return houseNumber; }
    Country getCountry() const { return country; }

    void setStreet(std::string newStreet) { street = std::move(newStreet); }
    void setTown(std::string newTown) { town = std::move(newTown); }
    void setPostCode(std::string newPostCode) { postCode = std::move(newPostCode); }
    void setHouseNumber(int newHouseNumber) { houseNumber = newHouseNumber; }
    void setCountry(Country newCountry) { country = newCountry; }

    const std::string toString() const;

    std::string street;
    std::string town;
    std::string postCode;
    int houseNumber;
    Country country;
};

std::string countryToString(Country c);
