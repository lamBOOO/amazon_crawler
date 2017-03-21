#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T01:25:41
#
#-------------------------------------------------

QT      += core gui webenginewidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = amazon_crawler
TEMPLATE = app

SOURCES += main.cc\
           mainwindow.cc \
           controller.cc \
           database.cc \
           amazonproductcrawler.cc \
    amazonproduct.cc

HEADERS += mainwindow.h \
           controller.h \
           database.h \
           amazonproduct.h \
           amazonproductcrawler.h
