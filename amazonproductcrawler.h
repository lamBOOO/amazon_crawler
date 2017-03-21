#ifndef AMAZONPRODUCTCRAWLER_H
#define AMAZONPRODUCTCRAWLER_H

#include "amazonproduct.h"
#include <QDebug>
#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QWebEnginePage>

class AmazonProductCrawler {
 public:
  AmazonProductCrawler();
  AmazonProduct GetProductInfo(QString /*asin*/);
 private:
  const QString kAmazonPriceOfferLink = "https://www.amazon.de/gp/offer-listing/";/*asin*/
  const QString kWhdID                = "A8KICS1PHF7ZO";
  const QString kAmzID                = "A3JWKAKR8XB7XF";
  void WaitForHtml();
  void WaitForLoad();
  QWebEnginePage web_page;
  QTextEdit html;
};

#endif // AMAZONPRODUCTCRAWLER_H
