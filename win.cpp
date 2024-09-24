#include "win.h"
#include <QMessageBox>
#include <QVBoxLayout>

Win::Win(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Возведение в квадрат"); // отображение названия виджета
    frame = new QFrame(this); // создаем рамку и связываем с окном
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);
    inputLabel = new QLabel("Введите число:", this); // создаем текстовую строку с именем, связываем с окном
    inputEdit = new QLineEdit("",this); // создаем строку ввода начального значения
    StrValidator *v=new StrValidator(inputEdit); // создаем объект контроля событий который прослушивает inputEdit
    inputEdit->setValidator(v); // устнавливаем валидатор для строки ввода
    outputLabel = new QLabel("Результат:", this); // текст с именем
    outputEdit = new QLineEdit("",this); // текстовое поле с именем
    nextButton = new QPushButton("Следующее", this); // кнопка обнуляющая результат
    exitButton = new QPushButton("Выход", this); // кнопка выхода
// компоновка приложения выполняется согласно рисунку 2
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame); // создаем вертикальный блок для элементов
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch();

    QVBoxLayout *vLayout2 = new QVBoxLayout();
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(frame);
    hLayout->addLayout(vLayout2);

    begin(); // обновляем программу

    connect(exitButton, &QPushButton::clicked, this, &Win::close);  // кнопка "Выход", сигнал - нажатие, слот - закрытие программы
    connect(nextButton, &QPushButton::clicked, this, &Win::begin);  // кнопка "Следующее", сигнал - нажатие, слот - обновление интерфейса программы
    connect(inputEdit, &QLineEdit::returnPressed, this, &Win::calc);// поле ввода, сигнал - начажите Enter, слот - вычисление
}

void Win::begin()
{
    inputEdit->clear(); // очищаем контент на линии ввода
    outputEdit->clear();
    nextButton->setEnabled(false); // опрделяет включен ли виджет(вкл обрабатывает события с клав и мыши, выкл не обрабатывает)
    nextButton->setDefault(false); // опередяет является ли кнопка кнопокой по умолчанию
    inputEdit->setEnabled(true);
    outputLabel->setVisible(true); // определяет является ли виджет видимым
    outputEdit->setVisible(true);
    outputEdit->setEnabled(false);
    inputEdit->setFocus(); // передает фокус ввода с клавиатуры этому виджету
}

void Win::calc() // вычисление значений
{
    bool Ok=true; float r,a;
    QString str=inputEdit->text(); // содержит текст редактирования строки
    a=str.toDouble(&Ok);
    if (Ok)
    {
        r=a*a;
        str.setNum(r); // Задает строке напечатанное значение в указанном , и возвращает ссылку на строку
        outputEdit->setText(str);
        inputEdit->setEnabled(false);
        //outputLabel->setVisible(true);
        //outputEdit->setVisible(true);
        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();
    }
    else
        if (!str.isEmpty())
        {
            QMessageBox msgBox(QMessageBox::Information,
            ("Возведение в квадрат."),
            ("Введено неверное значение."),
            QMessageBox::Ok);
            msgBox.exec(); //Отображает диалоговое окно как , блокирующее до тех пор, пока пользователь не закроет его
        }
}
