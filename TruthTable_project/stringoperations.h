/*!
*\file
*\brief В данном файле находятся заголовки функций для работы со строкой
*/
#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#endif // STRINGOPERATIONS_H

#include "truthtable.h"

// Функция unpackString распаковывает выражение, представленное в обратной польской записи, возвращает указатель на корень выражения и список переменных

/*!
* \brief Преобразует строку, записанную в ОПЗ в разобранное дерево выражения
* \param[in] input - входная строка с ОПЗ
* \param[in,out] variables - пустой список переменных, который будет наполнен по ходу распаковки строки
* \param[in,out] nodesAmount - пустой счетчик узлов в дереве
* \return Указатель на корень разобранного дерева выражения
* \throw - QList<error> - Выбрасывает список исключений в случае ошибок обработки файла
*/
Node* unpackString(QString input, QStringList &variables, int &nodesAmount);

/*!
* \brief Преобразует заранее правильный токен в тип операции
* \param[in] input - Строка с выделенным токеном
* \return Тип операции
*/
NodeType stringToNodeType(QString input);

/*!
* \brief Получает строку по пути файла
* \param[in] fileName - путь чтения входного файла
* \return Строка, прочитанная из файла
* \throw - QList<error> - Выбрасывает список исключений в случае ошибок обработки файла
*/
QString getStringFromFile(QString path);
