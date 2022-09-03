#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"

namespace sdds {
   std::ostream& operator << (std::ostream& os, const Streamable& RO) {
      if (RO) RO.write(os);
      return os;
   }
   std::istream& operator >> (std::istream& os, Streamable& RO) {
      return RO.read(os);
   }
}