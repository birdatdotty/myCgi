# myCgi
Мой проект для предоставления вев-страниц через FastCGI.

В основе идеи:
* Файлы используемых страниц хранятся в памяти, и, в случае изменения, выврасываются из кэша для обновления при следуещем запросе
* Необходумый контент создается по средстваем QJSEngine (в тексте определяются фрагменты, которые нужно сгенерировать)
* Работает через FastCGI - php в nginx работает также, так-что пока можно считать что это аптимальный вариант

PS. Я проект только начал, так-что даже не уверен что правильно реализовал связку с FastCGI

* html - директория для тестов (скопиоровать содержимое в /home/1/)
* я использую ":9000" - прослушивание на всех сетевых устройствах на порту 9000
* nginx-test.conf - я использую nginx для тестов

PS. Сейчас используется qml файл для настройки сервера (вместо класических конфигов), думаю полностью переписать связывание объектов для более удобного конфигурирования сервиса
