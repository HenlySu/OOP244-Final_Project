#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"

namespace sdds {

   MenuItem::MenuItem(const char* item) {
      if (item && item[0] != '\0') {
      m_item = new char[strlen(item) + 1];
      strcpy(m_item, item);
      }
      else {
         m_item = nullptr;
       }
   }
   MenuItem::~MenuItem() {
      delete[] m_item;
   }
   MenuItem::operator bool() const {
      return (m_item) ? true : false;
   }
   MenuItem::operator const char* () const {
      return m_item;
   }
   std::ostream& MenuItem::display(std::ostream& os) {
      std::cout << m_item;
      return os;
   }

   //Menu
   Menu::Menu() {
      m_menuTitle = nullptr;
      m_numPointers = 0;
   }
   Menu::Menu(const char* title) {
      m_numPointers = 0;
      if (title != nullptr) {
         m_menuTitle = new char[strlen(title) + 1];
         strcpy(m_menuTitle, title);
      }
   }
   Menu::~Menu() {
      delete[] m_menuTitle;
      for (unsigned int i = 0; i < m_numPointers; i++) {
         delete m_items[i];
      }
   }

   std::ostream& Menu::displayTitle(std::ostream& os) const {
      if (m_menuTitle != nullptr) std::cout << m_menuTitle << std::endl;
      return os;
   }
   std::ostream& Menu::display(std::ostream& os) const {
      displayTitle();
      for (unsigned int i = 0; i < m_numPointers; i++) {
         std::cout << " " << i + 1 << "- " << m_items[i]->m_item << std::endl;
      }
      std::cout << " 0- Exit" << std::endl << "> ";
      return os;
   }

   unsigned int Menu::run() {
      display(std::cout);
      unsigned int val = 0;
      bool flag = false;
      do {
         std::cin >> val;
         if (std::cin.fail()) {
            std::cout << "Invalid Selection, try again: ";
            std::cin.clear();
            while (std::cin.get() != '\n');
         }
         else if (val > m_numPointers) {
            std::cout << "Invalid Selection, try again: ";
            std::cin.clear();
            while (std::cin.get() != '\n');
         }
         else flag = true;
      } while (flag == false);
      return val;
   }


   unsigned int Menu::operator ~ () {
      return run();
   }
   Menu& Menu::operator << (const char* menuItem) {
      if (m_numPointers < MAX_MENU_ITEMS) {
         m_items[m_numPointers++] = new MenuItem(menuItem);
      }
      return *this;
   }

   Menu::operator int() const {
      return m_numPointers;
   }
   Menu::operator unsigned int() const {
      return m_numPointers;
   }
   Menu::operator bool() const {
      return (m_menuTitle) ? true : false;
   }
   char* Menu::operator [] (int i) const {
      return m_items[i]->m_item;
   }
   std::ostream& Menu::output(std::ostream& os) const {
      if (m_menuTitle) std::cout << m_menuTitle;
      return os;
   }

   std::ostream& operator << (std::ostream& os, const Menu& menu) {
      return menu.output(os);
   }
};
