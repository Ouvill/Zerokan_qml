#ifndef RESULTGRAPHFORM_H
#define RESULTGRAPHFORM_H

#include <QWidget>

namespace Ui {
class resultGraphForm;
}

class resultGraphForm : public QWidget
{
    Q_OBJECT

public:
    explicit resultGraphForm(QWidget *parent = 0);
    ~resultGraphForm();

private:
    Ui::resultGraphForm *ui;
};

#endif // RESULTGRAPHFORM_H
