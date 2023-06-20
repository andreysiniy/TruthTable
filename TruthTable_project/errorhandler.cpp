#include "errorhandler.h"

void exceptionHandler(QList<error> errors)
{
    for (error exeption : errors)
    {
        switch (exeption.type)
        {
        case PATH_NOT_FOUND:
            qDebug() << "Путь к файлу пустой";
            break;
        case FILE_NOT_FOUND:
            qDebug() << "Файл по пути не найден";
            break;
        case FILE_ACCESS_DENIED:
            qDebug() << "Нет доступа к пути файла с входными данными";
            break;
        case MORE_THAN_ONE_STRING:
            qDebug() << "В файле содержится больше одной строки";
            break;
        case UNKNOWN_SYMBOL:
            qDebug() << "Неизвестный символ в названии переменной " << exeption.data << " на позиции " << exeption.position;
            break;
        case NOT_ENOUGH_OPERATORS:
            qDebug() << "Недостаточно операторов в выражении";
            break;
        case NOT_ENOUGH_ARGUMENTS:
            qDebug() << "Недостаточно аргументов у " << exeption.data << " на позиции " << exeption.position;
            break;
        case TO_MANY_SPACES:
            qDebug() << "Неожиданный пробел на позиции " << exeption.position << " Ожидался операнд ";
            break;
        case EMPTY_TREE:
            qDebug() << "Пустое дерево";
            break;
        case NO_ACCESS_TO_FILE:
            qDebug() << "Нет доступа к пути выходного файла";
            break;
        case VARIABLE_STARTS_WITH_DIGIT:
            qDebug() << "Переменная начинается с цифры " << exeption.data << " на позиции " << exeption.position;
            break;
        case EMPTY_TOKEN:
            qDebug() << "Пустой токен";
            break;
        case TO_MANY_ARGUMENTS:
            qDebug() << "Передано слишком много аргументов";
            break;
        default:
            break;
        }
    }
}

tokenType tokenClassification(QString token)
{
    if (token == "")
    {
        return EMPTY;
    }
    if (operatorsMap.contains(token))
    {
        return OPERATOR;
    }
    if (variableValidation(token).isEmpty())
    {
        return VARIABLE;
    }
    else
    {
        return UNKNOWN_TOKEN;
    }
}

QList<error> variableValidation(QString token)
{
    QList<error> errorList;
    if (token == "")
    {
        error emptyTokenError = {EMPTY_TOKEN, 0, ""};
        errorList.append(emptyTokenError);
        return errorList;
    }

    if (token[0].isDigit())
    {
        error digitError = {VARIABLE_STARTS_WITH_DIGIT, 0, token[0]};
        errorList.append(digitError);
    }

    for (int i = 0; i < token.length(); i++)
    {
        if (!token[i].isDigit() && !token[i].isLetter())
        {
            error incorrectSymbolError = {UNKNOWN_SYMBOL, i, token[i]};
            errorList.append(incorrectSymbolError);
        }
    }

    return errorList;
}

/*void checkString(QString string)
{
    if (string.trimmed().isEmpty())
        {
            QList<error> emptyTree;
            emptyTree.append({EMPTY_TREE, 0, ""});
            throw emptyTree;
        }
    QList<error> errorList;
    const QStringList tokens = string.split(' ');

    QList<QString>::const_iterator tokenIterator = tokens.begin();
    int currentTokenPosition = 0;

    for (QString currentToken : tokens)
       {
           switch (tokenClassification(currentToken))
           {
           case EMPTY:
           {
               // Текущая лексема - пустая
               errorList.append({TO_MANY_SPACES, currentTokenPosition, currentToken}); // Лишний разделитель (пробел)
               break;
           }

           case OPERATOR:
           {
               // Текущая лексема - оператор
               node *operatorNode = new node();
               operatorNode->type = operatorsMap[currentLexeme].type;
               operatorNode->data = currentLexeme;

               if (stack.size() < operatorsMap[currentLexeme].amountOfOperands)
               {
                   // Не хватает операндов в стеке для того чтобы заполнить оператор
                   errorList.append({NOT_ENOUGH_ARGUMENTS, currentLexemePosition, currentLexeme});
               }
               else
               {
                   // Добавить детей в новый узел
                   for (int i = 0; i < operatorsMap[currentLexeme].amountOfOperands; i++)
                   {
                       operatorNode->childrens.append(stack.takeLast().element);
                   }
               }

               // Добавить новый узел в стек
               stack.append({operatorNode, currentLexemePosition});
               break;
           }

           case VARIABLE:
           {
               // Текущая лексема - переменная
               node *variableNode = new node();
               variableNode->type = VARIABLE;
               variableNode->data = currentLexeme;

               // Добавить новый узел в стек
               stack.append({variableNode, currentLexemePosition});
               break;
           }

           case UNKNOWN_TOKEN:
           {
               // Ошибки в написании переменной
               // Добавить ошибки в общий список
               for (error exeption : variableValidation(currentLexeme))
               {
                   exeption.position += currentLexemePosition; // Добавить позицию лексемы в строке
                   errorList.append(exeption);
               }
               break;
           }
           }

           // Позиция считается как сумма длин всех предыдущих лексем + кол-во разделителей
           currentLexemePosition += currentLexeme.length() + 1;
       }
} */
