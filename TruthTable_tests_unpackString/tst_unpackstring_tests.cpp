#include <QtTest>
#include <../TruthTable_project/stringoperations.h>
// add necessary includes here

class unpackString_tests : public QObject
{
    Q_OBJECT
private slots:
    void test_unpackString_twoNodes();
    void test_unpackString_fewNodes();
    void test_unpackString_fewVariables();
    void test_unpackString_singleVarOperator();
    void test_unpackString_opTypeNameContainsAnotherOpType();
    void test_unpackString_notEnoughVars();
    void test_unpackString_notEnoughOperators();
    void test_unpackString_invalidVarName();
    void test_unpackString_emptyTree();
};


void unpackString_tests::test_unpackString_twoNodes()
{
    QString input = "A NOT";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    _root = unpackString(input, _variables, _nodesAmount);
    Node expected(NOT, "NOT A");
    int expected_nodesAmount = 2;
    QStringList expected_variables = {"A"};

    QCOMPARE(_root->type, expected.type);
    QCOMPARE(_root->name, expected.name);
    QCOMPARE(_nodesAmount, expected_nodesAmount);
    QCOMPARE(_variables, expected_variables);
}

void unpackString_tests::test_unpackString_fewNodes()
{
    QString input = "A B AND C OR D XOR";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    _root = unpackString(input, _variables, _nodesAmount);
    Node expected(XOR, "((A AND B) OR C) XOR D");
    int expected_nodesAmount = 7;
    QStringList expected_variables = {"A","B","C","D"};

    QCOMPARE(_root->type, expected.type);
    QCOMPARE(_root->name, expected.name);
    QCOMPARE(_nodesAmount, expected_nodesAmount);
    QCOMPARE(_variables, expected_variables);
}

void unpackString_tests::test_unpackString_fewVariables()
{
    QString input = "A B AND C OR";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    _root = unpackString(input, _variables, _nodesAmount);
    Node expected(OR, "(A AND B) OR C");
    int expected_nodesAmount = 5;
    QStringList expected_variables = {"A","B","C"};

    QCOMPARE(_root->type, expected.type);
    QCOMPARE(_root->name, expected.name);
    QCOMPARE(_nodesAmount, expected_nodesAmount);
    QCOMPARE(_variables, expected_variables);
}

void unpackString_tests::test_unpackString_singleVarOperator()
{
    QString input = "A B OR NOT";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    _root = unpackString(input, _variables, _nodesAmount);
    Node expected(NOT, "NOT (A OR B)");
    int expected_nodesAmount = 4;
    QStringList expected_variables = {"A", "B"};

    QCOMPARE(_root->type, expected.type);
    QCOMPARE(_root->name, expected.name);
    QCOMPARE(_nodesAmount, expected_nodesAmount);
    QCOMPARE(_variables, expected_variables);
}

void unpackString_tests::test_unpackString_opTypeNameContainsAnotherOpType()
{
    QString input = "A B XOR C D NOR NOT OR";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    _root = unpackString(input, _variables, _nodesAmount);
    Node expected(OR, "(A XOR B) OR (NOT (C NOR D))");
    int expected_nodesAmount = 8;
    QStringList expected_variables = {"A", "B", "C", "D"};

    QCOMPARE(_root->type, expected.type);
    QCOMPARE(_root->name, expected.name);
    QCOMPARE(_nodesAmount, expected_nodesAmount);
    QCOMPARE(_variables, expected_variables);
}

void unpackString_tests::test_unpackString_notEnoughVars()
{
    QString input = "A XOR";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    QList<error> exp;
    exp.append({
        NOT_ENOUGH_ARGUMENTS,
        2,
        "XOR"
               });
    exp.append({
        NOT_ENOUGH_OPERATORS,
        0,
        ""
               });
    bool errorIsFound = false;
    try {
    _root = unpackString(input, _variables, _nodesAmount);
    }
    catch (QList<error> e)
    {
        errorIsFound = true;
        QCOMPARE(e, exp);
    }
    QCOMPARE(errorIsFound, true);

}

void unpackString_tests::test_unpackString_notEnoughOperators()
{
    QString input = "A B NOT";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    QList<error> exp;
    exp.append({
        NOT_ENOUGH_OPERATORS,
        0,
        ""
               });
    bool errorIsFound = false;
    try {
    _root = unpackString(input, _variables, _nodesAmount);
    }
    catch (QList<error> e)
    {
        errorIsFound = true;
        QCOMPARE(e, exp);
    }
    QCOMPARE(errorIsFound, true);
}

void unpackString_tests::test_unpackString_invalidVarName()
{
    QString input = "A,B NOT";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    QList<error> exp;
    exp.append({
        UNKNOWN_SYMBOL,
        1,
        ","
               });
    bool errorIsFound = false;
    try {
    _root = unpackString(input, _variables, _nodesAmount);
    }
    catch (QList<error> e)
    {
        errorIsFound = true;
        QCOMPARE(e, exp);
    }
    QCOMPARE(errorIsFound, true);
}

void unpackString_tests::test_unpackString_emptyTree()
{
    QString input = "";
    QStringList _variables;
    int _nodesAmount;
    Node* _root;
    QList<error> exp;
    exp.append({
        EMPTY_TREE,
        0,
        ""
               });
    bool errorIsFound = false;
    try {
    _root = unpackString(input, _variables, _nodesAmount);
    }
    catch (QList<error> e)
    {
        errorIsFound = true;
        QCOMPARE(e, exp);
    }
    QCOMPARE(errorIsFound, true);
}
QTEST_APPLESS_MAIN(unpackString_tests)

#include "tst_unpackstring_tests.moc"
