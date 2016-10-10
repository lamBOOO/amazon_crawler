#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
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

  QWidget *central;
  QTabWidget *tab_view;

  QGridLayout *main_layout;
  QGridLayout *database_layout;
  QFormLayout *database_input_formlayout;

  QGroupBox *database_box;

  QLabel *hostname_label;
  QLabel *database_name_label;
  QLabel *username_label;
  QLabel *password_label;
  QLabel *table_label;

  QLineEdit *hostname_edit;
  QLineEdit *database_name_edit;
  QLineEdit *username_edit;
  QLineEdit *password_edit;

  QPushButton *load_database_button;
  QPushButton *load_table_button;

  QComboBox *table_combobox;

  Controller *controller;
 private slots:
  void HandleLoadDatabase();
};

#endif // MAINWINDOW_H
