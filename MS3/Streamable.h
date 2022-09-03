#ifndef _STREAMABLE_H_
#define _STREAMABLE_H_

#include <iostream>

namespace sdds {
   class Streamable {
   public:
      virtual std::ostream& write(std::ostream& os) const = 0;
      virtual std::istream& read(std::istream& is) = 0;
      virtual bool conIO(std::ios& io) const = 0;
      virtual operator bool() const = 0;
      virtual ~Streamable(){};
   };
   std::ostream& operator << (std::ostream& os, const Streamable& RO);
   std::istream& operator >> (std::istream& os, Streamable& RO);
}
#endif // !_STREAMABLE_H_
