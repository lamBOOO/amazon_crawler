#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <QSqlQueryModel>
#include <QComboBox>
#include <QDebug>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QPluginLoader>
#include <QPushButton>
#include <QString>
#include <QTableView>
#include <QTime>
#include <QWidget>

class MainWindow : public QMainWindow {
 Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
 private:
  const QString kHostname     = "localhost";
  const QString kDatabaseName = "amazon";
  const QString kUsername     = "root";
  const QString kPassword     = "password";

  QTabWidget *SetupTabView();
  QGroupBox *SetupDatabaseBox();
  QGroupBox *SetupProductBox();


  QWidget *central;
  QTabWidget *tab_view;

  QGridLayout *main_layout;
  QGridLayout *database_layout;
  QGridLayout *product_layout;
  QFormLayout *database_input_formlayout;

  QGroupBox *database_box;
  QTableView *table_view;
  QGroupBox *product_box;

  QLabel *hostname_label;
  QLabel *database_name_label;
  QLabel *username_label;
  QLabel *password_label;
  QLabel *table_label;

  QLineEdit *hostname_edit;
  QLineEdit *database_name_edit;
  QLineEdit *username_edit;
  QLineEdit *password_edit;
  QLineEdit *product_link_edit;

  QPushButton *load_database_button;
  QPushButton *load_table_button;
  QPushButton *add_product_button;

  QComboBox *table_combobox;

  Controller *controller;
 private slots:
  void HandleLoadDatabase();
  void HandleDatabaseTableLoad();
  void HandleAddProductToDatabase();
};

#endif // MAINWINDOW_H
