#Задание
Разработать консольное серверное приложение работающее в среде ОС LINUX на пользовательском уровне. Приложение должно генерировать последовательность целых чисел, состоящую из 3-х подпоследовательностей, каждая из которых представляет собой целочисленный неотрицательный 64-х битный счетчик. Для каждой такой подпоследовательности начальное значение и шаг между двумя соседними значениями задается пользователем произвольно. 
Формат задания параметров – простой текст в tcp/ip сокет (для проверки используется telnet-клиент).

#Перечень команд
1. seq1 xxxx yyyy (задать начальное значение = xxxx и шаг = yyyy для первой подпоследовательности);
2. seq2 xxxx yyyy (задать начальное значение = xxxx и шаг = yyyy для второй подпоследовательности);
3. seq3 xxxx yyyy (задать начальное значение = xxxx и шаг = yyyy для третьей подпоследовательности);
4. export seq - выдавать в сокет каждому клиенту сгенерированную последовательность. 

#Примеры входных и выходных данных
1. seq1 1 2 – задает подпоследовательность 1, 3, 5 и т.д;
2. seq2 2 3 – задает подпоследовательность 2, 5, 8 и т.д;
3. seq3 3 4 – задает подпоследовательность 3, 7, 11 и т.д;
4. export seq – в сокет передается последовательность 1, 2, 3, 3, 5, 7, 5, 8, 11 и т.д. 

#Установка и запуск:
1. make
2. ./run_server
3. telnet localhost 3425
4. *enter the command*
