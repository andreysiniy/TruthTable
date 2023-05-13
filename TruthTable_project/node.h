#ifndef NODE_H
#define NODE_H
#include <QString.h>

enum NodeType
{
    VAR,
    NOT,
    AND,
    OR,
    XOR,
    NAND,
    NOR,
    EQU
};

class Node
{
public:
    NodeType type;
    QString name;
    Node *left;
    Node *right;


    Node(NodeType type, QString name, Node *left = nullptr, Node *right = nullptr);

    NodeType stringToNodeType(QString input);
    bool evaluate(Node *node, const QMap<QString, bool> &variables);
    Node *lowestOperationType();

};

#endif // NODE_H
