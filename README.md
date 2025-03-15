# Address Book
a C++ implementation of an address book

## Assumptions
CMake
c++20 compatible compiler
looks for addressbook.txt, if it cannot find this then creates a new book

## Build
```bash
mkdir build
cd build
cmake ..
make
./addressBook
```

## Project structure
include/ - header files
src/ - implementation files
CMakeLists.txt - build file

## How to use
- add - Add a new person to the address book with their contact details and address information
- remove name X - Remove people by searching for the last or first name where X is the name to search for
- find name X - Find people by searching their first or last name, where X is the name to search for
- find phone X - Find a person by their phone number, where X is the phone number to search for
- find email X - Find a person by their email address, where X is the email to search for
- find town X - Find all people living in a specific town, where X is the town name to search for
- find country X - Find all people living in a specific country, where X is either UK, France, or Spain
- print - Display all entries currently stored in the address book with their complete details
- save filename - Save the current address book to a file, where filename is the path to save to
- load filename - Load an address book from a file, where filename is the path to load from
- export name - Export person to address book\n"
- import name - import person to address book\n"
- help - Show the available commands and their descriptions
- exit - Close the address book program and return to the system prompt

## 2 Weeks
- more validation on input data
- better error handling
- unit tests
- delete by other parameters
- find by combinations
