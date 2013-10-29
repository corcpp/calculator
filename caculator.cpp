#include <QtGui>
#include "caculator.h"

Caculator::Caculator()
{
    createActions();
    createMenus();

    //button of widget
    mainWidget = new QWidget;
    createMainWidget();
    setCentralWidget(mainWidget);

    //initialization
    dot = false;
    caculToNum = false;
    showEdit = "0.";
    caculSign = '\0';
    result = temp = "";
    //value of register
    regResult = "";

    //set widget's title and fixed size
    setWindowTitle(tr("Simple Caculator"));
    setWindowIcon(QIcon(":/images/icon.jpg"));
    setFixedSize(mainWidget->sizeHint().width(),
                  mainWidget->sizeHint().height());

}

void Caculator::createActions()
{
    aboutAction = new QAction(tr("&about Caculator"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("about Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void Caculator::createMenus()
{
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void Caculator::createMainWidget()
{
    //set show edit property
    lineEdit = new QLineEdit(tr("0."));
    lineEdit->setFixedSize(246, 27);
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setMaxLength(19);
    lineEdit->setReadOnly(true);
    QFont font = lineEdit->font();
    font.setPointSize(font.pointSize() + 8);
    lineEdit->setFont(font);

    //set second line widget
    emptyButton = new QPushButton(tr(""));
    emptyButton->setFixedSize(35, 25);
    emptyButton->setEnabled(false);

    //set color of palette
    QPalette palRed;
    palRed.setColor(QPalette::ButtonText, QColor(255,0,0));
    QPalette palBlue;
    palBlue.setColor(QPalette::ButtonText, QColor(0,0,225));

    backSpaceButton = new QPushButton(tr("Backspace"));
    backSpaceButton->setFixedSize(65, 25);
    backSpaceButton->setPalette(palRed);
    connect(backSpaceButton, SIGNAL(clicked()),
                this, SLOT(on_backSpaceButton()));

    ceButton = new QPushButton(tr("CE"));
    ceButton->setFixedSize(65, 25);
    ceButton->setPalette(palRed);
    connect(ceButton, SIGNAL(clicked()), this, SLOT(on_ceButton()));

    cButton = new QPushButton(tr("C"));
    cButton->setFixedSize(65, 25);
    cButton->setPalette(palRed);
    connect(cButton, SIGNAL(clicked()), this, SLOT(on_cButton()));

    QHBoxLayout *secondLayout = new QHBoxLayout;
    secondLayout->addWidget(emptyButton);
    secondLayout->addWidget(backSpaceButton);
    secondLayout->addWidget(ceButton);
    secondLayout->addWidget(cButton);

    //set third line widget
    mcButton = new QPushButton(tr("MC"));
    mcButton->setFixedSize(35, 25);
    mcButton->setPalette(palRed);
    connect(mcButton, SIGNAL(clicked()), this, SLOT(on_mcButton()));

    sevenButton = new QPushButton(tr("7"));
    sevenButton->setFixedSize(35, 25);
    sevenButton->setPalette(palBlue);
    sevenButton->setShortcut(tr("7"));
    connect(sevenButton, SIGNAL(clicked()),
            this, SLOT(on_sevenButton()));

    eightButton = new QPushButton(tr("8"));
    eightButton->setFixedSize(35, 25);
    eightButton->setPalette(palBlue);
    eightButton->setShortcut(tr("8"));
    connect(eightButton, SIGNAL(clicked()),
            this, SLOT(on_eightButton()));

    nineButton = new QPushButton(tr("9"));
    nineButton->setFixedSize(35, 25);
    nineButton->setPalette(palBlue);
    nineButton->setShortcut(tr("9"));
    connect(nineButton, SIGNAL(clicked()),
            this, SLOT(on_nineButton()));

    divideButton = new QPushButton(tr("/"));
    divideButton->setFixedSize(35, 25);
    divideButton->setPalette(palRed);
    divideButton->setShortcut(tr("/"));
    connect(divideButton, SIGNAL(clicked()),
            this, SLOT(on_divideButton()));

    sqrtButton = new QPushButton(tr("sqrt"));
    sqrtButton->setFixedSize(35, 25);
    sqrtButton->setPalette(palBlue);
    connect(sqrtButton, SIGNAL(clicked()),
            this, SLOT(on_sqrtButton()));

    QHBoxLayout *thirdLayout = new QHBoxLayout;
    thirdLayout->addWidget(mcButton);
    thirdLayout->addWidget(sevenButton);
    thirdLayout->addWidget(eightButton);
    thirdLayout->addWidget(nineButton);
    thirdLayout->addWidget(divideButton);
    thirdLayout->addWidget(sqrtButton);

    //set fourth line widget
    mrButton = new QPushButton(tr("MR"));
    mrButton->setFixedSize(35, 25);
    mrButton->setPalette(palRed);
    connect(mrButton, SIGNAL(clicked()),
            this, SLOT(on_mrButton()));

    fourButton = new QPushButton(tr("4"));
    fourButton->setFixedSize(35, 25);
    fourButton->setPalette(palBlue);
    fourButton->setShortcut(tr("4"));
    connect(fourButton, SIGNAL(clicked()),
            this, SLOT(on_fourButton()));

    fiveButton = new QPushButton(tr("5"));
    fiveButton->setFixedSize(35, 25);
    fiveButton->setPalette(palBlue);
    fiveButton->setShortcut(tr("5"));
    connect(fiveButton, SIGNAL(clicked()),
            this, SLOT(on_fiveButton()));

    sixButton = new QPushButton(tr("6"));
    sixButton->setFixedSize(35, 25);
    sixButton->setPalette(palBlue);
    sixButton->setShortcut(tr("6"));
    connect(sixButton, SIGNAL(clicked()),
            this, SLOT(on_sixButton()));

    multipButton = new QPushButton(tr("*"));
    multipButton->setFixedSize(35, 25);
    multipButton->setPalette(palRed);
    multipButton->setShortcut(tr("*"));
    connect(multipButton, SIGNAL(clicked()),
            this, SLOT(on_multipButton()));

    modButton = new QPushButton(tr("%"));
    modButton->setFixedSize(35, 25);
    modButton->setPalette(palBlue);
    connect(modButton, SIGNAL(clicked()),
            this, SLOT(on_modButton()));

    QHBoxLayout *fourLayout = new QHBoxLayout;
    fourLayout->addWidget(mrButton);
    fourLayout->addWidget(fourButton);
    fourLayout->addWidget(fiveButton);
    fourLayout->addWidget(sixButton);
    fourLayout->addWidget(multipButton);
    fourLayout->addWidget(modButton);

    //set five line widget
    msButton = new QPushButton(tr("MS"));
    msButton->setFixedSize(35, 25);
    msButton->setPalette(palRed);
    connect(msButton, SIGNAL(clicked()),
            this, SLOT(on_msButton()));

    oneButton = new QPushButton(tr("1"));
    oneButton->setFixedSize(35, 25);
    oneButton->setPalette(palBlue);
    connect(oneButton, SIGNAL(clicked()),
            this, SLOT(on_oneButton()));

    twoButton = new QPushButton(tr("2"));
    twoButton->setFixedSize(35, 25);
    twoButton->setPalette(palBlue);
    connect(twoButton, SIGNAL(clicked()),
            this, SLOT(on_twoButton()));

    threeButton = new QPushButton(tr("3"));
    threeButton->setFixedSize(35, 25);
    threeButton->setPalette(palBlue);
    connect(threeButton, SIGNAL(clicked()),
            this, SLOT(on_threeButton()));

    subButton = new QPushButton(tr("-"));
    subButton->setFixedSize(35, 25);
    subButton->setPalette(palRed);
    subButton->setShortcut(tr("-"));
    connect(subButton, SIGNAL(clicked()),
            this, SLOT(on_subButton()));

    recipButton = new QPushButton(tr("1/x"));
    recipButton->setFixedSize(35, 25);
    recipButton->setPalette(palBlue);
    connect(recipButton, SIGNAL(clicked()),
            this, SLOT(on_recipButton()));

    QHBoxLayout *fiveLayout = new QHBoxLayout;
    fiveLayout->addWidget(msButton);
    fiveLayout->addWidget(oneButton);
    fiveLayout->addWidget(twoButton);
    fiveLayout->addWidget(threeButton);
    fiveLayout->addWidget(subButton);
    fiveLayout->addWidget(recipButton);

    //set sixth line widget
    mPlusButton = new QPushButton(tr("M+"));
    mPlusButton->setFixedSize(35, 25);
    mPlusButton->setPalette(palRed);
    connect(mPlusButton, SIGNAL(clicked()),
                this, SLOT(on_mPlusButton()));

    zeroButton = new QPushButton(tr("0"));
    zeroButton->setFixedSize(35, 25);
    zeroButton->setPalette(palBlue);
    zeroButton->setShortcut(tr("0"));
    connect(zeroButton, SIGNAL(clicked()),
            this, SLOT(on_zeroButton()));

    signButton = new QPushButton(tr("+/-"));
    signButton->setFixedSize(35, 25);
    signButton->setPalette(palBlue);
    connect(signButton, SIGNAL(clicked()),
            this, SLOT(on_signButton()));

    dotButton = new QPushButton(tr("."));
    dotButton->setFixedSize(35, 25);
    dotButton->setPalette(palBlue);
    dotButton->setShortcut(tr("."));
    connect(dotButton, SIGNAL(clicked()),
            this, SLOT(on_dotButton()));

    plusButton = new QPushButton(tr("+"));
    plusButton->setFixedSize(35, 25);
    plusButton->setPalette(palBlue);
    plusButton->setShortcut(tr("+"));
    connect(plusButton, SIGNAL(clicked()),
            this, SLOT(on_plusButton()));

    equalButton = new QPushButton(tr("="));
    equalButton->setFixedSize(35, 25);
    equalButton->setPalette(palRed);
    equalButton->setShortcut(tr("Enter"));
    connect(equalButton, SIGNAL(clicked()),
            this, SLOT(on_equalButton()));

    QHBoxLayout *sixLayout = new QHBoxLayout;
    sixLayout->addWidget(mPlusButton);
    sixLayout->addWidget(zeroButton);
    sixLayout->addWidget(signButton);
    sixLayout->addWidget(dotButton);
    sixLayout->addWidget(plusButton);
    sixLayout->addWidget(equalButton);

    //main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(secondLayout);
    mainLayout->addLayout(thirdLayout);
    mainLayout->addLayout(fourLayout);
    mainLayout->addLayout(fiveLayout);
    mainLayout->addLayout(sixLayout);

    mainWidget->setLayout(mainLayout);

}

void Caculator::digitNum(int num)
{
    //haven't input number
    if(showEdit == "0.")
    {
        //whether press dot
        if(dot == false)
            showEdit = QString::number(num) + ".";
        else
            showEdit.append(QString::number(num));
    }
    else
        if(showEdit.length() < 16)
        {
            if(dot == false){
                showEdit.insert(showEdit.length()-1, QString::number(num)); //如果dot是false插在小数点前面7.
            }
            else
            {
                showEdit.insert(showEdit.length(),QString::number(num));    //否则插在小数点后面.7
            }
        }
    caculToNum = false;
    lineEdit->setText(showEdit);
}

//private slots
void Caculator::about()
{
    QTextCodec *tc = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForTr(tc);
    QMessageBox::about(this, tr("About Qt Caculator"),
                       tr("<h2>Qt Caculator 1.0 [锋锋]菜</h2>"
                          "<p>Qt Caculator is a small application that "
                          "demonstrates QAction, QMainWinodow, QWidget, "
                          "QMenuBar, QPushButton, QLineEdit,  and many "
                          "other Qt classes."));
}

void Caculator::on_backSpaceButton()
{
    if(showEdit != "0.")
    {
        //one number that could is negtive or postive
        if((showEdit.length() == 3 && showEdit.at(0) == '-')
                || showEdit.length() == 2)
        {
            //clear this step
            on_ceButton();
        }
        else
        {
            if(showEdit.at(showEdit.length()-1) != '.')
                showEdit.remove(showEdit.length()-1,1); //如果是小数，3.333删除小数点后最后面的那一位
            else
                showEdit.remove(showEdit.length()-2,1); //如果是整数，333.删除小数点前面的那一位
        }

        lineEdit->setText(showEdit);
    }
}

//clear temp status
void Caculator::on_ceButton()
{
    dot = false;
    caculToNum = false;
    temp = "";
    showEdit = "0.";
    lineEdit->setText(showEdit);
}

//clear all status
void Caculator::on_cButton()
{
    dot = false;
    caculToNum = false;
    caculSign = '\0';
    result = temp = "";
    showEdit = "0.";
    lineEdit->setText(showEdit);
}

//clear register
void Caculator::on_mcButton()
{
    regResult = "";
    emptyButton->setText("");
}

void Caculator::on_sevenButton()
{
    digitNum(7);
}

void Caculator::on_eightButton()
{
    digitNum(8);
}

void Caculator::on_nineButton()
{
    digitNum(9);
}

void Caculator::on_divideButton()
{
    on_equalButton();
    caculSign = '/';
}

void Caculator::on_sqrtButton()
{
    if(showEdit.toDouble() >= 0)
    {
        double res = sqrt(showEdit.toDouble());
        showEdit = QString::number(res);
        if(!showEdit.contains('.'))
            showEdit.append(".");
        lineEdit->setText(showEdit);
    }
    else
    {
        on_cButton();
        lineEdit->setText("Input Error");
    }
    dot = false;
}

void Caculator::on_mrButton()
{
    if(!regResult.isEmpty())
    {
        result = regResult;
        if(!regResult.contains('.'))
            regResult.append(".");
        lineEdit->setText(regResult);

    showEdit = "0.";
    dot = false;
    caculToNum = true;
    }
}

void Caculator::on_fourButton()
{
    digitNum(4);
}

void Caculator::on_fiveButton()
{
    digitNum(5);
}

void Caculator::on_sixButton()
{
    digitNum(6);
}

void Caculator::on_multipButton()
{
    on_equalButton();;
    caculSign = '*';
}

void Caculator::on_modButton()
{

}

void Caculator::on_msButton()
{
    if(lineEdit->text().toDouble() != 0)
    {
        regResult = lineEdit->text();
        emptyButton->setText("M");

    }
}

void Caculator::on_oneButton()
{
    digitNum(1);
}

void Caculator::on_twoButton()
{
    digitNum(2);
}

void Caculator::on_threeButton()
{
    digitNum(3);
}

void Caculator::on_subButton()
{
    on_equalButton();
    caculToNum = '-';
}

void Caculator::on_recipButton()
{
    if(showEdit.toDouble() != 0)
    {
        double res = 1.0/showEdit.toDouble();
        showEdit = QString::number(res);
        if(!showEdit.contains('.'))
            showEdit.append(".");
        lineEdit->setText(showEdit);
    }
    else
    {
        on_cButton();
        lineEdit->setText("Input Error!");
    }
}

void Caculator::on_mPlusButton()
{
    if(regResult.isEmpty() && lineEdit->text().toDouble() != 0)
    {
        regResult = lineEdit->text();
        emptyButton->setText("M");
    }
    else
        if(!regResult.isEmpty() && lineEdit->text().toDouble() != 0)
        {
            QString regTemp = lineEdit->text();
            double res = regResult.toDouble() + regTemp.toDouble();
            if(res != 0)
                regResult = QString::number(res);
            else
                on_mcButton();
        }
}

void Caculator::on_zeroButton()
{
    digitNum(0);
}

void Caculator::on_signButton()
{
    if(showEdit != "0.")
    {
        if(showEdit.at(0) != '-')
            showEdit.insert(0, "-");
        else
            showEdit.remove(0,1);
        lineEdit->setText(showEdit);
    }
}

void Caculator::on_dotButton()
{
    if(dot == false)
        dot = true;
}

void Caculator::on_plusButton()
{
    on_equalButton();
    caculSign = '+';
}

void Caculator::on_equalButton()
{
    if(result.isEmpty())
        result = showEdit;      //如果result是空的，则把showedit的内容作为结果
    else  //result isn't empty, and now step isn't press on number
        if(caculToNum == false)  //否则，把showedit的内容作为 中间值
            temp = showEdit;

    double  res;
    bool flag = false;
    if(!temp.isEmpty() && caculToNum == false)
    {
        switch(caculSign.toAscii())
        {
        case '/':
            if(temp.toDouble() != 0)
                res = result.toDouble() / temp.toDouble();
            else
                flag = true;
            break;
        case '*':
            res = result.toDouble() * temp.toDouble();
            break;
        case '-':
            res = result.toDouble() - temp.toDouble();
            break;
        case '+':
            res = result.toDouble() + temp.toDouble();
            break;
        }

        if(flag)
        {
            on_cButton();
            lineEdit->setText("Input Error");
        }
        else
        {
            result = QString::number(res);
            if(!result.contains('.'))
                result.append(".");
            lineEdit->setText(result);
        }
    }

    showEdit = "0.";
    dot = false;
    caculToNum = true;
}
