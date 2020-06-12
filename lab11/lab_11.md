1)  vector-deadlock.c,  main-common.c и др.:
-Выполнить  ./vector-deadlock -n 2 -l 1 -v
которая инициирует 2 потока  (-n 2) и каждый из них осуществляет одно  сложение (-1 1) с опцией (-v).
Объяснить результат. Меняется ли он от вызова к вызову? 
- Добавить флаг  -d и изменить количество циклов  -l .
Всегда ли возникает состояние взаимной блокировки потоков (deadlock)?
- Теперь меняем число потоков -n. Есть ли такое число потоков, при котором блокировка не возникает?

          -d          
             Этот флаг включает возможность блокировки потоков.
             Когда вы передаете -d программе, каждый другой поток вызывает vector_add () 
             с векторами в другом порядке, например, с двумя потоками, и -d включен, 
             Поток 0 вызывает vector_add (v1, v2), а поток 1 вызывает vector_add (v2, v1)
          -p
             Этот флаг дает каждому потоку различный набор векторов для вызова add () 
             Используй, чтобы увидеть, как все работает 
             когда нет конкуренции за один и тот же набор векторов. 
          -n num_threads
             Создает некоторое количество потоков; вам нужно больше, чем один, чтобы зайти в deadlock.
          -l loops
             Сколько раз каждый поток должен вызывать vector_add ()?
          -v 
             Подробный флаг: распечатывает немного больше о том, что происходит.
          -t
             Включает тайминг и показывает, как долго все прошло.
             
 - Эта программа захватывает lock в определенном порядке. Она создает условия для deadlock, так
как один поток может вызвать vector_add (v1, v2), в то время как другой вызовет одновременно vector_add (v2, v1).
Вывод меняется, так потоки не всегла перехватывают выполнение в одно и то же время.
Но так как в программе порядок установлен верно, то deadlock не происходит.
 - При выставлении флага -d блокировка случается, но редко и при очень больших значениях -l.
 - При смене числа потоков так же можно добиться deadlock. Но при -n 1 это сделать невозможно)

2.  vector-global-order.c:
- За счет чего программа избегает блокировок? 
- Для чего предусмотрен специальный случай в vector add(), когда исходный и результирующий вектор совпадают?
- Флаги: -t -n 2 -l 100000 -d. Как меняется время в зависимости от числа циклов и числа потоков?
- Что происходит, когда включается ключ -p (при сложении различных векторов и одного и того же)?

 - Эта программа упорядочивает блокировку, независимо от того что ей передается. 
 Эта версия vector_add () захватывает lock в общем порядке на основе адрес вектора.

 - Существует особый случай, когда src и dst совпадают, потому что в этом случае необходимо получить только одну блокировку.
 Без этого особого случая будет гарантирован deadlock.
 
  ![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/time.png)
  
 - Зависимость от loops понятна - чем больше loops, тем больше времени на выполнение потребуется
  Зависимость от количества потоков не так очевидна, казалось бы. Чем больше потоков, тем больше времени затратится.
 
  - Скорость выполнения увеличивается, так как теперь потокам не нужно ждать тех же двух блокировок. 
  Номеров векторов стало больше, поэтому локи ставятся реже.
  
![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/time_p.png)
  
3. vector-try-wait.c: 
- Нужен ли первый вызов  pthread mutex trylock()?
- Как меняется число повторных попыток, когда растет число потоков?

Эта версия vector_add () использует pthread_mutex_trylock (), 
чтобы попытаться захватить lock; 
когда попытка не удалась, код освобождает любые блокировки, которые он может удерживать
возвращается наверх и пробует все заново.

  - Первый вызов нужен, чтобы заблокировать вектор в первый раз, так как trylock блокирует в случае удачи.
  - Чем больше потоков, тем больше попыток.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/try_lock.png)

4.  vector-avoid-hold-and-wait.c: 
- Сравнить с другими подходами.
- Как меняется производительность в зависимости от наличия флага -p?

 - Основная проблема этого подхода заключается в том, что он слишком грубый: 
 глобальная блокировка будет ставить lock, даже если векторы каждого потока различны.
 Этот способ работает лучше предыдущего, но хуже чем глобальная очередность.

![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/compare.png)

 - C -p флагом все работает значительно быстрее.
Время выполнения (без флага -p) очень близко к таковому для vector-global-order. Но с флогом эта программа заметнее медленнее.


![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/compare2.png)

5.  vector-nolock.c:

- Сравнить семантику и производительность с другими вариантами при работе с двумя одинаковыми векторами и в случае,
когда каждый поток работает на своем векторе  -p.


![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/compare3.png)

 - Эта версия vector_add () даже не использует блокировки; 
Она использует atomic fetch-and-add для реализации подпрограммы vector_add (). 
Ее семантика немного отличается от предыдущих.
Этот вариант атомарнен в отношении добавления пары записей.