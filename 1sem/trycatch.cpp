#include <iostream>

int GCD(int x, int y){
/*
	Реализуемый в этой функции алгоритм требует на входе положительные числа.
	Если один из входных параметров 0, то получится бесконечный цикл.
	Если один из входных параметров отрицательный может получиться бесконечный цикл.
	Так как в функции не известно, что делать в случае, если параметры не корректные, 
	то будем бросать исключение, которое будет обрабатываться там, где функция вызывалась.
	Ради эксперимента будем генерировать исключения разного типа.
*/
	if (x<0) throw "First argument is negative";
	if (y<0) throw "Second argument is negative";
	if (x==0 || y==0) throw 0;

	while (x!=y){
		if (x>y)
			x-=y;
		else
			y-=x;
	}
	return x;
}

void tester(){
	// Протестируем функцию GCD с разными значениями аргументов,
	// но отлавливать будем только исключения типа (const char *)

	std::cout << "step 1" << std::endl;
	try{
		GCD(10, 20);    // Здесь исключение не должны генерироваться
	}catch(const char * error){
		std::cout<<"tester: " << error << std::endl;
	}

	std::cout << "step 2" << std::endl;
	try{
		GCD(10, -20);   // Здесь генерируется исключение и должны увидеть сообщение об ошибке
	}catch(const char * error){
		std::cout<<"tester: " << error << std::endl;
	}

	std::cout << "step 3" << std::endl;
	try{
		GCD(10, 0);    // Здесь генерируется исключение, которое не обрабатывается в функции tester.
					   
	}catch(const char * error){
		std::cout<<"tester: " << error << std::endl;
	}

	std::cout << "step 4" << std::endl; // Этого мы уже не увидим, так на 3-м шаге было исключение типа int, 
										// которое не обрабатывалось в функции tester и сообщение о возникшем исключении "полетело" дальше. 
	try{
		GCD(0, 0);     // Здесь могло бы генерироваться исключение, но до этой строки мы не доходим из-за step 3
	}catch(const char * error){
		std::cout<<"tester: " << error << std::endl;
	}

}

int main(){
	try{
		tester();
	} catch(...) {
		// Здесь будут отлавливаться исключения любого типа.
		// В частности сдесь будет словлено исключение типа int, которое возникло на шаге 3 в tester.
		std::cout<< "Something happend."<<std::endl;
	}

	int x,y;
	while(true){
		std::cout << "x = ";
		std::cin >> x;
		std::cout << "y = ";
		std::cin >> y;
		
		try{
			std::cout<<"GCD(x,y) = " << GCD(x,y)<<std::endl;
		}
		catch(int error){   // Для каждого типа исключений можем поставить свой обработчик. Этот, например, для исключений типа int.
				std::cout<<"Error: "<<error<<std::endl;
		}
		catch (const char* error){ // А этот для типа (const char *)
				std::cout<<"Error. "<<error<<std::endl;
		}
		catch(...){   // Здесь будут обрабатываться все остальные исключения
			std::cout<<"Unknown error." <<std::endl;
		}

	}


	return 0;
}