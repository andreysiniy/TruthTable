#include <QtTest>
#include <../TruthTable_project/node.h>
// add necessary includes here

class lowestOperationType_tests : public QObject
{
    Q_OBJECT



private slots:
    void test_lowestOperationType_twoNodes();
    void test_lowestOperationType_fewNodes();
    void test_lowestOperationType_singleLevel();
    void test_lowestOperationType_twoLevels();
    void test_lowestOperationType_singleVarOperator();
    void test_lowestOperationType_lowestOnLeftSide();
    void test_lowestOperationType_lowestOnRightSide();
};

void lowestOperationType_tests::test_lowestOperationType_twoNodes()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node nota(NOT, "NOT A", nullptr, &a);

    Node expected_nota(NOT, "NOT A", nullptr, &a);
    QCOMPARE(nota.lowestOperationType()->type, expected_nota.type);
    QCOMPARE(nota.lowestOperationType()->name, expected_nota.name);
    QCOMPARE(nota.lowestOperationType()->left, expected_nota.left);
    QCOMPARE(nota.lowestOperationType()->right, expected_nota.right);
}

void lowestOperationType_tests::test_lowestOperationType_fewNodes()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);

    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    Node aandborcxord(XOR, "((A AND B) OR C) XOR D", &aandborc, &d);

    Node expected(AND, "A AND B", &a, &b);
    QCOMPARE(aandborcxord.lowestOperationType()->type, expected.type);
    QCOMPARE(aandborcxord.lowestOperationType()->name, expected.name);
    QCOMPARE(aandborcxord.lowestOperationType()->left, expected.left);
    QCOMPARE(aandborcxord.lowestOperationType()->right, expected.right);
}

void lowestOperationType_tests::test_lowestOperationType_singleLevel()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);

    Node expected(AND, "A AND B", &a, &b);

    QCOMPARE(aandb.lowestOperationType()->type, expected.type);
    QCOMPARE(aandb.lowestOperationType()->name, expected.name);
    QCOMPARE(aandb.lowestOperationType()->left, expected.left);
    QCOMPARE(aandb.lowestOperationType()->right, expected.right);

}

void lowestOperationType_tests::test_lowestOperationType_twoLevels()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);


    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);

    Node expected(AND, "A AND B", &a, &b);

    QCOMPARE(aandborc.lowestOperationType()->type, expected.type);
    QCOMPARE(aandborc.lowestOperationType()->name, expected.name);
    QCOMPARE(aandborc.lowestOperationType()->left, expected.left);
    QCOMPARE(aandborc.lowestOperationType()->right, expected.right);
}

void lowestOperationType_tests::test_lowestOperationType_singleVarOperator()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aorb(OR, "A OR B", &a, &b);
    Node notaorb(NOT, "NOT (A OR B)", nullptr, &aorb);

    Node expected(OR, "A OR B", &a, &b);

    QCOMPARE(notaorb.lowestOperationType()->type, expected.type);
    QCOMPARE(notaorb.lowestOperationType()->name, expected.name);
    QCOMPARE(notaorb.lowestOperationType()->left, expected.left);
    QCOMPARE(notaorb.lowestOperationType()->right, expected.right);
}

void lowestOperationType_tests::test_lowestOperationType_lowestOnLeftSide()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);

    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);

    Node expected(AND, "A AND B", &a, &b);

    QCOMPARE(aandborc.lowestOperationType()->type, expected.type);
    QCOMPARE(aandborc.lowestOperationType()->name, expected.name);
    QCOMPARE(aandborc.lowestOperationType()->left, expected.left);
    QCOMPARE(aandborc.lowestOperationType()->right, expected.right);
}

void lowestOperationType_tests::test_lowestOperationType_lowestOnRightSide()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);
    Node cord(OR, "C OR D", &c, &d);
    Node notcord(NOT, "NOT (C OR D)", nullptr, &cord);

    Node aandbornotcord(OR, "(A AND B) OR (NOT (C OR D))", &aandb, &notcord);

    Node expected(AND, "A AND B", &a, &b);

    QCOMPARE(aandbornotcord.lowestOperationType()->type, expected.type);
    QCOMPARE(aandbornotcord.lowestOperationType()->name, expected.name);
    QCOMPARE(aandbornotcord.lowestOperationType()->left, expected.left);
    QCOMPARE(aandbornotcord.lowestOperationType()->right, expected.right);
}

QTEST_APPLESS_MAIN(lowestOperationType_tests)

#include "tst_lowestoperationtype_tests.moc"
