#ifndef DIALOGMEDIA_H
#define DIALOGMEDIA_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
    class dialogMedia;
}

class dialogMedia : public QDialog
{
    Q_OBJECT

public:
    explicit dialogMedia(QWidget *parent = 0);
    ~dialogMedia();

public:
    QString stringTamMask;
    QString stringGanho;
    int tamMask;
    float ganho;
    //QString indice[256];
    float indice[256];

signals:
    void terminou();

private slots:
    void on_lineEdit_tamMask_editingFinished();

    void on_pushButton_cancelar_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::dialogMedia *ui;
};

#endif // DIALOGMEDIA_H
