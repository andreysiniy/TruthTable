#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H
#include "node.h"
#include <QString>
#include <QStringList>

class TruthTable
{
public:
    Node *root;
    QStringList variables;
    int nodesAmount;


    QList<QMap<QString, bool>> generateCombinations(QStringList variables);
    QList<QMap<QString, bool>> generateTruthTable();

    TruthTable();
};

#endif // TRUTHTABLE_H
