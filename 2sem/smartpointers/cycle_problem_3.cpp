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

	const std::shared_ptr<Human> getPartner() const { 
       return m_partner.lock(); // используем метод lock() для конвертации
                                // std::weak_ptr в std::shared_ptr
	} 

	const std::string& getName() const { return m_name; }
};
 
int main()
{
    std::shared_ptr<Human> partner;
    auto ivan = std::make_shared<Human>("Ivan");
	{
  		// создание умного указателя с объектом Anton класса Human 
		auto anton = std::make_shared<Human>("Anton"); 

		partnerUp(anton, ivan);
  		// Anton указывает на Ivan-а, а Ivan указывает на Anton-а

		partner = ivan->getPartner(); // передаем partner-у содержимое 
                                      //умного указателя, которым владеет ivan
	}
	std::cout << ivan->getName() << "'s partner is: " 
            << partner->getName() << '\n';

	return 0;
}
