#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include "LibApp.h"

namespace sdds {
   //Constructor
   LibApp::LibApp() {
      m_changed = false;

      m_mainMenu << "Add New Publication" <<
         "Remove Publication" <<
         "Checkout publication from library" <<
         "Return publication to library";

      m_exitMenu << "Save changes and exit" <<
         "Cancel and go back to the main menu";
      load();
   }

   //Private Methods
   bool LibApp::confirm(const char* message) {
      Menu menu(message);
      menu << "Yes";
      return menu.run() == 1;
   }
   void LibApp::load() {
      std::cout << "Loading Data" << std::endl;
   }
   void LibApp::save() {
      std::cout << "Saving Data" << std::endl;
   }
   void LibApp::search() {
      std::cout << "Searching for publication" << std::endl;
   }
   void LibApp::returnPub() {
      search();
      std::cout << "Returning publication" << std::endl;
      std::cout << "Publication returned" << std::endl;
      m_changed = true;
   }
   //------------------------------------------//
   void LibApp::newPublication() {
      std::cout << "Adding new publication to library" << std::endl;
      if (confirm("Add this publication to library?")) {
         m_changed = true;
         std::cout << "Publication added" << std::endl << std::endl;
      }
   }
   void LibApp::removePublication() {
      std::cout << "Removing publication from library" << std::endl;
      search();
      if (confirm("Remove this publication from the library?")) {
         m_changed = true;
         std::cout << "Publication removed" << std::endl;
      }
   }
   void LibApp::checkOutPub() {
      search();
      if (confirm("Check out publication?")) {
         m_changed = true;
         std::cout << "Publication checked out" << std::endl;
      }
   }

   void LibApp::run() {
      bool flag = false;
      do {
         int num = m_mainMenu.run();
         switch (num){
         case 1:
            newPublication();
            std::cout << std::endl;
            break;
         case 2:
            removePublication();
            std::cout << std::endl;
            break;
         case 3:
            checkOutPub();
            std::cout << std::endl;
            break;
         case 4:
            returnPub();
            std::cout << std::endl;
            break;
         case 0:
            if (m_changed) {
               int num2 = m_exitMenu.run();
               switch (num2) {
               case 1:
                  save();
                  flag = true;
                  break;
               case 2:
                  std::cout << std::endl;
                  break;
               case 0:
                  bool ans = confirm("This will discard all the changes are you sure?");
                  ans == true ? flag = true : flag = false;
               }
            }
            else flag = true;
         }
      } while (!flag);
      std::cout << std::endl;
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "Thanks for using Seneca Library Application" << std::endl;
   }
}