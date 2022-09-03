#ifndef LIBAPP_H
#define LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "PublicationSelector.h"
#include "Lib.h"
#include "Book.h"

namespace sdds {
   class LibApp{
      char m_fileName[256]{};
      Publication* m_ppa[SDDS_LIBRARY_CAPACITY];
      int m_nolp;
      int m_llrn;
      Menu typeSelection{ "Choose the type of publication:" };
      
      bool m_changed;
      Menu m_mainMenu{ "Seneca Library Application" };
      Menu m_exitMenu{ "Changes have been made to the data, what would you like to do?" };

      //Private Methods
      Publication* getPub(int num);
      bool confirm(const char* message);
      void load();
      void save();
      int search(int num);
      void returnPub();

      void newPublication();
      void removePublication();
      void checkOutPub();

   public:
      LibApp(const char *filename);
      ~LibApp();
      void run();
   };
}
#endif // !LIBAPP_H

