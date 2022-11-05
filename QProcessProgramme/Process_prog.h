#ifndef PROCESS_PROG_H
#define PROCESS_PROG_H
#include <QWidget>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui { class Process_prog; }
QT_END_NAMESPACE

class QSystemTrayIcon;

class Process_prog : public QWidget
{
    Q_OBJECT

public:
     Process_prog(QWidget *parent = nullptr);
    ~Process_prog();

private slots:
    void on_actionAjouterArguments_triggered();
    void on_actionSupprimer_argument_triggered();
    void on_Sortie_Button_clicked();
    void on_encour_Button_clicked();
    void on_toolButton_clicked();

private:
    void makeConfiguration();
    void makeConnection();
    Ui::Process_prog *ui;
    QProcess m_process;
    QSystemTrayIcon *mTrayIcon;
};
#endif // PROCESS_PROG_H
