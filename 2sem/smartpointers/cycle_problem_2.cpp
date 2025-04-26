#include <memory>
#include <string>
#include <iostream>

class Human {
	std::string m_name;
	std::weak_ptr<Human> m_partner; 
public:
	Human(const std::string &name): m_name(name) { 
		std::cout << m_name << " created\n";
	}
	~Human() {
		std::cout << m_name << " destroyed\n";
	}
 
	friend bool partnerUp(std::shared_ptr<Human> &h1,
                        std::shared_ptr<Human> &h2)
	{
	    if (!h1 || !h2)
		return false;
 
	    h1->m_partner = h2;
	    h2->m_partner = h1;
       std::cout << h1->m_name << " is now partnered with " 
                 << h2->m_name << "\n";
		return true;
	}
};
 
int main()
{
  // создание умного указателя с объектом Anton класса Human 
	auto anton = std::make_shared<Human>("Anton"); 
  
  // создание умного указателя с объектом Ivan класса Human 
	auto ivan = std::make_shared<Human>("Ivan"); 
 
	partnerUp(anton, ivan); 
  // Anton указывает на Ivan-а, а Ivan указывает на Anton-а
 
	return 0;
}
