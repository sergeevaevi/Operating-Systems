Разработать план  (что, зачем и как тестируется)  для трех вариантов кода и прокомментировать результаты тестирования для
queue. c  - наивный вариант

проблемы:

- доступ к очереди не является пригодным для многопотокового
выполнения. Разные потоки могут вызывать next_in и
next_out одновременно

- если первый в очереди потребитель обнаруживает пустую очередь,
он печатает сообщение об ошибке и завершает процесс, хотя должен ждать
(перейти в состояние Blocked), когда очередь пополнится. 


![Иллюстрация](https://github.com/sergeevaevi/Operating-Systems/raw/master/image/exmpl1.png)


например один поток хочет извлечь 10 запись, когда первый добавил только 8.

queue_mutex. c  - с использованием mutex

проблемы:

- если первый в очереди потребитель обнаруживает пустую очередь,
он печатает сообщение об ошибке и завершает процесс, хотя должен ждать
(перейти в состояние Blocked), когда очередь пополнится. Также и с
полной очередью.

Была решена проблема с доступом к очереди в многопоточном режиме.

queue_cond. c  - с использованием условных переменных для ситуаций с пустой и полной очередями

условная переменная – это структура данных, связанная с
условием для блокировки потока до момента, когда условие не
станет выполненным в связи с изменениями, вносимых другими
потоками

cond_wait ждет сигнала, но могут возникнуть ложные пробуждения, которые ничего не подразумевают в значении этого предиката, предикат должен быть переоценен после такого возврата. 
Поэтому его нужно помещать в цикл с проверкой условия пробуждения.

Данная программа решает поднятые проблемы.
