#include "amazonproductcrawler.h"

AmazonProductCrawler::AmazonProductCrawler() {
}

AmazonProduct AmazonProductCrawler::GetProductInfo(QString _asin) {
  web_page.load(kAmazonPriceOfferLink + _asin + "/ref=sr_1_1_olp?m=" + kAmzID);
  this->WaitForLoad();
  web_page.toHtml([&](const QString &result) mutable { html.setPlainText(result);});
  this->WaitForHtml();

  QString html_code = html.toPlainText();

  // Name
  const QString name_string = "<h1 class=\"a-size-large a-spacing-none\" role=\"main\">";
  int start = html_code.indexOf("</div>", html_code.indexOf(name_string));
  int end   = html_code.indexOf("</h1>", html_code.indexOf(name_string));
  QString name_container = html_code.mid(start+6, end-start-6);
  while (name_container.mid(0,1) == " " || name_container.mid(name_container.length()-1,1) == " ") {
    if (name_container.mid(0,1) == " ") name_container.remove(0,1);
    if (name_container.mid(name_container.length()-1,1) == " ")
      name_container.remove(name_container.length()-1,1);
  }
  QString name = name_container;

  // Prime Price
  const QString pp_string = "<span class=\"a-size-large a-color-price olpOfferPrice a-text-bold\">";
  int pp_start = html_code.indexOf(">", html_code.indexOf(pp_string));
  int pp_end   = html_code.indexOf("<", pp_start);
  QString pp_container = html_code.mid(pp_start+1, pp_end-pp_start-1);
  while (pp_container.mid(0,1) == " " || pp_container.mid(pp_container.length()-1,1) == " ") {
    if (pp_container.mid(0,1) == " ") pp_container.remove(0,1);
    if (pp_container.mid(pp_container.length()-1,1) == " ")
      pp_container.remove(pp_container.length()-1,1);
  }
  if (pp_container.left(4) == "EUR ") pp_container.remove(0,4);
  pp_container.replace(pp_container.length()-3,1,".");
  bool *pp_price_ok = new bool();
  float pp_price = pp_container.toFloat(pp_price_ok);

  // Whd Price
  web_page.load(kAmazonPriceOfferLink + _asin + "/ref=sr_1_1_olp?m=" + kWhdID);
  this->WaitForLoad();
  web_page.toHtml([&](const QString &result) mutable { html.setPlainText(result);});
  this->WaitForHtml();
  html_code = html.toPlainText();
  const QString whd_string = "<span class=\"a-size-large a-color-price olpOfferPrice a-text-bold\">";
  int whd_start = html_code.indexOf(">", html_code.indexOf(whd_string));
  int whd_end   = html_code.indexOf("<", whd_start);
  QString whd_container = html_code.mid(whd_start+1, whd_end-whd_start-1);
  while (whd_container.mid(0,1) == " " || whd_container.mid(whd_container.length()-1,1) == " ") {
    if (whd_container.mid(0,1) == " ") whd_container.remove(0,1);
    if (whd_container.mid(whd_container.length()-1,1) == " ")
      whd_container.remove(whd_container.length()-1,1);
  }
  if (whd_container.left(4) == "EUR ") whd_container.remove(0,4);
  whd_container.replace(whd_container.length()-3,1,".");
  bool *whd_price_ok = new bool();
  float whd_price = whd_container.toFloat(whd_price_ok);

  AmazonProduct product(_asin,name,pp_price,whd_price);
  return product;
}

void AmazonProductCrawler::WaitForLoad() {
  QEventLoop loop_waiter;
  QObject::connect(&web_page, SIGNAL(loadFinished(bool)), &loop_waiter,
                   SLOT(quit()));
  loop_waiter.exec();
  //qDebug() << "load finished";
}

void AmazonProductCrawler::WaitForHtml() {
  QEventLoop loop_waiter;
  QObject::connect(&html, SIGNAL(textChanged()), &loop_waiter, SLOT(quit()));
  loop_waiter.exec();
  //qDebug() << "html setted";
}
