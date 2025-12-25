// #ifndef NEWANALYSIS_H
// #define NEWANALYSIS_H

// #include <QWidget>
// #include "../benchmark/PerformanceMetrics.h"
// #include "../analyzer/DataAnalyzer.h"


// namespace Ui {
// class NewAnalysis;
// }

// class NewAnalysis : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit NewAnalysis(QWidget *parent = nullptr);
//     ~NewAnalysis();

// private:
//     Ui::NewAnalysis *ui;
// };

// #endif // NEWANALYSIS_H

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
    
    // Override event filter to block wheel events on sliders
    bool eventFilter(QObject *obj, QEvent *event) override;

    // Public getters for UI elements (or make ui public)
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
