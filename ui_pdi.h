/********************************************************************************
** Form generated from reading ui file 'pdi.ui'
**
** Created: Wed 15. Jul 02:50:16 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PDI_H
#define UI_PDI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pdi
{
public:
    QAction *actionSair;
    QAction *actionAbrir;
    QAction *actionSalvar;
    QWidget *centralWidget;
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pdi)
    {
        if (pdi->objectName().isEmpty())
            pdi->setObjectName(QString::fromUtf8("pdi"));
        pdi->resize(876, 663);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pdi->sizePolicy().hasHeightForWidth());
        pdi->setSizePolicy(sizePolicy);
        actionSair = new QAction(pdi);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        actionAbrir = new QAction(pdi);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        actionSalvar = new QAction(pdi);
        actionSalvar->setObjectName(QString::fromUtf8("actionSalvar"));
        centralWidget = new QWidget(pdi);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 380, 280));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 360, 251, 71));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(440, 10, 380, 280));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(440, 310, 380, 280));
        pdi->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(pdi);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 876, 21));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QString::fromUtf8("menuArquivo"));
        pdi->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pdi);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        pdi->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(pdi);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        pdi->setStatusBar(statusBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuArquivo->addAction(actionAbrir);
        menuArquivo->addAction(actionSalvar);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);

        retranslateUi(pdi);
        QObject::connect(actionSair, SIGNAL(activated()), pdi, SLOT(close()));

        QMetaObject::connectSlotsByName(pdi);
    } // setupUi

    void retranslateUi(QMainWindow *pdi)
    {
        pdi->setWindowTitle(QApplication::translate("pdi", "pdi", 0, QApplication::UnicodeUTF8));
        actionSair->setText(QApplication::translate("pdi", "Sair", 0, QApplication::UnicodeUTF8));
        actionAbrir->setText(QApplication::translate("pdi", "Abrir", 0, QApplication::UnicodeUTF8));
        actionSalvar->setText(QApplication::translate("pdi", "Salvar", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        pushButton_2->setText(QApplication::translate("pdi", "play", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("pdi", "pause", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("pdi", "next", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("pdi", "Image1", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("pdi", "Image2", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("pdi", "Estimar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label_3->setText(QString());
        menuArquivo->setTitle(QApplication::translate("pdi", "Arquivo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pdi: public Ui_pdi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDI_H
