1) Установка Linux - Ubuntu

3) Редактор - CLion;
grep - мощный файловый поисковик, который поставляется на каждом дистрибутиве Linux.

Ключ -C - поиск с окружением слова(строки выше и ниже)

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/grepC.png)

Ключ -с - поиск с подсчетом количества

Ключ -w - поиск по слову целиком

Ключ -l - список файлов содержащих искомое слово

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/keys.png)

. - вывод содержимого

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/grepALLout.png)


4) Компиляция, отладка и выполнение, полезные флаги.

-c - компиляция программы и генерация машинного кода, без создания исполняемого файла

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccCnm.png)

-S - компиляция и генерация кода ассемблера 

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccS.png)

-o - задать имя исполняемого файла

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccO.png)

-E - запуск только препроцессора - он содержит код из всех подключенных библиотек

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccE.png)

-Wall - вывод всех ошибок и предупреждений

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccWall.png)

-g - отладочная информация для работы с отладчиком - файл с отладочными данными занимает больше места на диске

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccGless.png)

-O - контролирование уровня оптимизации

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccO1.png)

nm - выводится информацию о бинарных файлах

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/nm.png)


подключение библиотек 

статические .a:

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/lib.png)

создать библиотеку из объектых файлов
надо добавить к этому архиву индекс символов
надо сообщить компилятору каталог, в котором они содержатся и список билиотек. 
Каталог с библиотеками указывается ключом -L.
Используемые библиотеки перечисляются через ключ -l, после которого указывается название библиотеки без префикса lib и окончания .a. 
В нашем случае этот ключ будет выглядеть, как -lfs.


динамические .so:


![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/blob/master/image/dynlib.png)

использование специальной переменной среды LD_LIBRARY_PATH, в которой перечисляются все каталоги содержащие пользовательские динамические библиотеки
генерируемый компилятором код должен быть независимым от адресов, такая возможность включается ключом -fPIC.
Для того, чтобы создать динамическую библиотеку надо использовать ключ -shared.
использование man для поиска необходимой библиотеки

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/mansin.png)


связывание, например, math.h - с помощью ключа -lm

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/lm.png)

5) Пример отладки простой ошибочной программы

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/gccG.png)

4) Применение Makefile для автоматизации (синтаксис, использование правил и переменных)
make — утилита предназначенная для автоматизации преобразования файлов из одной формы в другую. 
Правила преобразования задаются в скрипте с именем Makefile, который должен находиться в корне рабочей директории проекта.
Сам скрипт состоит из набора правил, описывающимися целями - что правило делает, реквизитами - что необходимо и командами.


<цели>: <реквизиты>
	<команда>
	...
	<команда>
  

Инкрементная компиляция - разделение компиляции на два этапа: этап трансляции и этап линковки.
Теперь, после изменения одного из исходных файлов, достаточно произвести его трансляцию и линковку всех объектных файлов.

Правило задания переменных
<VAR_NAME> = <value string>
Для использования значения переменной ее следует разименовать при помощи конструкции $(<VAR_NAME>)

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/make.png)
