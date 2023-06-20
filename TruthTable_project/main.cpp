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

Node* unpackString(QString input, QStringList &variables, int &nodesAmount)
{
    // Вывести исключение, если строка пустая
    if (input.trimmed().isEmpty())
    {
            QList<error> emptyTree;
            emptyTree.append({EMPTY_TREE, 0, ""});
            throw emptyTree;
    }
    QList<error> errorList; // Список исключений
    nodesAmount = 0; // Счетчик кол-ва узлов
    // Инициализация пустого списка узлов
    QList<Node*> nodeList;
    // Разбиваем строку на токены
    QStringList tokens = input.split(" ", Qt::SkipEmptyParts);
    // Текущая позиция начала токена
    int currentTokenPosition = 0;
    // Для каждого токена
    foreach (QString token, tokens) {
        // Создаем пустой узел
        Node* newNode = new Node(VAR, token, NULL, NULL);
        nodesAmount++;

        // Обработка токена
        switch (tokenClassification(token))
        {
        case EMPTY: // Пустой токен
        {
            errorList.append({TO_MANY_SPACES, currentTokenPosition, token}); // Лишний разделитель (пробел)
            break;
        }
        case OPERATOR: // Токен является оператором
        {
            if (token == "NOT") {
                // Считать тип операции текущего узла операцией NOT
                newNode->type = NOT;
                // Если в списке нет аргументов операнда, то выдать исключение
                if (nodeList.empty())
                    errorList.append({NOT_ENOUGH_ARGUMENTS, currentTokenPosition, token});
                else // Иначе - продолжить обработку
                {
                // Считать "правым" потомком последний записанный в список узел, извлечь его из списка узлов
                newNode->right = nodeList.takeLast();
                // Формирование имени узла
                // Если правый потомок - переменная, то скобки в названии не нужны
                if (newNode->right->type == VAR)
                // Формирование имени по принципу "тип операции" + пробел + "имя правого потомка"
                newNode->name = token + " " + newNode->right->name;
                // Иначе - добавить скобки к названию
                else
                    // Формирование имени по принципу "тип операции" + пробел + "(имя правого потомка)"
                    newNode->name = token + " (" + newNode->right->name + ")";
                }
                }
            else { // Если токен - другой тип операции
                // Присвоить тип операции текущего узла по токену
                newNode->type = stringToNodeType(token);
                // Если в списке меньше двух узлов, то выдать исключение
                if (nodeList.length() < 2)
                    errorList.append({NOT_ENOUGH_ARGUMENTS, currentTokenPosition, token});
                else {
                // Извлечь из списка "правого" потомка - последний записанный в список узел
                newNode->right = nodeList.takeLast();
                // Извлечь из списка "левого" потомка - следующий в списке узел
                newNode->left = nodeList.takeLast();
                // Формирование имени узла по принципу "имя левого потомка" + пробел + "тип операции" + пробел + "имя правого потомка" (добавляем скобки к имени потомков при необходимости)
                // Инициализировать пустую строку
                newNode->name = "";
                // Если левый потомок - переменная, то скобки в названии не нужны
                if (newNode->left->type == VAR)
                newNode->name += newNode->left->name;
                else //  Если левый потомок - любая другая операция, то добавить скобки к его названию
                    newNode->name += ("(" + newNode->left->name + ")");
                    // Добавить тип операции с пробелами к названию
                newNode->name += (" " + token + " ");
                // Если правый потомок - переменная, то скобки в названии не нужны
                if (newNode->right->type == VAR)
                    newNode->name += newNode->right->name;
                else //  Если правый потомок - любая другая операция, то добавить скобки к его названию
                    newNode->name += ("(" + newNode->right->name + ")");
                }
            }
            break;
        }
        case VARIABLE:
        {
            // Считать тип операции текущего узла переменной
            newNode->type = VAR;

            // Добавить название переменной в список переменных
            variables.append(newNode->name);
            break;
        }
        case UNKNOWN_TOKEN:
        {
            // Ошибки в написании переменной
            // Добавить ошибки в общий список
            for (error exeption : variableValidation(token))
            {
                exeption.position += currentTokenPosition; // Добавить позицию лексемы в строке
                errorList.append(exeption);
            }
            break;
        }

        }
        nodeList.append(newNode); // Добавить узел в список
        currentTokenPosition += token.length() + 1; // Увеличение позиции текущего токена

    }
    if (nodeList.size() == 0)
    {
        // Пустое дерево
        errorList.append({EMPTY_TREE, 0, ""});
    }

    if (nodeList.size() > 1)
    {
        // После обработки выражения в стеке остались необработанные операторы (древо не сходится к единому корню)
        errorList.append({NOT_ENOUGH_OPERATORS, 0, ""});
    }

    if (errorList.size() > 0)
    {
        throw errorList;
    }
    // Вернуть единственный оставшийся узел в списке, являющимся корнем
    return nodeList.last();
}

NodeType stringToNodeType(QString input)
{
    if (input == "NOT")
        return NodeType::NOT;
    else if (input == "AND")
        return NodeType::AND;
    else if (input == "OR")
        return NodeType::OR;
    else if (input == "XOR")
        return NodeType::XOR;
    else if (input == "NAND")
        return NodeType::NAND;
    else if (input == "NOR")
        return NodeType::NOR;
    else if (input == "EQU")
        return NodeType::EQU;
    else return NodeType::VAR;
}

QString getStringFromFile(QString path)

{
    QList<error> errorList;

    if (path.isEmpty())
    {
        // Путь к файлу пустой
        error pathError;
        pathError.type = PATH_NOT_FOUND;
        errorList.append(pathError);
        throw errorList;
    }

    QFile file(path);
    if (!file.exists())
    {
        // Файл по пути не найден
        error fileError;
        fileError.type = FILE_NOT_FOUND;
        errorList.append(fileError);
        throw errorList;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Нет доступа к файлу
        error fileError;
        fileError.type = FILE_ACCESS_DENIED;
        errorList.append(fileError);
        throw errorList;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    if (!line.isNull() && !in.atEnd())
    {
        // В файле содержится больше одной строки
        error multipleStringsError;
        multipleStringsError.type = MORE_THAN_ONE_STRING;
        errorList.append(multipleStringsError);
        throw errorList;
    }

    return line;
}
