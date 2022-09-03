#ifndef _BOOK_H_
#define _BOOK_H_

#include "Publication.h"

namespace sdds {
   class Book : public Publication{
      char* authorName;
   public:
      //Constructor
      Book();

      //Rule of three
      Book(const Book& book);
      Book& operator = (const Book& book);
      ~Book();

      //Overides

      char type()const;

      std::ostream& write(std::ostream& os) const;
      std::istream& read(std::istream& istr);

      void set(int member_id);

      operator bool() const;
   };
}
#endif // !_BOOK_H_
