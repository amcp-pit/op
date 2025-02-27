/*
  Большинству программ, имеющих пользовательский интерфейс, необходимо обрабатывать пользовательский ввод. 
  Обычно мы использовали std::cin, чтобы попросить пользователя ввести текст. 
  Поскольку пользователь может ввести что угодно, может оказаться, что пользователь ввёл совсем не то, что бы ожидали.
  Как правильно читать числа с помощью std::cin ?

  Упрощенное представление того, как работает operator>> :
  * Начальные пробелы (пробелы, табуляции и символы новой строки в начале буфера) удаляются из входного буфера. 
    Это отбросит любой неизвлеченный символ новой строки, оставшийся от предыдущей строки ввода.
  * Если входной буфер теперь пуст, operator>> будет ждать, пока пользователь введет больше данных. Начальные пробелы снова отбрасываются.
  * Затем извлекается столько последовательных символов, сколько возможно, пока не встретится символ новой строки (представляющий конец строки ввода) или символ, который недопустим для извлекаемой переменной.

  Если какие-либо символы были извлечены на шаге 3 выше, извлечение считается успешным. 
  Извлеченные символы преобразуются в значение, которое затем присваивается переменной.
  Если на шаге 3 выше не удалось извлечь ни одного символа, извлечение не удалось. 
  Извлекаемому объекту присваивается значение 0, и любые будущие извлечения немедленно завершатся ошибкой (пока std::cin не будет очищено).

  Подробнее: https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
*/

#include <limits> // for std::numeric_limits

void ignoreLine() {
	// std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble() {
    while (true) { // Будем считывать до тех пор, пока пользователь не введет число
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) {
            // Если предыдущее извлечение не удалось
            std::cin.clear(); // Вернемся в режим 'normal'
            ignoreLine();     // Уберем все символы из буфера до \n
            continue;
        }

        ignoreLine(); // Проигнорируем все остальные символы в строке
        return x;
    }
}
