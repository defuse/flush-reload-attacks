#include <QtCore/QScopedPointer>
#include <QtTest/QtTest>

#include "goo/GooString.h"

class TestGooString : public QObject
{
    Q_OBJECT
private slots:
    void testInsertData_data();
    void testInsertData();
    void testInsert();
    void testFormat();
};

void TestGooString::testInsertData_data()
{
    QTest::addColumn<QByteArray>("string");
    QTest::addColumn<QByteArray>("addition");
    QTest::addColumn<int>("position");
    QTest::addColumn<QByteArray>("result");

    QTest::newRow("foo") << QByteArray("foo") << QByteArray("bar") << 0 << QByteArray("barfoo");
    QTest::newRow("<empty>") << QByteArray() << QByteArray("bar") << 0 << QByteArray("bar");
    QTest::newRow("foo+bar #1") << QByteArray("f+bar") << QByteArray("oo") << 1 << QByteArray("foo+bar");
    QTest::newRow("foo+bar #2") << QByteArray("fobar") << QByteArray("o+") << 2 << QByteArray("foo+bar");
    QTest::newRow("foo+bar #last") << QByteArray("foo+r") << QByteArray("ba") << 4 << QByteArray("foo+bar");
    QTest::newRow("foo+bar #end") << QByteArray("foo+") << QByteArray("bar") << 4 << QByteArray("foo+bar");
    QTest::newRow("long #start") << QByteArray("very string") << QByteArray("long long long long long ") << 5 << QByteArray("very long long long long long string");
}

void TestGooString::testInsertData()
{
    QFETCH(QByteArray, string);
    QFETCH(QByteArray, addition);
    QFETCH(int, position);
    QFETCH(QByteArray, result);

    GooString goo(string.constData());
    QCOMPARE(goo.getCString(), string.constData());
    goo.insert(position, addition.constData());
    QCOMPARE(goo.getCString(), result.constData());
}

void TestGooString::testInsert()
{
    {
    GooString goo;
    goo.insert(0, ".");
    goo.insert(0, "This is a very long long test string");
    QCOMPARE(goo.getCString(), "This is a very long long test string.");
    }
    {
    GooString goo;
    goo.insert(0, "second-part-third-part");
    goo.insert(0, "first-part-");
    QCOMPARE(goo.getCString(), "first-part-second-part-third-part");
    }
}

void TestGooString::testFormat()
{
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:d},{1:x}", 1, 0xF));
        QCOMPARE(goo->getCString(), "1,f");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:d},{0:x},{0:X},{0:o},{0:b},{0:w}", 0xA));
        QCOMPARE(goo->getCString(), "10,a,A,12,1010,          ");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:d},{0:x},{0:X},{0:o},{0:b}", -0xA));
        QCOMPARE(goo->getCString(), "-10,-a,-A,-12,-1010");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:c}{1:c}{2:c}{3:c}",
            'T', (char)'E', (short)'S', (int)'T'));
        QCOMPARE(goo->getCString(), "TEST");

        const QScopedPointer<GooString> goo2(GooString::format("{0:s} {1:t}", "TEST", goo.data()));
        QCOMPARE(goo2->getCString(), "TEST TEST");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:ud} {1:d} {2:d}",
            UINT_MAX, INT_MAX, INT_MIN));
        const QByteArray expected = QString("%1 %2 %3").arg(UINT_MAX).arg(INT_MAX).arg(INT_MIN).toLatin1();
        QCOMPARE(goo->getCString(), expected.constData());
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:uld} {1:ld} {2:ld}",
            ULONG_MAX, LONG_MAX, LONG_MIN));
        const QByteArray expected = QString("%1 %2 %3").arg(ULONG_MAX).arg(LONG_MAX).arg(LONG_MIN).toLatin1();
        QCOMPARE(goo->getCString(), expected.constData());
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:ulld} {1:lld} {2:lld}",
            ULLONG_MAX, LLONG_MAX, LLONG_MIN));
        const QByteArray expected = QString("%1 %2 %3").arg(ULLONG_MAX).arg(LLONG_MAX).arg(LLONG_MIN).toLatin1();
        QCOMPARE(goo->getCString(), expected.constData());
    }
    {
        const QScopedPointer<GooString> gooD(GooString::format("{0:.1f} {0:.1g} {0:.1gs} | {1:.1f} {1:.1g} {1:.1gs}", 1., .012));
        const QScopedPointer<GooString> gooF(GooString::format("{0:.1f} {0:.1g} {0:.1gs} | {1:.1f} {1:.1g} {1:.1gs}", 1.f, .012f));
        QCOMPARE(gooD->getCString(), "1.0 1 1 | 0.0 0 0.01");
        QCOMPARE(gooF->getCString(), "1.0 1 1 | 0.0 0 0.01");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{0:.4f} {0:.4g} {0:.4gs}", .012));
        QCOMPARE(goo->getCString(), "0.0120 0.012 0.012");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{{ SomeText {0:d} }}", 1));
        QCOMPARE(goo->getCString(), "{ SomeText 1 }");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("{{{{ {{ SomeText {0:d}", 2));
        QCOMPARE(goo->getCString(), "{{ { SomeText 2");
    }
    {
        const QScopedPointer<GooString> goo(GooString::format("SomeText {0:d} }} }}}}", 3));
        QCOMPARE(goo->getCString(), "SomeText 3 } }}");
    }
}

QTEST_MAIN(TestGooString)
#include "check_goostring.moc"

