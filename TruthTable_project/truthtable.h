#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H
#include "node.h"
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>

class TruthTable
{
public:
    Node *root;
    QStringList variables;
    int nodesAmount;


    QList<QMap<QString, bool>> generateCombinations(QStringList variables);
    QList<QMap<QString, bool>> generateTruthTable();
    void writeTruthTableToCSV(const QList<QMap<QString, bool>>& truthTable, const QStringList& variableNames, const QString& fileName);

    TruthTable();
};

#endif // TRUTHTABLE_H
