#include "Process_prog.h"
#include "ui_Process_prog.h"
#include <QSystemTrayIcon>
#include <QInputDialog>
#include <QFileDialog>

Process_prog::Process_prog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Process_prog)
{
    ui->setupUi(this);
    mTrayIcon = new QSystemTrayIcon(this);
    makeConfiguration();
    makeConnection();
}

Process_prog::~Process_prog()
{
    delete ui;
}

void Process_prog::makeConfiguration(){
    mTrayIcon->setIcon(QIcon("://ok_96px.png"));
    mTrayIcon->show();
    ui->listWidget->addActions({ui->actionAjouterArguments,ui->actionSupprimer_argument});

}

void Process_prog::makeConnection()
{
   auto finishedSignal = static_cast<void(QProcess::*)(int)>(&QProcess::finished);
   connect(&m_process,finishedSignal, [&](int exitCode)
   {
        mTrayIcon->showMessage(tr("message"),tr("processus termine avec: 1%...").arg(exitCode));
   });

   connect(&m_process, &QProcess::started, [&](){
       mTrayIcon->showMessage(tr("message"),tr("processus d'initialisation..."));
   });
}


void Process_prog::on_actionAjouterArguments_triggered()
{
    bool ok;
    auto arg = QInputDialog::getMultiLineText(this,tr("Arguments"),tr("Arguments"),"", &ok);

    if(!ok || arg.isEmpty()){
        return;
    }
    ui->listWidget->addItem(new QListWidgetItem(arg));
}


void Process_prog::on_actionSupprimer_argument_triggered()
{
    delete  ui->listWidget->currentItem();
}


void Process_prog::on_Sortie_Button_clicked()
{
    close();
}


void Process_prog::on_encour_Button_clicked()
{
    auto program = ui->Programme_lineEdit->text();
    const int argc = ui->listWidget->count();
    QStringList args;
    for(int x=0; x<argc; x++){
        args << ui->listWidget->item(x)->text();
    }
    m_process.setProgram(program);
    m_process.setArguments(args);
    m_process.start();
}


void Process_prog::on_toolButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,tr("Ouvrir"),"/", "EXE files(*.exe)");
    if(filename.isEmpty()){
        return;
    }
    ui->Programme_lineEdit->setText(filename);
}

