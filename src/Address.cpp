#include "Address.h"
#include <format>
#include <stdexcept>
#include <utility>

Address::Address(std::string street, std::string town, std::string postCode, int houseNumber,
                 Country country)
    : street{std::move(street)}, town{std::move(town)}, postCode{std::move(postCode)},
      houseNumber{houseNumber}, country{country} {}

bool Address::operator<(const Address &other) const {
    if (street != other.street) {
        return street < other.street;
    }

    if (town != other.town) {
        return town < other.town;
    }

    if (postCode != other.postCode) {
        return postCode < other.postCode;
    }

    if (houseNumber != other.houseNumber) {
        return houseNumber < other.houseNumber;
    }

    return static_cast<int>(country) < static_cast<int>(other.country);
}

const std::string Address::toString() const {
    return std::format("{} {} \n{} \n{}", houseNumber, street, town, postCode,
                       countryToString(country));
}

bool Address::operator>(const Address &other) const { return other < *this; }

std::string countryToString(Country c) {
    switch (c) {
    case Country::UK:
        return "UK";
    case Country::FRANCE:
        return "France";
    case Country::SPAIN:
        return "Spain";
    default:
        throw std::runtime_error("Invalid country");
    }
}
