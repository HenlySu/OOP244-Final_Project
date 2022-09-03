#ifndef _PUBLICATION_H_
#define _PUBLICATION_H_

#include "Streamable.h"
#include "Date.h"
#include "Lib.h"

namespace sdds {
   class Publication : public Streamable {
      char* m_title;
      char m_shelfId[SDDS_SHELF_ID_LEN + 1];
      int m_membership;
      int m_libRef;
      Date m_date;

   public:
      //Default Constructor
      Publication();

      //Rule of three
      Publication(Publication& publication);
      Publication& operator = (const Publication& publication);
      virtual ~Publication();    //hmmmmm

      //Methods
      virtual void set(int member_id);
      void setRef(int value);
      void resetDate();

      //Queries
      virtual char type()const;
      bool onLoan()const;
      Date checkoutDate()const;
      bool operator==(const char* title)const;
      operator const char* ()const;
      int getRef()const;

      //Streamable pure virtual functions
      bool conIO(std::ios& io) const;
      std::ostream& write(std::ostream& os) const;
      std::istream& read(std::istream& istr);
      operator bool() const;
   };
}
#endif // !_PUBLICATION_H_
