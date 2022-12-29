# Утилита WordCount

Утилита WordCount - подсчитывает количество строк, слов и байт для указанного файла и выводит эту информацию в поток вывода.

Программа поддерживает следующие опции:

**-l, --lines** вывод только количества строк

**-c, --bytes** вывод размера файла в байтах

**-w, --words** вывод количества слов

**-m, –chars** вывод количества букв*

Название файла и опции передаются через аргументы командной строки в следующем формате:

_**WordCont.exe [OPTION] filename [filename,.....]**_

Формат вывода (без заданных опций):
  lines words bytes filename
