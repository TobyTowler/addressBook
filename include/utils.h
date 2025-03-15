#pragma once

#include "AddressBook.h"
#include <string>

AddressBook readFile(std::string filePath);
AddressBook readAddressBookFromFile(const std::string &filePath);
void runAddressBookRepl(AddressBook &addressBook);
