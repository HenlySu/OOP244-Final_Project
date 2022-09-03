#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
   unsigned int const MAX_MENU_ITEMS = 10;

   class Menu;
   class MenuItem {
      char* m_item;

      friend Menu;

      //Constructor
      MenuItem(const char* item);
      ~MenuItem();

      operator bool() const;
      operator const char* () const;
      std::ostream& display(std::ostream& os = std::cout);
   };

   class Menu {
      char* m_menuTitle;
      MenuItem* m_items[MAX_MENU_ITEMS];
      unsigned int m_numPointers;
   public:
      //Constructor
      Menu();
      Menu(const char* title);
      ~Menu();

      std::ostream& displayTitle(std::ostream& os = std::cout) const;
      std::ostream& display(std::ostream& os = std::cout) const;

      unsigned int run();

      unsigned int operator ~ ();
      Menu& operator << (const char* menuItem);

      operator int() const;
      operator unsigned int() const;

      operator bool() const;
      char* operator [] (int i) const;

      std::ostream& output(std::ostream& os = std::cout) const;
   };
   std::ostream& operator << (std::ostream& os, const Menu& menu);
}
#endif // !SDDS_MENU_H
