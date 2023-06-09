/*!
*\file
*\brief Данный  файл содержит в себе реализацию функций для работы со строкой
*/
#include "stringoperations.h"

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

    if (!path.endsWith(".txt"))
    {
        // Неверное расширение файла
        error fileExtensionError;
        fileExtensionError.type = INPUT_FILE_EXTENSION_EXCEPTION;
        errorList.append(fileExtensionError);
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
