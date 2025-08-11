#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <cstdio>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_AC_clicked();

    void on_button_pow_clicked();

    void on_button_mod_clicked();

    void on_button_div_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_multi_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_sub_clicked();

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_plus_clicked();

    void on_button_0_clicked();

    void on_button_comma_clicked();

    void on_button_del_clicked();

    void on_button_equal_clicked();

    QString eval(QString calcul);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
