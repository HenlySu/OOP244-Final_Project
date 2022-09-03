#ifndef LIBAPP_H
#define LIBAPP_H
#include "Menu.h"

namespace sdds {
   class LibApp : public Menu{
      bool m_changed;
      Menu m_mainMenu{ "Seneca Library Application" };
      Menu m_exitMenu{ "Changes have been made to the data, what would you like to do?" };

      //Private Methods
      bool confirm(const char* message);
      void load();
      void save();
      void search();
      void returnPub();

      void newPublication();
      void removePublication();
      void checkOutPub();

   public:
      LibApp();
      void run();
   };
}
#endif // !LIBAPP_H

