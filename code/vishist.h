#ifndef VISHIST_H
#define VISHIST_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <math.h>

namespace Ui {
    class visHist;
}

class visHist : public QDialog
{
    Q_OBJECT

public:
    explicit visHist(QWidget *parent = 0);
    ~visHist();

public:
    QImage qwe;
    QString teste;
    QPixmap pixHist; // Histograma

public slots:
    void init();

private:
    Ui::visHist *ui;
};

#endif // VISHIST_H
