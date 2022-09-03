#define _CRT_SECURE_NO_WARNINGS

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

   std::ostream& Book::write(std::ostream& os) const {
      Publication::write(os);

      if (conIO(os)) {
         os << " ";
         os.setf(std::ios::left);

         if (strlen(authorName) >= SDDS_AUTHOR_WIDTH) {
            for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
               os << authorName[i];
            }
         }
         else {
            os.width(SDDS_AUTHOR_WIDTH);
            os << authorName;
            os.fill(' ');
         }
         os << " |";
      }
      else {
         os << "\t";
         if (strlen(authorName) >= SDDS_AUTHOR_WIDTH) {
            for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
               os << authorName[i];
            }
         }
         else {
            os.setf(std::ios::left);
            os.width(SDDS_AUTHOR_WIDTH);
            os << authorName;
            os.fill(' ');
         }
      }
      return os;
   }
   std::istream& Book::read(std::istream& istr) {
      char tempAuthorName[256];
      Publication::read(istr);

      delete[] authorName;
      authorName = nullptr;

      if (conIO(istr)) {
         istr.get();
         std::cout << "Author: ";
         istr.get(tempAuthorName, 256);
      }
      else {
         istr.get();
         istr.get(tempAuthorName, 256);
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