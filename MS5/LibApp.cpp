#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstring>
#include "LibApp.h"

namespace sdds {
   //Constructor
   LibApp::LibApp(const char* fileName) {
      if (fileName && fileName[0]) strcpy(m_fileName, fileName); else m_fileName[0] = '\0';

      for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++) {
         m_ppa[i] = nullptr;
      }

      m_nolp = 0;
      m_llrn = 0;

      typeSelection << "Book" <<
         "Publication";

      m_changed = false;

      m_mainMenu << "Add New Publication" <<
         "Remove Publication" <<
         "Checkout publication from library" <<
         "Return publication to library";

      m_exitMenu << "Save changes and exit" <<
         "Cancel and go back to the main menu";
   }

   LibApp::~LibApp() {
      for (int i = 0; i < this->m_nolp; i++) {
         delete this->m_ppa[i];
      }
   }

   //Private Methods
   Publication* LibApp::getPub(int libref) {
      for (int i = 0; i < this->m_nolp; i++) {
         if (this->m_ppa[i]->getRef() == libref) {
            return this->m_ppa[i];
         }
      }
      return nullptr;
   }

   bool LibApp::confirm(const char* message) {
      Menu menu(message);
      menu << "Yes";
      return menu.run() == 1;
   }

   void LibApp::save() {
      std::cout << "Saving Data" << std::endl;
      std::ofstream fp(this->m_fileName);
      if (fp) {
         for (int i = 0; i < m_nolp; i++) {
            if (m_ppa[i]->getRef() != 0) {
               fp << *m_ppa[i] << std::endl;
            }
         }
      }
   }

   void LibApp::load() {
      std::cout << "Loading Data" << std::endl;
      std::ifstream fp(m_fileName);

      char character = '\0';

      for (int i = 0; fp; i++) {
         fp >> character;
         if (fp) {
            switch (character)
            {
            case 'P':
               m_ppa[i] = new Publication;
               break;

            case 'B':
               m_ppa[i] = new Book;
               break;
            }
            if (m_ppa[i]) {
               fp >> *m_ppa[i];
               m_nolp++;
            }
            if (std::cin.fail()) {
               delete m_ppa[i];
            }
         }
      }
      m_llrn = m_ppa[m_nolp - 1]->getRef();
   }

   int LibApp::search(int num) {
      PublicationSelector pSelector("Select one of the following found matches:");
      int selection = typeSelection.run();
      char type{}, title[256];
      int reference = 0;

      switch (selection) {
      case 1:
         type = 'B';
         break;
      case 2:
         type = 'P';
         break;
      }

      std::cout << "Publication Title: ";
      std::cin.ignore();
      std::cin.getline(title, 256);

      for (int i = 0; i < m_nolp; i++) {
         switch (num) {
         case 1:
            if (strstr(*m_ppa[i], title) && type == m_ppa[i]->type()) {
               pSelector << this->m_ppa[i];
            }
            break;
         case 2:
            if (strstr(*m_ppa[i], title) && m_ppa[i]->onLoan() && type == m_ppa[i]->type()) {
               pSelector << m_ppa[i];
            }
            break;
         case 3:
            if (strstr(*m_ppa[i], title) && !m_ppa[i]->onLoan() && type == m_ppa[i]->type()) {
               pSelector << m_ppa[i];
            }
            break;
         }
      }

      if (pSelector) {
         pSelector.sort();
         int ref = pSelector.run();
         if (ref) {
            reference = ref;
            std::cout << *getPub(ref) << std::endl;
         }
         else {
            std::cout << "Aborted!" << std::endl;
         }
      }
      else {
         std::cout << "No matches found!" << std::endl;
      }
      return reference;
   }

   void LibApp::returnPub() {
      std::cout << "Return publication to the library" << std::endl;
      int selection = search(2),
         daysLoan = Date() - getPub(selection)->checkoutDate(),
         daysOverDue = daysLoan - SDDS_MAX_LOAN_DAYS;

      double penalty = (daysOverDue) * 0.50;
      
      if (selection) {
         if (confirm("Return Publication?")) {
            if (daysLoan > SDDS_MAX_LOAN_DAYS) {
               std::cout << "Please pay $";
               std::cout.setf(std::ios::fixed);
               std::cout.precision(2);
               std::cout << penalty << " penalty for being " << daysOverDue << " days late!" << std::endl;
               std::cout.unsetf(std::ios::fixed);
            }
            getPub(selection)->set(0);
            m_changed = true;
            std::cout << "Publication returned" << std::endl;
         }
      }
   }

   void LibApp::newPublication() {
      if (m_nolp < SDDS_LIBRARY_CAPACITY) {
         Publication* temp;
         std::cout << "Adding new publication to the library" << std::endl;
         int type = typeSelection.run();

         switch (type)
         {
         case 1:
            temp = new Book();
            break;
         case 2:
            temp = new Publication();
            break;
         default:
            std::cout << "Aborted!" << std::endl;
            return;
            break;
         }

         std::cin >> *temp;

         if (!std::cin.fail()) {
            if (confirm("Add this publication to the library?")) {
               if (temp->operator bool()) {
                  temp->setRef(++m_llrn);
                  m_ppa[m_nolp++] = temp;
                  m_changed = true;
                  std::cout << "Publication added" << std::endl;
               }
               else {
                  std::cout << "Failed to add publication!" << std::endl;
                  delete temp;
               }
            }
            else {
               std::cout << "Aborted!" << std::endl;
               delete temp;
            }
         }
         else {
            std::cin.ignore(1000, '\n');
            std::cout << "Aborted!" << std::endl;
            delete temp;
         }
      }
      else {
         std::cout << "Library is at its maximum capacity!" << std::endl;
         return;
      }
   }

   void LibApp::removePublication() {
      std::cout << "Removing publication from the library" << std::endl;
      int selecation = search(1);
      if (selecation) {
         if (confirm("Remove this publication from the library?")) {
            getPub(selecation)->setRef(0);
            m_changed = true;
            std::cout << "Publication removed" << std::endl;
         }
      }
   }

   void LibApp::checkOutPub() {
      std::cout << "Checkout publication from the library" << std::endl;
      unsigned int membershipNumber = 0;
      int selection = search(3);
      bool flag = false;

      if (selection) {
         if (confirm("Check out publication?")) {

            std::cout << "Enter Membership number: ";
            do {
               std::cin >> membershipNumber;
               if (std::cin.fail()) {
                  std::cin.clear();
                  std::cin.ignore(1000, '\n');
                  std::cout << "Invalid membership number, try again: ";
               }
               else if (std::cin.get() != '\n') {
                  std::cin.ignore(1000, '\n');
                  std::cout << "Invalid membership number, try again: ";
               }
               else if (membershipNumber < 10000 || membershipNumber > 99999) {
                  std::cout << "Invalid membership number, try again: ";
               }
               else {
                  flag = true;
               }
            } while (!flag);

            getPub(selection)->set(membershipNumber);
            m_changed = true;
            std::cout << "Publication checked out" << std::endl;
         }
      }
   }

   void LibApp::run() {
      bool end = false;

      if (m_fileName[0] != '\0') load();

      while (!end) {
         int selection = m_mainMenu.run();
         switch (selection) {
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
            int selection2 = m_exitMenu.run();
            switch (selection2)
            {
            case 1:
               save();
               end = true;
               break;
            case 2:
               std::cout << std::endl;
               break;
            case 0:
               if (confirm("This will discard all the changes are you sure?")) {
                  end = true;
               }
               break;
            }
         }
      }
      std::cout << std::endl << "-------------------------------------------" << std::endl;
      std::cout << "Thanks for using Seneca Library Application" << std::endl;
   }
}