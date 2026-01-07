#ifndef NEWANALYSIS_H
#define NEWANALYSIS_H

#include <QWidget>

namespace Ui {
class NewAnalysis;
}

class NewAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit NewAnalysis(QWidget *parent = nullptr);
    ~NewAnalysis();
    
    bool eventFilter(QObject *obj, QEvent *event) override;

    Ui::NewAnalysis* getUi() { return ui; }
    QString getUploadedFilePath() const { return uploadedFilePath; }

private slots:
    void onDataSourceChanged(int index);
    void onUploadFileClicked();

private:
    Ui::NewAnalysis *ui;
    QString uploadedFilePath;
};

#endif // NEWANALYSIS_H
