// Классификация паттернов по цели (Уровень 1):
/*

порождающие паттерны - связаныпроцессом создания объектов

структурные паттерны и паттерны поведения - композиция объектов и классов

*/

// Паттерны поведения характеризуют то, как классы или объекты
// взаимодействуют между собой.

/*
    Второй критерий уровень говорит о том, к чему обычно применяется пат
    терн: к объектам или классам. Паттерны уровня классов описывают отношения
    между классами и их подклассами. Такие отношения выражаются с помощью на
    следования, поэтому они статичны, то есть зафиксированы на этапе компиляции.
    Паттерны уровня объектов описывают отношения между объектами,
    которые могут изменяться во время выполнения и потому более динамичны. 
*/


/*
|  Уровень/ Цель   |  Порождающие паттерны  |    Структурные паттерны    |         Паттерны поведения           |
|------------------|------------------------|----------------------------|--------------------------------------|
| Класс            |    Фабричный метод     |     Адаптер (класса)       |      Интерпретатор                   |
|                  |                        |                            |      Шаблонный метод                 |
|------------------|------------------------|----------------------------|--------------------------------------|
| Объект           | Абстрактная фабрика    |    Адаптер (объекта)       |          Итератор                    |
|                  |      Одиночка          |         Декоратор          |          Команда                     |
|                  |      Прототип          |        Заместитель         |         Наблюдатель                  |
|                  |      Строитель         |        Компоновщик         |          Посетитель                  |
|                  |                        |           Мост             |          Посредник                   |
|                  |                        |      Приспособленец        |          Состояние                   |
|                  |                        |           Фасад            |          Стратегия                   |
|                  |                        |                            |          Хранитель                   |
|                  |                        |                            |    Цепочка обязанностей              |
*/

/*
    1. Порождающие паттерны:
            классов частично делегируют ответственность за создание объектов своим подклассам.
            
            объектов передают ответственность другому объекту. 
        

    2. Структурные паттерны 
            классов используют наследование для составления классов.

            объектов описывают способы сборки объектов из частей. 
        

    3. Поведенческие паттерны 
            классов используют наследование для описания алгоритмов и потока управления. 

            объектов описывают, как объекты, принад лежащие некоторой группе, совместно функционируют и 
            выполняют задачу, ко торая ни одному отдельному объекту не под силу.

*/

// #########################################
// Объект содержит методы.
// Единственный способ заставить объект выполнить операцию - вызвать метод.
// Выполнить операцию - единственный способ изменить состояние объекта.
// --> Внутр. состояние инкапсулировано 
// #########################################



//------------------------------
//TODO: Как решать задачи проектирования с помощью паттернов

// 1. Поиск подходящих объектов

// 2. Определение степени детализации объекта
/*
    Размеры и число объектов могут сильно варьироваться. С их помощью может
    быть представлено все, начиная с уровня аппаратуры и до законченных приложе
    ний. <-> Помогут паттерны.
*/

// 3. Специфицирование интерфейсов объекта
/*
    При объявлении объектом любой операции должны быть заданы: имя опера
    ции, объекты, передаваемые в качестве параметров, и значение, возвращаемое опе
    рацией. Эту триаду называют сигнатурой операции. Множество сигнатур всех
    определенных для объекта операций называется интерфейсом этого объекта
*/
/*
    Тип – это имя, используемое для обозначения конкретного интерфейса. Гово
    рят, что объект имеет тип Window, если он готов принимать запросы на выполне
    ние любых операций, определенных в интерфейсе с именем Window. 
*/

// 4. Специфицирование реализации объектов
/*
    До сих пор мы почти ничего не сказали о том, как же в действительности опре
    деляется объект. Реализация объекта определяется его классом. Класс специфи
    цирует внутренние данные объекта и его представление, а также операции, кото
    рые объект может выполнять
 */

// Наследование класса и наследование интерфейса
/*
    Наследование классов– это не что иное, как механизм расширения функцио
    нальности приложения путем повторного использования функциональности ро
    дительских классов
*/
// Правило 1. Программировать на уровне интерфейсов, а не реализации.

// 5. Механизмы повторного использования
// Наследование, композиция, делигирование, параметризованные типы. 

// Правило 2. Предпочитать композицию наследованию.



//------------------------------
// TODO:  Проектирование с учетом будущих изменений.

// 1. Задавать объекты косвенно - абстрактная фабрика, фабричный метод, прототи.

// 2. Не использовать зависимость от конкретных операций - цепочка обязанностей, команда.

// 3. Не использовать зависимость от аппаратной и программнойс платформ - абстрактная фабрика, мост.

// 4. Скрывать представление и реализацию объекта - абстрактная фабрика, мост, хранитель, заместитель.

// 5. Изолировать алгоритмы, которые будут в последующем изменяться - мотс, итератор, стратегия, шаблонный мтеод, посетитель.

// 6. Избегать сильной связанности - абстрактная фабрик, мост, цепочка об., команда, фасад, посредник, наблюдатель.

// 7. Стараться не использовать расширение функциональности за счет наследования - мост, цепочка, комп., декор., набл., стратегия.

// 8. Использовать паттерны для изменения классов - адаптер, декоратор, посетитель.


// TODO: Проектирование прикладных программ - внутреннее повторное использование, удобство сопровождения и расишряемости.
/*
    1. вы не проектируете и не реализуете больше, чем необходимо; - паттерны уменьш. число зависимостей.
*/


// Инструментальная библиотека – это набор взаимосвязанных, повторно используемых классов, 
// спроектированный с целью предоставления полезных функций
//  общего назначения. 

// Каркас – это набор взаимодействующих классов, составляющих 
// повторно используемый дизайн для конкретного класса программ.

/*

    ❑ подумайте, как паттерны решают проблемы проектирования. 
    
    В разделе 1.6 обсуждается то, как с помощью паттернов можно найти подходящие объек
    ты, определить нужную степень их детализации, специфицировать их ин
    терфейсы. Здесь же говорится и о некоторых иных подходах к решению за
    дач с помощью паттернов;


    
    ❑ пролистайте разделы каталога, описывающие назначение паттернов. 
    
    В разделе 1.4 перечислены назначения всех представленных паттернов. Ознакомь
    тесь с целью каждого паттерна, когда будете искать тот, что в наибольшей сте
    пени относится к вашей проблеме. Чтобы сузить поиск, воспользуйтесь
    схемой в таблице 1.1;

    
    
    ❑ изучите взаимосвязи паттернов. 
    
    На рис. 1.1 графически изображены соот
    ношения между различными паттернами проектирования. Данная инфор
    мация поможет вам найти нужный паттерн или группы паттернов;



    ❑ проанализируйте паттерны со сходными целями. 

    Каталог состоит из трех частей: порождающие паттерны, 
    структурные паттерны и паттерны поведе
    ния. Каждая часть начинается со вступительных замечаний о паттернах со
    ответствующего вида и заканчивается разделом, где они сравниваются друг
    с другом;

    
    
    ❑ разберитесь в причинах, вызывающих перепроектирование. 
    
    Взгляните на пе речень причин, приведенный выше. Быть может, в нем упомянута ваша про
    блема? Затем обратитесь к изучению паттернов, помогающих устранить эту
    причину;



    ❑ посмотрите, что в вашем дизайне должно быть изменяющимся. 
    
    Такой подход противоположен исследованию причин, вызвавших необходимость перепро
    ектирования. Вместо этого подумайте, что могло бы заставить изменить ди
    зайн, а также о том, что бы вы хотели изменять без перепроектирования.
    Акцент здесь делается на инкапсуляции сущностей, подверженных измене
    ниям, а это предмет многих паттернов. В таблице 1.2 перечислены те аспек
    ты дизайна, которые разные паттерны позволяют варьировать независимо,
    устраняя тем самым необходимость в перепроектировании.

*/