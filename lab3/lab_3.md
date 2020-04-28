Использование виртуальной памяти

0. Ознакомиться со структурой виртуальной памяти и инструментами для работы с ней.

Виртуальная память — метод управления памятью компьютера, позволяющий выполнять программы, требующие больше оперативной памяти, чем имеется в компьютере, путём автоматического перемещения частей программы между основной памятью и вторичным хранилищем. Размер виртуальной памяти теоретически ограничивается разрядностью операционной системы. Название "виртуальная" произошло из-за того что процессу неизвестно реальное (физическое) расположение памяти.перационная система предоставляет процессу виртуальное адресное пространство (ВАП, virtual address space) определенного размера и процесс может работать с ячейками памяти по любым виртуальным адресам этого пространства, не "задумываясь" о том, где реально хранятся данные.
Самые частые функции выделения памяти – это malloc и free. На самом деле, Linux не выделяет всю запрошенную память сразу. Никакой физической аллокации не происходит. А произойдет она только в том случае, если мы попробуем в эту страницу произвести запись.
Отображение страниц выполняется с помощью mmap/munmap. Ещё существуют brk/sbrk, которые изменяют размер одного-единственного интервала «данных».

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/stracture_of_process_mem.png)


malloc обеспечивает динамическое выделение памяти в "куче" в процессе работы. По существу, чтобы управлять размером адресного пространства процесса, она использует низкоуровневые системные вызовы sbrk() / brk(). sbrk() добавляет память в конец адресного пространства процесса, увеличивая тем самым размер. brk(), с другой стороны, можно задать произвольный размер в пространстве процесса. Они эффективно используются библиотечными вызовами malloc / free для выделения/освобождения памяти для приложений, соответственно. Пространство процесса в стандартном Linux является виртуальным адресным пространством и, следовательно, добавление большей памяти выполняется простой настройкой структур виртуальной памяти в ядре, которое обеспечивает необходимую связь с физическими адресами. Так что malloc просто увеличивает размер виртуальной памяти, а free уменьшает размер виртуальной памяти по мере необходимости.

1. Разработать программу memory-user.c, которая принимает на вход количество Mb памяти, которую она резервирует и в которой она размещает массив,  а затем перебирает все его элементы в бесконечном цикле или заданное количество времени, которое также вводитс по запросу.

  memory/main.c
  
2. Пока программа memory-user.c выполнется при различных объемах запрошенной памяти (включая значительные), из другого терминала выполнить запрос free(). Проанализировать результаты распределени памяти до и после завершения memory-user.c с помощью kill.

Первая версия программы выделяла память и просто выводила содержимое массива на экран, не меняя содержимое. В таком случае, -free не показывал значительного изменения количества занятой памяти. Команда free позволяет вызывать одноименную утилиту, осуществляющую вывод информации об использовании оперативной памяти.
Колонки:
* total – общий размер ОЗУ
* used – реально использующая в данный момент и зарезервированная системой память 
* free – свободная память (total - used)
* shared – разделяемая память
* buffers – буферы в памяти – страницы памяти, зарезервированные системой для выделения их процессам, когда им это  потребуется
* cached – файлы, которые недавно были использованы системой/процессами и хранящиеся в памяти на случай, если они снова потребуются.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/free_and_kill_.png)

Но если в цикле менялось содержимое массива, допустим все обнулялось, то количество занятой памяти увеличивалось.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/another_free.png)

После завершения процесса при помощи -kill память возвращается к исходному состоянию.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/another_kill.png)

3. Исследовать распределение памяти для memory-user.c с использованием pmap при различных объемах запрошенной памяти (включая значительные).

Команда -pmap детально расписывает использование оперативной памяти процессами в системе.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/empty_pmap_.png)

До того как в программе была выделена память, оперативная память ей практически не занимется.
При запуске программы создается процесс, при этом в память загружаются код и данные программы, а также необходимые программе динамически подключаемые библиотеки. Формируется куча – область, в которой процесс может выделять память динамическим структурам данных. Кроме того, каждому потоку предоставляется стек для хранения локальных переменных и параметров функций.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/busy_pmap_.png)

После того, как была выделена память, количество использованной памяти увеличивается на соответственное количество Мб.