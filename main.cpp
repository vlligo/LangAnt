//#include <QApplication>
//#include <QPushButton>
//
//int main(int argc, char* argv[]) {
//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
//}

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLabel>
#include <QRectF>
#include <QWidget>
#include <QInputDialog>
#include <QDir>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include "paint.h"

bool isdigit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch));
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    auto* c = new QWidget(nullptr);

    Colours window;
    window.resize(480, 360);
    window.setWindowTitle("Ant field");

    auto* label_command = new QLabel(c);
    QString command = "RL";
    window.command = command;
    QString pref = "Current command is: ";
    label_command->setText(pref + command);
    label_command->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label_command->setGeometry(10, 60, label_command->text().size() * 8, 40);
    int one_char_len = 9;
    auto read_command = [&]() {
        bool ok;
        QString text = QInputDialog::getText(c, "Langton ant command line",
                                             "Command to the ant:", QLineEdit::Normal,
                                             command, &ok);
        if (ok && !text.isEmpty()) {
            QString tot_text = pref + text;
            // check if command is invalid
//            if (text.size() % 2 == 1) {
//                tot_text = "Invalid input.\n" + pref + command;
//                label_command->resize(
//                        (tot_text.size() - 14) * one_char_len,
//                        label_command->height());
//                label_command->setText(tot_text);
//                c->resize(std::max(c->width(), label_command->width() + 10), c->height());
//                return;
//            }
            for (auto i = 0; i < (int)text.size(); i++) {
//                if (i % 2 == 0) {
                    if (text[i] != 'L' && text[i] != 'R') {
                        tot_text = "Invalid input.\n" + pref + command;
                        label_command->resize(
                                (tot_text.size() - 14) * one_char_len,
                                label_command->height());
                        label_command->setText(tot_text);
                        c->resize(std::max(c->width(), label_command->width() + 10), c->height());
                        return;
                    }
//                } else {
//                    if (!isdigit(text.at(i).QChar::toLatin1()) || ((QString)text.at(i)).toInt() > text.size() / 2 || ((QString)text.at(i)).toInt() < 1)  {
//                        tot_text = "Invalid input.\n" + pref + command;
//                        label_command->resize(
//                                (tot_text.size() - 14) * one_char_len,
//                                label_command->height());
//                        label_command->setText(tot_text);
//                        c->resize(std::max(c->width(), label_command->width() + 10), c->height());
//                        return;
//                    }
//                }
            }
            // submit  a command
            command = text;
            label_command->setText(tot_text);
            label_command->resize(tot_text.size() * one_char_len, label_command->height());
            c->resize(std::max(c->width(), label_command->width() + 10), c->height());
            window.reset();
            window.command = text;
        }
    };
    auto* button_read_new_command = new QPushButton("New command", c);
    button_read_new_command->resize(200, 50);
    QWidget::connect(button_read_new_command, &QPushButton::pressed, c, read_command);
    button_read_new_command->show();
    label_command->show();

    // Ant simulation
    // buttons of next turns
    auto next_turn = [&]() {
        window.next(1);
    };
    auto* button_next = new QPushButton("Next", c);
    button_next->setGeometry(200, 0, 100, 50);
    QWidget::connect(button_next, &QPushButton::pressed, c, next_turn);
    button_next->show();
    QString last_custom_number = "1000";
    auto next_last_custom_turns = [&]() {
        window.next(last_custom_number.toInt());
    };
    auto* button_next_last_custom = new QPushButton("Next " + last_custom_number, c);
    button_next_last_custom->setGeometry(300, 0, 100, 50);
    QWidget::connect(button_next_last_custom, &QPushButton::pressed, c, next_last_custom_turns);
    button_next_last_custom->show();
    auto next_custom_turns = [&]() {
        bool ok;
        QString text = QInputDialog::getText(c, "Custom number of turns",
                                             "Number of turns:", QLineEdit::Normal,
                                             last_custom_number, &ok);
        bool isNum;
        int value = text.toInt(&isNum);
        if (ok && !text.isEmpty()) {
            if (isNum) {
                last_custom_number = text;
                button_next_last_custom->setText("Next " + last_custom_number);
                window.next(value);
            } else {
                QMessageBox msgBox;
                msgBox.setText("Invalid number(" + text + ")");
                msgBox.exec();
            }
        }
    };
    auto* button_next_custom = new QPushButton("Next custom", c);
    button_next_custom->setGeometry(400, 0, 100, 50);
    QWidget::connect(button_next_custom, &QPushButton::pressed, c, next_custom_turns);
    auto clear_field = [&]() {
        window.reset();
    };
    // Clearing the field and quiting of all windows buttons
    auto* button_clear = new QPushButton("Clear", c);
    button_clear->setGeometry(500, 0, 100, 50);
    QWidget::connect(button_clear, &QPushButton::pressed, c, clear_field);
    button_clear->show();
    auto quit_all = [&]() {
        window.quit();
        c->close();
    };
    auto* button_quit = new QPushButton("Quit", c);
    button_quit->setGeometry(600, 0, 100, 50);
    QWidget::connect(button_quit, &QPushButton::pressed, c, quit_all);
    button_quit->show();
    window.show();
    c->show();
    return QApplication::exec();
}
