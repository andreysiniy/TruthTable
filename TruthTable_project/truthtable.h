/*!
*\file
*\brief В данном файле находятся заголовки функций и поля класса TruthTable, которые используются для работы программы.
*/

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H
#include "node.h"
#include "errorhandler.h"
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>


/*!
* \brief Класс параметров таблицы истинности
* \param root - указатель на корень разобранного выражения дерева
* \param variables - список переменных
* \param nodesAmount - количество узлов дерева
*/
class TruthTable
{
public:
    Node *root;
    QStringList variables;
    int nodesAmount;


    /*!
    * \brief Генерирует список комбинаций возможных значений переменных
    * \return Заполненный список комбинаций возможных значений переменных
    */
    QList<QMap<QString, bool>> generateCombinations();

    /*!
    * \brief Генерирует таблицу истинности выражения в виде списка комбинаций разных значений
    * \return Заполненный список с вычисленными значениями таблицы истинности
    */
    QList<QMap<QString, bool>> generateTruthTable();

    /*!
    * \brief Записывает таблицу истинности в файл таблицы формата .csv
    * \param[in] truthTable - вычисленная таблица истинности, представленная в виде списка комбинаций разных значений
    * \param[in] fileName - путь записи выходного файла
    */
    void writeTruthTableToCSV(const QList<QMap<QString, bool>>& truthTable, const QString& fileName);

    TruthTable();
};

#endif // TRUTHTABLE_H
