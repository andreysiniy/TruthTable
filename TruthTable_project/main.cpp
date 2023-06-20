/*!
*\file
*\brief Данный файл содержит главную управляющую функцию программы
*\mainpage Документация для программы "TruthTable"
Программа предназначена для создания таблицы истинности логического выражения
Для функционирования программы необходима операционная система Windows 10 или выше.
Программа разработана на языке С++ с использованием библиотеки QT в IDE QT creator.
Стандарт языка ISO C++17 (/std:c++17).
Консольная программа должна получать два параметра командной строки: имя входного файла с данными о дереве разбора логического выражения,
имя файла для записи результирующей таблицы истинности.

Пример команды запуска программы:
*\code
app.exe C:\\Documents\input.txt .\out.csv.
*\endcode

*\author Устимов Данила
*\date Июнь 2023
*\version 1.0
*/

#include <QCoreApplication>
#include "node.h"
#include "truthtable.h"
#include "stringoperations.h"



int main(int argc, char *argv[])
{
    QCoreApplication aa(argc, argv);
    setlocale(LC_ALL, "Russian");
    if (argc > 3){
        exceptionHandler(QList<error>() << error(TO_MANY_ARGUMENTS, 0, ""));
        return 0;
    }
    QString input;
    try
    {
        input = getStringFromFile(argv[1]);
    }
    catch (QList<error> exeptions)
    {
        exceptionHandler(exeptions);
        return 0;
    }
    QStringList _variables;
    int _nodesAmount;

    Node* _root;
    try {
    _root = unpackString(input, _variables, _nodesAmount);
    }
    catch (QList<error> exceptions) {
        exceptionHandler(exceptions);
        return 0;
    }

    TruthTable outputTable;
    outputTable.nodesAmount = _nodesAmount;
    outputTable.root = _root;
    outputTable.variables = _variables;

    QList<error> errorList;
    QString fileName = argv[2];
    try {
        checkOutputPathString(fileName);
    }
    catch (QList<error> exceptions) {
        exceptionHandler(exceptions);
        return 0;
    }


    try {
    outputTable.writeTruthTableToCSV(outputTable.generateTruthTable(), fileName);
    }
    catch (QList<error> exceptions) {
        exceptionHandler(exceptions);
        return 0;
    }

    return 0;
}


