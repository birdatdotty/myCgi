# myCgi
Мой проект для предоставления вев-страниц через FastCGI.

В основе идеи:
* Файлы используемых страниц хранятся в памяти, и, в случае изменения, выврасываются из кэша для обновления при следуещем запросе
* Необходумый контент создается по средстваем QJSEngine (в тексте определяются фрагменты, которые нужно сгенерировать)
* Работает через FastCGI - php в nginx работает также, так-что пока можно считать что это аптимальный вариант

PS. Я проект только начал, так-что даже сомниваюсь что правильно реализовал связку с FastCGI
