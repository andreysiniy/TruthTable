/*!
*\file
*\brief В данном файле находятся заголовки функций и поля класса Node, которые используются для работы программы.
*/

#ifndef NODE_H
#define NODE_H
#include <QString.h>

/*!
* \brief Перечисление логических операторов
*/
enum NodeType
{
    VAR,    ///< переменная
    NOT,    ///< логическое НЕ
    AND,    ///< логическое И
    OR,     ///< логическое ИЛИ
    XOR,    ///< логическое исключающее ИЛИ
    NAND,   ///< логическое не И
    NOR,    ///< логическое не ИЛИ
    EQU     ///< логическое равенство (не исключающее ИЛИ)
};

/*!
* \brief Класс узла дерева Node
* \param type - тип операции
* \param name - имя узла
* \param left - указатель на левого потомка
* \param right - указатель на правого потомка
*/
class Node
{
public:
    NodeType type;
    QString name;
    Node *left;
    Node *right;


    Node(NodeType type, QString name, Node *left = nullptr, Node *right = nullptr);

    /*!
    * \brief Оценивает логическое выражение, представленное в виде дерева
    * \param[in] root - указатель на корень дерева
    * \param[in] variables - комбинация значений переменных, для которых производится оценка
    * \return оценка выражения, ложь или истина
    */
    bool evaluate(const Node *node, const QMap<QString, bool> &variables);

    /*!
    * \brief Находит самую низкоуровневую операцию (уровня var operator var)
    * \return указатель на узел самой низкоуровневой операции в дереве
    */
    Node *lowestOperationType();

};

#endif // NODE_H
