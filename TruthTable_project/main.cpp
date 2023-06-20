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



    QString input = getStringFromFile("input\\truth_table.txt");
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

    QString fileName = "truth_table.csv";
    try {
    outputTable.writeTruthTableToCSV(outputTable.generateTruthTable(), fileName);
    }
    catch (QList<error> exceptions) {
        exceptionHandler(exceptions);
    }

    return 0;
}


