// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>
// #include <QStackedWidget>

// #include "newAnalysis.h"
// #include "results.h"

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     explicit MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private:
//     Ui::MainWindow *ui;

//     QStackedWidget *stack;
//     QWidget *dashboardPage;
//     NewAnalysis *analysisPage;
//     Results *resultsPage;
// };

// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QProgressDialog>
#include <QMessageBox>

#include "newAnalysis.h"
#include "results.h"
#include "../analyzer/DataAnalyzer.h"
#include "../analyzer/RecommendationEngine.h"
#include "../benchmark/Benchmark.h"
#include "../core/BST.h"
#include "../core/HashMap.h"
#include "../core/Heap.h"
#include "../core/Trie.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSidebarItemClicked(int index);
    void onStartAnalysisClicked();
    void onLoadResultsClicked();
    void onBackButtonClicked();
    void onStartAnalysisFromNewPage();
    void onExportResultsClicked();
    void onNewAnalysisFromResults();
    void onSettingsClicked();
    void onHelpClicked();

private:
    // Analysis Input Structure
    struct AnalysisInputs {
        std::string dataType;
        int dataSize;
        int searchPercent;
        int insertPercent;
        int deletePercent;
        bool speedCritical;
        bool memoryConstrained;
        bool needsRangeQueries;
        bool needsPrefixSearch;
        bool needsPriorityQueue;
        bool isSorted;
        std::string datasetPath;
    };

    void runAnalysis(AnalysisInputs inputs);
    void updateResultsPage(const std::map<std::string, PerformanceMetrics>& results,
                           const DataAnalyzer::DataProfile& profile,
                           const std::vector<RecommendationEngine::StructureScore>& scores);
    std::vector<int> generateTestData(int size);
    std::vector<std::string> generateTestStrings(int size);

private:
    Ui::MainWindow *ui;

    QStackedWidget *stack;
    QWidget *dashboardPage;
    NewAnalysis *analysisPage;
    Results *resultsPage;

    // Backend components
    DataAnalyzer *dataAnalyzer;
    RecommendationEngine *recommendationEngine;
    Benchmark<int> *intBenchmark;
    Benchmark<std::string> *stringBenchmark;

    // Current analysis data
    std::map<std::string, PerformanceMetrics> currentResults;
    DataAnalyzer::DataProfile currentProfile;
    std::vector<RecommendationEngine::StructureScore> currentScores;
};

#endif // MAINWINDOW_H
