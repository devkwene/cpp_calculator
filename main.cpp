#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr) : QWidget(parent) {
        display = new QLineEdit(this);
        display->setReadOnly(true);
        display->setAlignment(Qt::AlignRight);
        display->setMaxLength(15);

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(display, 0, 0, 1, 4);

        QString buttons[4][4] = {
            {"7", "8", "9", "/"},
            {"4", "5", "6", "*"},
            {"1", "2", "3", "-"},
            {"0", "C", "=", "+"}
        };

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                QString text = buttons[row][col];
                QPushButton *btn = new QPushButton(text, this);
                layout->addWidget(btn, row + 1, col);

                connect(btn, &QPushButton::clicked, this, [=]() {
                    handleButton(text);
                });
            }
        }

        resize(300, 350);
    }

private:
    QLineEdit *display;
    QString currentOp = "";
    double firstValue = 0;

    void handleButton(QString text) {
        if (text == "C") {
            display->clear();
            firstValue = 0;
            currentOp = "";
        }
        else if (text == "+" || text == "-" || text == "*" || text == "/") {
            firstValue = display->text().toDouble();
            currentOp = text;
            display->clear();
        }
        else if (text == "=") {
            double secondValue = display->text().toDouble();
            double result = 0;

            if (currentOp == "+") result = firstValue + secondValue;
            else if (currentOp == "-") result = firstValue - secondValue;
            else if (currentOp == "*") result = firstValue * secondValue;
            else if (currentOp == "/") {
                if (secondValue == 0) {
                    display->setText("Error");
                    return;
                }
                result = firstValue / secondValue;
            }

            display->setText(QString::number(result));
        }
        else {
            display->setText(display->text() + text);
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.setWindowTitle("Qt Calculator");
    calculator.show();

    return app.exec();
}

