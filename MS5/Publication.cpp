#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Publication.h"

namespace sdds {
   //Default Constructor
   Publication::Publication(){
      m_title = nullptr;
      m_shelfId[0] = '\0';
      m_membership = 0;
      m_libRef = -1;
   }

   //Rule of three
   Publication::Publication(Publication& publication){
      m_title = nullptr;
      *this = publication;
   }
   Publication& Publication::operator = (const Publication& publication) {
      if (this != &publication) {
         if (publication) {
            delete[] m_title;

            m_title = new char[strlen(publication.m_title) + 1];
            strcpy(m_title, publication.m_title);
            strcpy(m_shelfId, publication.m_shelfId);
         }
         m_membership = publication.m_membership;
         m_libRef = publication.m_libRef;
         m_date = publication.m_date;
      }
      return *this;
   }
   Publication::~Publication() {
      delete[] m_title;
      m_title = nullptr;
   }

   //Methods
   void Publication::set(int member_id) {
      m_membership = m_membership == 0 ? member_id : 0;
   }
   void Publication::setRef(int value) {
      m_libRef = value;
   }
   void Publication::resetDate() {
      m_date = Date();
   }

   //Queries
   char Publication::type()const {
      return 'P';
   }
   bool Publication::onLoan()const {
      return m_membership != 0 ? true : false;
   }
   Date Publication::checkoutDate()const {
      return m_date;
   }
   bool Publication::operator==(const char* title)const {
      return strstr(m_title, title) != nullptr;
   }
   Publication::operator const char* ()const {
      return m_title;
   }
   int Publication::getRef()const {
      return m_libRef;
   }

   //Streamable pure virtual functions
   bool Publication::conIO(std::ios& io) const {
      return &io == &std::cin || &io == &std::cout;
   }

   std::ostream& Publication::write(std::ostream& os) const {
   if (conIO(os)) {
      os << "| " << std::setw(SDDS_SHELF_ID_LEN) << std::setfill('0') << m_shelfId;
      if (strlen(m_title) > SDDS_TITLE_WIDTH) {
         os << " | ";
         os.write(m_title, SDDS_TITLE_WIDTH) << " | ";
      }
      else {
         os << " | " << std::setw(SDDS_TITLE_WIDTH) << std::setfill('.') << std::left << m_title << " | ";
      }
      if (m_membership) {
         os << m_membership << " | ";
      }
      else {
         os << " N/A  | ";
      }
      os << m_date << " |";
   }
   else {
      os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
   }
      return os;
   }
   std::istream& Publication::read(std::istream& istr) {
      
      //Local Variables
      char tempTitle[100], tempShelfId[100];
      int tempLibRef = 0, tempMembership = 0;
      Date tempDate{};

      //Freeing Memory
      delete[] m_title;

      //Setting everything to default values
      m_title = nullptr;
      m_shelfId[0] = '\0';
      m_membership = 0;
      m_libRef = -1;

      tempTitle[0] = '\0';
      tempShelfId[0] = '\0';

      //Improvising since I dont know whats wrong with my read function.
      int day = 0, month = 0, year = 0;

      if (conIO(istr)) {
         std::cout << "Shelf No: ";
         istr >> tempShelfId;

         if (strlen(tempShelfId) != SDDS_SHELF_ID_LEN) istr.setstate(std::ios::failbit);
         std::cout << "Title: ";
         if (!std::cin.fail()) {
            istr.ignore(1000, '\n');
            istr.getline(tempTitle, 256);
         }

         std::cout << "Date: ";
         //if (!istr.fail()) tempDate.read();         //Not working properly
         if (!istr.fail()) {
            istr >> year;
            istr.ignore(1, '\n');
            istr >> month;
            istr.ignore(1, '\n');
            istr >> day;
            Date tempDate(year, month, day);
            if (tempDate.errCode()) istr.setstate(std::ios_base::failbit);
         }
      }
      else {
         istr >> tempLibRef;
         istr.ignore(1, '\n');
         istr >> tempShelfId;
         istr.ignore(1, '\n');
         istr.getline(tempTitle, 99, '\t');

         istr >> tempMembership;
         //if (!istr.fail()) tempDate.read();         //Not working properly
         istr.ignore(1, '\n');
         istr >> year;
         istr.ignore(1, '\n');
         istr >> month;
         istr.ignore(1, '\n');
         istr >> day;
         Date tempDate(year, month, day);
         if (tempDate.errCode()) istr.setstate(std::ios_base::failbit);
      }
      if (!istr.fail()) {
         m_title = new char[strlen(tempTitle) + 1];
         strcpy(m_title, tempTitle);

         strcpy(m_shelfId, tempShelfId);
         m_membership = tempMembership;

         m_libRef = tempLibRef;

         Date tempDate(year, month, day);
         m_date = tempDate;
         if (tempDate.errCode()) istr.setstate(std::ios_base::failbit);
      }
      return istr;
   }
   Publication::operator bool() const {
      return m_title != nullptr && m_shelfId[0] != '\0';
   }
}