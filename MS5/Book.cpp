#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "Book.h"
#include <cstring>

namespace sdds {
   Book::Book() {
      authorName = nullptr;
   }

   //Rule of three
   Book::Book(const Book& book) {
      authorName = nullptr;
      *this = book;
   }
   Book& Book::operator = (const Book& book) {
      if (this != &book) {
         if (book) {
            delete[] authorName;
            Publication::operator = (book);

            authorName = new char[strlen(book.authorName) + 1];
            strcpy(authorName, book.authorName);
         }
      }
      return *this;
   }
   Book::~Book() {
      delete[] authorName;
      authorName = nullptr;
   }

   //Overides
   char Book::type()const {
      return 'B';
   }

   std::ostream& Book::write(std::ostream& ostr) const {
      if (this->authorName != nullptr) {
         Publication::write(ostr);
         if (conIO(ostr)) {
            if (strlen(this->authorName) > SDDS_AUTHOR_WIDTH) {
               ostr << " ";
               ostr.write(this->authorName, SDDS_AUTHOR_WIDTH) << " |";
            }
            else {
               ostr << " " << std::setw(SDDS_AUTHOR_WIDTH) << std::setfill(' ') << std::left << this->authorName << " |";
            }
         }
         else {
            ostr << '\t' << this->authorName;
         }
      }
      return ostr;
   }
   std::istream& Book::read(std::istream& istr) {
      char tempAuthorName[256];
      Publication::read(istr);

      delete[] authorName;
      authorName = nullptr;

      if (conIO(istr)) {
         istr.get();
         std::cout << "Author: ";
         istr.getline(tempAuthorName, 256, '\n');
      }
      else {
         istr.get();
         istr.getline(tempAuthorName, 256, '\n');
      }

      if (!istr.fail()) {
         authorName = new char[strlen(tempAuthorName) + 1];
         strcpy(authorName, tempAuthorName);
      }
      return istr;
   }

   void Book::set(int member_id) {
      Publication::set(member_id);
      resetDate();
   }

   Book::operator bool() const {
      return authorName && authorName[0] && Publication::operator bool();
   }
}