#include "node.h"
#include <QMap>
#include <QString>

Node::Node(NodeType type, QString name, Node *left, Node *right)
{
    this->type = type;
    this->name = name;
    this->left = left;
    this->right = right;
};

/*
Эта функция оценивает логическое выражение, представленное в виде дерева. Каждый узел дерева представляет либо переменную (VAR),
либо логический оператор (NOT, AND, OR, XOR, NAND, NOR, EQU). Функция принимает указатель на корень дерева и QMap,
содержащий значения переменных, используемых в выражении.
*/
bool Node::evaluate(const Node *node, const QMap<QString, bool> &variables)
{
    // Создание локальной копии QMap, которая копирует значения из QMap, переданного в качестве аргумента функции.
    QMap<QString, bool> variablesCopy = variables;
    // Проверка типа узла, после которой идет рекурсивный обход дерева, пока не будет вычислено значение.
    switch (node->type)
    {
        case VAR:
            return variablesCopy[node->name];
        case NOT:
            return !evaluate(node->right, variablesCopy);
        case AND:
            return evaluate(node->left, variablesCopy) && evaluate(node->right, variablesCopy);
        case OR:
            return evaluate(node->left, variablesCopy) || evaluate(node->right, variablesCopy);
        case XOR:
            return evaluate(node->left, variablesCopy) != evaluate(node->right, variablesCopy);
        case NAND:
            return !(evaluate(node->left, variablesCopy) && evaluate(node->right, variablesCopy));
        case NOR:
            return !(evaluate(node->left, variablesCopy) || evaluate(node->right, variablesCopy));
        case EQU:
            return evaluate(node->left, variablesCopy) == evaluate(node->right, variablesCopy);
        default:
            return false;
    }
}

Node *Node::lowestOperationType()
{
    Node *result = this;

    if (this->left != NULL && this->left->type != VAR)
    {
        result = this->left->lowestOperationType();
    }
    else if (this->right != NULL && this->right->type != VAR)
    {
        result = this->right->lowestOperationType();
    }
    return result;
}




