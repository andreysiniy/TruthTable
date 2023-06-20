/*!
*\file
*\brief В данном файле находятся заголовки функций и структуры данных, которые используются для проверки исключений.
*/

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#endif // ERRORHANDLER_H

#include <QString>
#include <QList>
#include <QDebug>
#include "node.h"

/*!
* \brief Перечисление исключений
*/
enum exeption {
    NULL_EXEPTION, ///< нет ошибки
    PATH_NOT_FOUND, ///< путь к файлу пустой
    FILE_NOT_FOUND, ///< файл по пути не найден
    FILE_ACCESS_DENIED, ///< нет доступа к файлу
    MORE_THAN_ONE_STRING, ///< в файле содержится слишком много строк
    UNKNOWN_SYMBOL, ///< неизвестный символ в названии переменной
    NOT_ENOUGH_OPERATORS, ///< недостаточно оператором
    NOT_ENOUGH_ARGUMENTS, ///< недостаточно аргументов
    TO_MANY_SPACES, ///< слишком много пробелов
    EMPTY_TREE, ///< пустое древо
    NO_ACCESS_TO_FILE, ///< нет доступа к файлу
    VARIABLE_STARTS_WITH_DIGIT, ///< переменная начинается с цифры
    EMPTY_TOKEN, ///< пустой токен
    TO_MANY_ARGUMENTS ///< передано слишком много аргументов
};

/*!
* \brief Перечисление типов токенов
*/
enum tokenType
{
    EMPTY, ///< пустая лексема
    OPERATOR,   ///< оператор
    VARIABLE,    ///< переменная
    UNKNOWN_TOKEN ///< неизвестный токен
};

/*!
* \brief Структура ошибки
*/
struct error {
    exeption type;
    int position;
    QString data;


    // Конструктор по умолчанию
    error(){
        this->type = NULL_EXEPTION;
        this->position = 0;
        this->data = "";
    }

    // Конструктор с параметрами
    error(exeption error, int position, QString data){
        this->type = error;
        this->position = position;
        this->data = data;
    }

    // Перегрузка оператора сравнения
    bool operator==(const error &other) const
    {
        return (type == other.type && position == other.position && data == other.data);
    }
};

/*!
 * \brief  Структура операторов для обработки ошибки
 */
struct operators
{
    NodeType type; ///< тип оператора
    int amountOfOperands; ///< количество операндов
};

/*!
 * \brief  Интерпретация поддерживаемых операторов из строки
 */
const QMap<QString, operators> operatorsMap = {
    {"AND", {AND, 2}},
    {"OR", {OR, 2}},
    {"NOT", {NOT, 1}},
    {"XOR", {XOR, 2}},
    {"NAND", {NAND, 2}},
    {"NOR", {NOR, 2}},
    {"EQU", {EQU, 2}}
};


/*!
* \brief Обрабатывает исключения и выводит их в консоль
* \param[in] errors - список ошибок
*/
void exceptionHandler(QList<error> errors);

/*!
* \brief Проверяет соответствует ли лексема правилам написания переменной
* \param[in] token - токен
* \return QList<error> - список ошибок написания переменной (если ошибок нет, то лексема соответствует правилу написания переменной)
*/
QList<error> variableValidation(QString token);

/*!
* \brief Классифицирует токен
* \param[in] token - токен
* \return тип токена из перечисления tokenType
*/
tokenType tokenClassification(QString token);


