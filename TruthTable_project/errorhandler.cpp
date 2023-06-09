/*!
*\file
*\brief Данный  файл содержит в себе реализацию функций обработки ошибок
*/
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
        case CONSOLE_ARGS_EXCEPTION:
            qDebug() << "Недостаточно аргументов в консоли";
            break;
        case INPUT_FILE_EXTENSION_EXCEPTION:
            qDebug() << "Неверное расширение входного файла, ожидался .txt файл на входе";
            break;
        case OUTPUT_FILE_EXTENSION_EXCEPTION:
            qDebug() << "Неверное расширение выходного файла, ожидался .csv файл на выходе";
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
        // Пустой токен
        error emptyTokenError = {EMPTY_TOKEN, 0, ""};
        errorList.append(emptyTokenError);
        return errorList;
    }

    if (token[0].isDigit())
    {
        // Переменная начинается с цифры
        error digitError = {VARIABLE_STARTS_WITH_DIGIT, 0, token[0]};
        errorList.append(digitError);
    }

    for (int i = 0; i < token.length(); i++)
    {
        // Символ, не соответствующий правилам языка C
        if (!token[i].isDigit() && !token[i].isLetter() && token[i] != '_')
        {
            error incorrectSymbolError = {UNKNOWN_SYMBOL, i, token[i]};
            errorList.append(incorrectSymbolError);
        }
    }

    return errorList;
}

void checkOutputPathString(QString path)
{
    QList<error> errorList;
    if (!path.endsWith(".csv"))
    {
        // Неверное расширение выходного файла
        error outputFileExtensionError;
        outputFileExtensionError.type = OUTPUT_FILE_EXTENSION_EXCEPTION;
        errorList.append(outputFileExtensionError);
        throw errorList;
    }
}
