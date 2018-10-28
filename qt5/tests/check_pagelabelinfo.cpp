#include <QtTest/QtTest>

#include <poppler-private.h>

#include "PageLabelInfo_p.h"

#include "config.h"

class TestPageLabelInfo : public QObject
{
    Q_OBJECT
private slots:
    void testFromDecimal();
    void testFromDecimalUnicode();
    void testToRoman();
    void testFromRoman();
    void testToLatin();
    void testFromLatin();
};

void TestPageLabelInfo::testFromDecimal()
{
  std::string str{"2342"};
  const auto res = fromDecimal(str.data(), str.data() + str.size(), false);
  QCOMPARE(res.first, 2342);
  QCOMPARE(res.second, true);
}

void TestPageLabelInfo::testFromDecimalUnicode()
{
  std::unique_ptr<GooString> str(Poppler::QStringToUnicodeGooString(QString::fromLocal8Bit("2342")));
  const auto res = fromDecimal(str->getCString(), str->getCString() + str->getLength(), str->hasUnicodeMarker());
#ifndef HAVE_CODECVT
  QEXPECT_FAIL("", "unicode text to index fails without codecvt", Continue);
#endif
  QCOMPARE(res.first, 2342);
#ifndef HAVE_CODECVT
  QEXPECT_FAIL("", "unicode text to index fails without codecvt", Continue);
#endif
  QCOMPARE(res.second, true);
}

void TestPageLabelInfo::testToRoman()
{
    GooString str;
    toRoman(177, &str, false);
    QCOMPARE (str.getCString(), "clxxvii");
}

void TestPageLabelInfo::testFromRoman()
{
    GooString roman("clxxvii");
    QCOMPARE(fromRoman(roman.getCString()), 177);
}

void TestPageLabelInfo::testToLatin()
{
    GooString str;
    toLatin(54, &str, false);
    QCOMPARE(str.getCString(), "bbb");
}

void TestPageLabelInfo::testFromLatin()
{
    GooString latin("ddd");
    QCOMPARE(fromLatin(latin.getCString()), 56);
}

QTEST_GUILESS_MAIN(TestPageLabelInfo)
#include "check_pagelabelinfo.moc"

