#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_AC_clicked()
{
    ui->input->setText("");
    ui->tmp_result->setText("");
}


void MainWindow::on_button_pow_clicked()
{
    ui->input->setText(ui->input->text()+"^");
}


void MainWindow::on_button_mod_clicked()
{
    ui->input->setText(ui->input->text()+"%");
}


void MainWindow::on_button_div_clicked()
{
    ui->input->setText(ui->input->text()+"/");
}


void MainWindow::on_button_7_clicked()
{
    ui->input->setText(ui->input->text()+"7");
}


void MainWindow::on_button_8_clicked()
{
    ui->input->setText(ui->input->text()+"8");
}


void MainWindow::on_button_9_clicked()
{
    ui->input->setText(ui->input->text()+"9");
}


void MainWindow::on_button_multi_clicked()
{
    ui->input->setText(ui->input->text()+"*");
}


void MainWindow::on_button_4_clicked()
{
    ui->input->setText(ui->input->text()+"4");
}


void MainWindow::on_button_5_clicked()
{
    ui->input->setText(ui->input->text()+"5");
}


void MainWindow::on_button_6_clicked()
{
    ui->input->setText(ui->input->text()+"6");
}


void MainWindow::on_button_sub_clicked()
{
    ui->input->setText(ui->input->text()+"-");
}


void MainWindow::on_button_1_clicked()
{
    ui->input->setText(ui->input->text()+"1");
}


void MainWindow::on_button_2_clicked()
{
    ui->input->setText(ui->input->text()+"2");
}


void MainWindow::on_button_3_clicked()
{
    ui->input->setText(ui->input->text()+"3");
}


void MainWindow::on_button_plus_clicked()
{
    ui->input->setText(ui->input->text()+"+");
}


void MainWindow::on_button_0_clicked()
{
    ui->input->setText(ui->input->text()+"0");
}


void MainWindow::on_button_comma_clicked()
{
    ui->input->setText(ui->input->text()+",");
}


void MainWindow::on_button_del_clicked()
{
    ui->input->setText(ui->input->text().length() > 1 ? ui->input->text().chopped(1) : "");
}


void MainWindow::on_button_equal_clicked()
{
    ui->tmp_result->setText(eval(ui->input->text()));
}

QString MainWindow::eval(QString calcul)
{
    std::string cmds = "echo [ "+calcul.toStdString()+" ] | bc";
    FILE *cmd = popen(cmds.c_str(), "r");
    if(!cmd){
        return "Syntaxes error";
    }
    char *val = NULL;
    std::string result = "";
    while(!feof(cmd)){
        if(fgets(val, 255, cmd)!=NULL){
            result += val;
        }
    }

    pclose(cmd);

    return QString::fromStdString(result);
}
