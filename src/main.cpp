#include "AddressBook.h"
#include "utils.h"
int main() {

    AddressBook book = readAddressBookFromFile("../AddressBook.txt");
    runAddressBookRepl(book);
}
