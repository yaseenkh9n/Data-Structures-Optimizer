
#include "mainwindow.h"
#include "gui/ui_mainwindow.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QProgressDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <fstream>
#include <random>
#include <thread>
#include <QStyleFactory>
#include <sstream>
#include <iostream>
#include <QtCharts>
#include <QTextBrowser>
#include <QTextBrowser>
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataAnalyzer(new DataAnalyzer()),
    recommendationEngine(new RecommendationEngine()),
    intBenchmark(new Benchmark<int>()),
    stringBenchmark(new Benchmark<std::string>()),
    userName("User")
{
    // Apply Modern Dark Theme
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53, 53, 53));
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Base, QColor(42, 42, 42));
    p.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    p.setColor(QPalette::ToolTipBase, Qt::white);
    p.setColor(QPalette::ToolTipText, Qt::white);
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor(42, 130, 218));
    p.setColor(QPalette::Highlight, QColor(42, 130, 218));
    p.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(p);
    
    // Additional styling for specific widgets
    QString styleSheet = R"(
        QMainWindow {
            background-color: #353535;
        }
        QDialog, QMessageBox {
            background-color: #0d1117;
            color: white;
        }
        QMessageBox QLabel {
            color: #ffffff;
            font-size: 14px;
        }
        QMessageBox QPushButton {
            background-color: #3d3d3d;
            border: 1px solid #555;
            padding: 6px 12px;
            border-radius: 4px;
            color: white;
            min-width: 80px;
        }
        QMessageBox QPushButton:hover {
            background-color: #4d4d4d;
        }
        QPushButton {
            background-color: #0d6efd;
            color: white;
            border-radius: 5px;
            padding: 8px 16px;
            font-weight: bold;
            border: none;
        }
        QPushButton:hover {
            background-color: #0b5ed7;
        }
        QPushButton:pressed {
            background-color: #0a58ca;
        }
        QListWidget {
            background-color: #353535;
            border-right: 1px solid #444;
            outline: none;
        }
        QListWidget::item {
            color: #ccc;
            padding: 12px;
            border-radius: 5px;
            margin: 2px 5px;
        }
        QListWidget::item:selected {
            background-color: #3d3d3d;
            color: white;
        }
        QListWidget::item:hover {
            background-color: #353535;
        }
        QLabel {
            color: #eee;
        }
        QComboBox, QSpinBox {
            background-color: #3d3d3d;
            color: white;
            border: 1px solid #555;
            padding: 5px;
            border-radius: 4px;
        }
        QProgressBar {
            border: 1px solid #444;
            border-radius: 5px;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: #0d6efd;
        }
    )";
    qApp->setStyleSheet(styleSheet);

    ui->setupUi(this);
    setMinimumSize(1200, 650);

    // Initialize User Profile
    ui->userNameLabel->setText(userName);
    ui->userAvatarLabel->setText(userName.left(1).toUpper());

    // STACK
    stack = new QStackedWidget(this);

    // Initial pages (Adding directly to stack)
    dashboardPage = new QWidget();
    if (ui->contentArea->layout()) {
        dashboardPage->setLayout(ui->contentArea->layout());
        // Zero out the margins of the dashboard layout we just took
        if (dashboardPage->layout()) {
            dashboardPage->layout()->setContentsMargins(0, 0, 0, 0);
        }
    }

    analysisPage = new NewAnalysis(this);
    resultsPage = new Results(this);
    aboutPage = new QWidget();
    setupAboutPage();

    stack->addWidget(dashboardPage); // 0
    stack->addWidget(analysisPage);  // 1
    stack->addWidget(resultsPage);   // 2
    stack->addWidget(aboutPage);     // 3

    // Create a SINGLE global glass card wrapping the stack
    mainGlassPanel = new QFrame(ui->contentArea);
    mainGlassPanel->setObjectName("mainGlassPanel");
    mainGlassPanel->setStyleSheet(R"(
        #mainGlassPanel {
            background: rgba(255, 255, 255, 0.04);
            border: 1px solid rgba(255, 255, 255, 0.1);
            border-radius: 24px;
        }
    )");

    QVBoxLayout *glassLayout = new QVBoxLayout(mainGlassPanel);
    glassLayout->setContentsMargins(40, 40, 40, 40); // Initial dashboard padding
    glassLayout->addWidget(stack);

    // Clean up contentArea and add the glass card
    QLayout *oldLayout = ui->contentArea->layout();
    delete oldLayout;

    QVBoxLayout *contentLayout = new QVBoxLayout(ui->contentArea);
    contentLayout->setContentsMargins(15, 15, 15, 15); // Global outer spacing (smaller)
    contentLayout->addWidget(mainGlassPanel);

    stack->setCurrentIndex(0);

    // CONNECTIONS
    // Sidebar navigation
    connect(ui->sidebarList, &QListWidget::currentRowChanged, this, &MainWindow::onSidebarItemClicked);

    // Dashboard buttons
    connect(ui->primaryButton, &QPushButton::clicked, this, &MainWindow::onStartAnalysisClicked);
    connect(ui->secondaryButton, &QPushButton::clicked, this, &MainWindow::onLoadResultsClicked);

    // Analysis page buttons
    connect(analysisPage->findChild<QPushButton*>("backButton"), &QPushButton::clicked,
            this, &MainWindow::onBackButtonClicked);
    connect(analysisPage->findChild<QPushButton*>("startAnalysisButton"), &QPushButton::clicked,
            this, &MainWindow::onStartAnalysisFromNewPage);

    // Results page buttons
    connect(resultsPage->findChild<QPushButton*>("exportButton"), &QPushButton::clicked,
            this, &MainWindow::onExportResultsClicked);
    connect(resultsPage->findChild<QPushButton*>("newAnalysisButton"), &QPushButton::clicked,
            this, &MainWindow::onNewAnalysisFromResults);
    
    // Dashboard settings button
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);

    // Settings Button (New Analysis) - Assuming it's in the NewAnalysis widget
    // Since NewAnalysis is a custom widget promoted or added, we find it there.
    // analysisPage is likely the NewAnalysis widget instance.
    if (analysisPage) {
        QPushButton* analysisSettings = analysisPage->findChild<QPushButton*>("settingsButton");
        if (analysisSettings) {
            connect(analysisSettings, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);
        }
    }
    

}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataAnalyzer;
    delete recommendationEngine;
    delete intBenchmark;
    delete stringBenchmark;
}

void MainWindow::onSidebarItemClicked(int index)
{
    if (index >= 0 && index < stack->count()) {
        stack->setCurrentIndex(index);
        
        // Dynamic padding adjustment
        if (mainGlassPanel && mainGlassPanel->layout()) {
            if (index == 0 || index == 3) { // Dashboard or About
                mainGlassPanel->layout()->setContentsMargins(40, 40, 40, 40);
            } else if (index == 1) { // Analysis
                // Shorter bottom padding to increase scroll height as requested
                mainGlassPanel->layout()->setContentsMargins(20, 20, 20, 10);
            } else { // Results
                mainGlassPanel->layout()->setContentsMargins(20, 20, 20, 20);
            }
        }
    }
}

void MainWindow::onStartAnalysisClicked()
{
    stack->setCurrentIndex(1);
}

void MainWindow::onLoadResultsClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Load Previous Results", "", "CSV Files (*.csv);;All Files (*)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        if (fileInfo.suffix().toLower() != "csv") {
            QMessageBox::critical(this, "Invalid File Type", "Please select a .csv file.");
            return;
        }

        QFile qFile(fileName);
        if (qFile.size() == 0) {
             QMessageBox::critical(this, "Invalid File", "The selected file is empty.");
             return;
        }
        
        if (!qFile.open(QIODevice::ReadOnly)) {
             QMessageBox::critical(this, "Error", "Could not open file for reading.");
             return;
        }
        
        // Binary Check
        QByteArray chunk = qFile.read(1024);
        if (chunk.contains('\0')) {
             QMessageBox::critical(this, "Invalid Content", "The file appears to be binary. Please select a valid CSV results file.");
             qFile.close();
             return;
        }
        qFile.close();

        // OPEN FILE
        if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
             QMessageBox::critical(this, "Error", "Could not open file for reading text.");
             return;
        }
        

        
        QTextStream in(&qFile);
        QString line = in.readLine();
        
        // Validate Header (Simple check for existence of key columns)
        if (line.isNull() || (!line.contains("Structure") && !line.contains("DataSize"))) {
             QMessageBox::warning(this, "Unknown Format", "The CSV header does not match the expected format.\nExpected: Structure,DataSize,InsertTime...");
             return;
        }

        currentResults.clear();
        currentScores.clear();
        
        int successCount = 0;
        int failCount = 0;
        
        qDebug() << "Starting CSV parse. File:" << fileName;


        while (!in.atEnd()) {
            QString dataLine = in.readLine();
            if (dataLine.trimmed().isEmpty()) continue;

            QStringList parts = dataLine.split(',');
            if (parts.size() < 8) {
                failCount++;
                continue; 
            }

            // Clean parts (trim whitespace)
            for (auto& part : parts) part = part.trimmed();

            // Parse using QLocale::C (standard) first, then try System
            QLocale cLocale = QLocale::c();
            QLocale sysLocale = QLocale::system();
            
            PerformanceMetrics metrics(parts[0].toStdString());
            bool ok = true;
            bool totalOk = true;

            // Helper lambda for robust double parsing
            auto parseDouble = [&](const QString& str) -> double {
                bool conversionOk = false;
                double val = cLocale.toDouble(str, &conversionOk);
                if (!conversionOk) {
                    val = sysLocale.toDouble(str, &conversionOk);
                }
                if (!conversionOk) totalOk = false;
                return val;
            };

            metrics.dataSize = parts[1].toInt(&ok); 
            if (!ok) totalOk = false;

            metrics.insertTime = parseDouble(parts[2]);
            metrics.searchTime = parseDouble(parts[3]);
            metrics.deleteTime = parseDouble(parts[4]);
            metrics.totalTime = parseDouble(parts[5]);
            metrics.memoryUsed = static_cast<size_t>(parseDouble(parts[6]));
            
            if (totalOk) {
                // If we have a Score column (9th column), read it
                if (parts.size() >= 9) {
                    double importedScore = parseDouble(parts[8]);
                    metrics.score = importedScore;
                } else {
                    // Fallback for old files
                    metrics.score = 1000.0 / (metrics.totalTime + 1.0); 
                }
                
                currentResults[metrics.structureName] = metrics;

                RecommendationEngine::StructureScore score;
                score.name = metrics.structureName;
                score.totalScore = metrics.score; 
                currentScores.push_back(score);
                successCount++;
            } else {
                qDebug() << "Row failed parsing. Parts:" << parts;
                failCount++;
            }
        }
        
        // Sort scores
        std::sort(currentScores.begin(), currentScores.end(), 
                 [](const RecommendationEngine::StructureScore& a, const RecommendationEngine::StructureScore& b) {
                     return a.totalScore > b.totalScore;
                 });
                 
        // VALIDATION: Check if we actually loaded any valid data
        if (currentResults.empty()) {
            QString msg = "No valid performance data could be parsed.";
            if (failCount > 0) {
                msg += QString("\n\n%1 rows failed numeric parsing. Please check the decimal delimiters (dot vs comma) or file format.").arg(failCount);
            }
            QMessageBox::critical(this, "Invalid Data", msg);
            return;
        }

        // Normalize scores to percentage roughly
        if (!currentScores.empty()) {
            double maxScore = currentScores[0].totalScore;
            for (auto& score : currentScores) {
                score.totalScore = (score.totalScore / maxScore) * 100.0;
            }
        }

        updateResultsPage(currentResults, currentProfile, currentScores);
        
        // Update recent datasets for loaded file
        QFileInfo fi(fileName);
        recentDatasets.push_front(fi.fileName().toStdString());
        if (recentDatasets.size() > 3) recentDatasets.pop_back();
        updateDashboard();
        
        stack->setCurrentIndex(2); // Go to results
        
        QMessageBox::information(this, "Success", "Results loaded successfully.");
    }
}

void MainWindow::onBackButtonClicked()
{
    stack->setCurrentIndex(0);
}

void MainWindow::onStartAnalysisFromNewPage()
{
    // 1. Collect all inputs on the MAIN THREAD
    AnalysisInputs inputs;
    
    // Get configuration from UI
    QComboBox* dataTypeCombo = analysisPage->findChild<QComboBox*>("dataTypeCombo");
    QComboBox* dataSourceCombo = analysisPage->findChild<QComboBox*>("dataSourceCombo");
    QSlider* searchSlider = analysisPage->findChild<QSlider*>("searchSlider");
    QSlider* insertSlider = analysisPage->findChild<QSlider*>("insertSlider");
    QSlider* deleteSlider = analysisPage->findChild<QSlider*>("deleteSlider");
    QSpinBox* dataSizeSpin = analysisPage->findChild<QSpinBox*>("dataSizeSpinBox");
    
    // Get constraints
    QCheckBox* speedCheck = analysisPage->findChild<QCheckBox*>("speedCriticalCheck");
    QCheckBox* memoryCheck = analysisPage->findChild<QCheckBox*>("memoryConstrainedCheck");
    QCheckBox* rangeCheck = analysisPage->findChild<QCheckBox*>("rangeQueriesCheck");
    QCheckBox* prefixCheck = analysisPage->findChild<QCheckBox*>("prefixSearchCheck");
    QCheckBox* priorityCheck = analysisPage->findChild<QCheckBox*>("priorityQueueCheck");
    QCheckBox* sortedCheck = analysisPage->findChild<QCheckBox*>("sortedDataCheck");

    if (!dataTypeCombo || !searchSlider || !dataSizeSpin) {
        QMessageBox::critical(this, "Error", "Could not find UI elements required for analysis.");
        return;
    }

    inputs.dataType = dataTypeCombo->currentText().toStdString();
    inputs.dataSize = dataSizeSpin->value();
    
    // Check for uploaded file
    if (dataSourceCombo && dataSourceCombo->currentIndex() == 1) { // 1 is Upload
        inputs.datasetPath = analysisPage->getUploadedFilePath().toStdString();
        if (inputs.datasetPath.empty()) {
             QMessageBox::warning(this, "No File", "Please upload a dataset file or select 'Generate Random Data'.");
             return;
        }
    } else {
        inputs.datasetPath = "";
    }

    inputs.searchPercent = searchSlider->value();
    inputs.insertPercent = insertSlider->value();
    inputs.deletePercent = deleteSlider->value();
    
    inputs.speedCritical = speedCheck ? speedCheck->isChecked() : false;
    inputs.memoryConstrained = memoryCheck ? memoryCheck->isChecked() : false;
    inputs.needsRangeQueries = rangeCheck ? rangeCheck->isChecked() : false;
    inputs.needsPrefixSearch = prefixCheck ? prefixCheck->isChecked() : false;
    inputs.needsPriorityQueue = priorityCheck ? priorityCheck->isChecked() : false;
    inputs.isSorted = sortedCheck ? sortedCheck->isChecked() : false;

    // ===================== INPUT VALIDATION =====================
    QStringList errors;
    
    // 1. Validate Data Size
    if (inputs.dataSize <= 0) {
        errors << "• Data size must be greater than 0.";
    } else if (inputs.dataSize > 10000000) {
        errors << "• Data size is too large (max: 10,000,000).";
    }
    
    // 2. Validate Operation Percentages
    int totalPercent = inputs.searchPercent + inputs.insertPercent + inputs.deletePercent;
    if (totalPercent != 100) {
        errors << QString("• Operation percentages must add up to 100%% (currently %1%%).").arg(totalPercent);
    }
    
    // 3. Validate individual percentages
    if (inputs.searchPercent < 0 || inputs.insertPercent < 0 || inputs.deletePercent < 0) {
        errors << "• Operation percentages cannot be negative.";
    }
    
    // 4. Validate Data Type selection
    if (inputs.dataType.empty()) {
        errors << "• Please select a data type.";
    }
    
    // Show errors if any
    if (!errors.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid Input");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Please fix the following errors before starting analysis:");
        msgBox.setInformativeText(errors.join("\n"));
        msgBox.setStyleSheet(R"(
            QMessageBox { background-color: #353535; }
            QMessageBox QLabel { color: white; }
            QPushButton { background-color: #0d6efd; border: none; padding: 8px 16px; border-radius: 4px; color: white; }
            QPushButton:hover { background-color: #0b5ed7; }
        )");
        msgBox.exec();
        return;
    }
    // ===================== END VALIDATION =====================

    // Create progress dialog
    // NOTE: ProgressDialog is tricky with threads. We'll use a modal dialog that we close when done.
    QProgressDialog* progress = new QProgressDialog("Running Analysis...", "Cancel", 0, 0, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumDuration(0);
    progress->setRange(0, 0); // Indeterminate progress
    
    // Increase width to make it look like a bar
    progress->setFixedWidth(500);
    progress->setMinimumHeight(100);
    progress->setMaximumHeight(150);
    
    // Style the progress dialog
    progress->setStyleSheet(R"(
        QProgressDialog { 
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #0d1117, stop:1 #151b25);
            border: 1px solid rgba(0, 212, 255, 0.4);
            border-radius: 20px;
            color: #ffffff;
            padding: 20px;
        }
        QLabel { 
            color: #ffffff; 
            font-size: 16px; 
            font-weight: 600;
            margin-bottom: 10px;
            padding: 5px;
        }
        QPushButton { 
            background: rgba(255, 255, 255, 0.08); 
            border: 1px solid rgba(255, 255, 255, 0.15); 
            padding: 10px 25px; 
            border-radius: 12px; 
            color: rgba(255, 255, 255, 0.9); 
            font-weight: 600;
            margin-top: 15px;
        }
        QPushButton:hover { 
            background: rgba(239, 68, 68, 0.15); 
            border: 1px solid rgba(239, 68, 68, 0.4); 
            color: #ff5555; 
        }
        QProgressBar { 
            background: rgba(255, 255, 255, 0.06);
            border: 1px solid rgba(255, 255, 255, 0.12); 
            border-radius: 8px; 
            text-align: center; 
            color: white; 
            height: 12px;
            font-weight: bold;
            margin-top: 10px;
            margin-bottom: 5px;
        }
        QProgressBar::chunk { 
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, 
                stop:0 #00d4ff, 
                stop:0.5 #00b8e6,
                stop:1 #00d4ff);
            border-radius: 8px; 
        }
    )");
    
    progress->show();

    // Run analysis in background thread
    std::thread analysisThread([this, inputs, progress]() {
        // Run analysis (this calls no GUI functions)
        runAnalysis(inputs);
        
        // Clean up UI on main thread
        // Clean up UI on main thread
        QMetaObject::invokeMethod(this, [progress, this, inputs]() {
            progress->close();
            progress->deleteLater();
            
            // Add to recent datasets
            if (!inputs.datasetPath.empty()) {
                 QFileInfo fi(QString::fromStdString(inputs.datasetPath));
                 recentDatasets.push_front(fi.fileName().toStdString());
            } else {
                 recentDatasets.push_front("Generated Data (" + inputs.dataType + ")");
            }
            if (recentDatasets.size() > 3) recentDatasets.pop_back();

            updateResultsPage(currentResults, currentProfile, currentScores);
            updateDashboard(); // Update dashboard with new data
            stack->setCurrentIndex(2); // Switch to results page
        }, Qt::QueuedConnection);
    });

    analysisThread.detach(); // Detach since we handle cleanup via invokeMethod
}

void MainWindow::updateDashboard()
{
    // 1. Last Run Summary
    QLabel* lastRunValues = dashboardPage->findChild<QLabel*>("cardText");
    QLabel* bestStructureTitle = dashboardPage->findChild<QLabel*>("cardTitle_2");
    
    if (lastRunValues) {
        if (!recentDatasets.empty()) {
            lastRunValues->setText(QString::fromStdString(recentDatasets.front()));
        } else {
            lastRunValues->setText("No Analysis Run");
        }
    }
    
    if (bestStructureTitle) {
        if (!currentScores.empty()) {
            bestStructureTitle->setText(QString::fromStdString(currentScores[0].name));
        } else {
            bestStructureTitle->setText("-");
        }
    }
    
    // 2. Top Performing Structure
    QLabel* topScoreLabel = dashboardPage->findChild<QLabel*>("highlightText");
    QLabel* topMetricLabel = dashboardPage->findChild<QLabel*>("cardText_3");
    
    if (topScoreLabel && !currentScores.empty()) {
        topScoreLabel->setText(QString::number(currentScores[0].totalScore, 'f', 0) + "%");
    } else if (topScoreLabel) {
        topScoreLabel->setText("-");
    }
    if (topMetricLabel) topMetricLabel->setText("Performance Score");

    // 3. Recent Datasets
    QLabel* recent1 = dashboardPage->findChild<QLabel*>("cardText_4");
    QLabel* recent2 = dashboardPage->findChild<QLabel*>("cardText_5");
    QLabel* recent3 = dashboardPage->findChild<QLabel*>("cardText_6");
    
    if (recent1) recent1->setText(recentDatasets.size() > 0 ? QString::fromStdString(recentDatasets[0]) : "-");
    if (recent2) recent2->setText(recentDatasets.size() > 1 ? QString::fromStdString(recentDatasets[1]) : "-");
    if (recent3) recent3->setText(recentDatasets.size() > 2 ? QString::fromStdString(recentDatasets[2]) : "-");
}

std::vector<int> MainWindow::generateTestData(int size)
{
    std::vector<int> data;
    data.reserve(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < size; i++) {
        data.push_back(dis(gen));
    }

    return data;
}

std::vector<std::string> MainWindow::generateTestStrings(int size)
{
    std::vector<std::string> data;
    data.reserve(size);
    std::vector<std::string> prefixes = {"app", "ban", "cat", "dog", "ele", "fox"};
    std::vector<std::string> suffixes = {"le", "ana", "ch", "gy", "phant", "trot"};

    for (int i = 0; i < size; i++) {
        data.push_back(prefixes[i % prefixes.size()] + suffixes[i % suffixes.size()] + std::to_string(i));
    }

    return data;
}

void MainWindow::runAnalysis(AnalysisInputs inputs)
{
    // This runs in a BACKGROUND THREAD. Do NOT access widgets here.

    int totalOps = inputs.dataSize * 2; 

    if (inputs.dataType == "Integer") {
        std::vector<int> data;
        
        if (!inputs.datasetPath.empty()) {
            std::ifstream file(inputs.datasetPath);
            if (file.is_open()) {
                std::string line;
                int val;
                while (file >> val) {
                    data.push_back(val);
                }
                while (std::getline(file, line)) {
                     // Fallback for CSV-like parsing if simple stream extraction failing or mixed
                     if (line.empty()) continue;
                     std::stringstream ss(line);
                     std::string segment;
                     while(std::getline(ss, segment, ',')) {
                         try { data.push_back(std::stoi(segment)); } catch(...) {}
                     }
                }
                file.close();
            }
        }
        
        if (data.empty()) {
             if (!inputs.datasetPath.empty()) std::cerr << "Failed to load data or empty file. Generating random." << std::endl;
             data = generateTestData(inputs.dataSize);
        } else {
             // Update input size to match actual data
             // inputs.dataSize = data.size(); // Can't update const inputs copy here easily, but we use data.size() implicitly in analysis
        }

        // Analyze data
        currentProfile = dataAnalyzer->analyzeIntegerData(data);

        // Update profile with constraints
        currentProfile.speedCritical = inputs.speedCritical;
        currentProfile.memoryConstrained = inputs.memoryConstrained;
        currentProfile.needsRangeQueries = inputs.needsRangeQueries;
        currentProfile.needsPrefixSearch = inputs.needsPrefixSearch;
        currentProfile.needsPriorityQueue = inputs.needsPriorityQueue;
        currentProfile.isSorted = inputs.isSorted; // Assuming DataProfile has this field or logic respects it

        // Run benchmarks
        Benchmark<int>::OperationProfile opProfile(inputs.searchPercent, inputs.insertPercent,
                                                   inputs.deletePercent, totalOps);

        currentResults = intBenchmark->runAllTests(data, opProfile);

    } else if (inputs.dataType == "String") {
        std::vector<std::string> data;

        if (!inputs.datasetPath.empty()) {
            std::ifstream file(inputs.datasetPath);
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    std::stringstream ss(line);
                    std::string segment;
                    while(std::getline(ss, segment, ',')) {
                        // Trim
                        segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
                        segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
                        if (!segment.empty()) data.push_back(segment);
                    }
                }
                file.close();
            }
        }
        
        if (data.empty()) {
             if (!inputs.datasetPath.empty()) std::cerr << "Failed to load data or empty file. Generating random." << std::endl;
             data = generateTestStrings(inputs.dataSize);
        }

        // Analyze data
        currentProfile = dataAnalyzer->analyzeStringData(data);

        // Update profile with constraints
        currentProfile.speedCritical = inputs.speedCritical;
        currentProfile.memoryConstrained = inputs.memoryConstrained;
        currentProfile.needsRangeQueries = inputs.needsRangeQueries;
        currentProfile.needsPrefixSearch = inputs.needsPrefixSearch;
        currentProfile.needsPriorityQueue = inputs.needsPriorityQueue;
        // currentProfile.isSorted = inputs.isSorted;

        // Run benchmarks
        Benchmark<std::string>::OperationProfile opProfile(inputs.searchPercent, inputs.insertPercent,
                                                           inputs.deletePercent, totalOps);

        currentResults = stringBenchmark->runAllTests(data, opProfile);
    }

    // Generate recommendations
    RecommendationEngine::OperationProfile recOpProfile(inputs.searchPercent, inputs.insertPercent, inputs.deletePercent);
    RecommendationEngine::Weights weights(0.5, 0.3, 0.2);

    if (currentProfile.speedCritical) {
        weights = RecommendationEngine::Weights(0.7, 0.2, 0.1);
    } else if (currentProfile.memoryConstrained) {
        weights = RecommendationEngine::Weights(0.3, 0.6, 0.1);
    }

    currentScores = recommendationEngine->rankStructures(currentResults, currentProfile,
                                                         recOpProfile, weights);
    
    // PERSIST SCORES: Save calculated scores back to metrics so they can be exported
    for (const auto& score : currentScores) {
        if (currentResults.find(score.name) != currentResults.end()) {
            currentResults[score.name].score = score.totalScore;
        }
    }

    // Update results page on main thread
    QMetaObject::invokeMethod(this, [this]() {
        updateResultsPage(currentResults, currentProfile, currentScores);
    }, Qt::QueuedConnection);
}

void MainWindow::updateResultsPage(const std::map<std::string, PerformanceMetrics>& results,
                                   const DataAnalyzer::DataProfile& profile,
                                   const std::vector<RecommendationEngine::StructureScore>& scores)
{
    if (scores.empty()) return;

    // --- Performance Graph Implementation ---
    QFrame* graphPlaceholder = resultsPage->findChild<QFrame*>("graphPlaceholder");
    if (graphPlaceholder) {
        if (!graphPlaceholder->layout()) {
            QVBoxLayout* layout = new QVBoxLayout(graphPlaceholder);
            layout->setContentsMargins(0, 0, 0, 0);
        }
        
        // Clear existing widgets
        QLayoutItem* item;
        while ((item = graphPlaceholder->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        // Create Chart
        QBarSet *set0 = new QBarSet("Score");
        QStringList categories;
        
        for (const auto& score : scores) {
            // Round to 1 decimal place for cleaner display
            double roundedScore = std::round(score.totalScore * 10.0) / 10.0;
            *set0 << roundedScore;
            categories << QString::fromStdString(score.name);
        }

        // Style the bars (Cyan theme)
        set0->setColor(QColor(0, 212, 255));
        set0->setBorderColor(QColor(0, 212, 255));
        set0->setLabelColor(Qt::white);

        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->setLabelsVisible(true);
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
        series->setLabelsFormat("@value%");

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        
        // TRANSPARENCY FIXES
        chart->setBackgroundBrush(Qt::NoBrush);
        chart->setBackgroundVisible(false);
        chart->setPlotAreaBackgroundVisible(false);
        chart->legend()->setVisible(false);
        chart->setMargins(QMargins(0, 0, 0, 0));

        // X Axis
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setLabelsColor(Qt::white);
        axisX->setGridLineVisible(false);
        axisX->setLineVisible(false);
        QFont fontX = axisX->labelsFont();
        fontX.setPointSize(10);
        axisX->setLabelsFont(fontX);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Y Axis
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 110);
        axisY->setVisible(false);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        
        // COMPREHENSIVE TRANSPARENCY SETTINGS
        chartView->setBackgroundBrush(Qt::NoBrush);
        chartView->setStyleSheet("background: transparent; border: none;");
        chartView->setFrameShape(QFrame::NoFrame);
        chartView->setAttribute(Qt::WA_TranslucentBackground);
        
        // Ensure parent is also transparent just in case
        graphPlaceholder->setStyleSheet("background-color: transparent; border: none;");

        graphPlaceholder->layout()->addWidget(chartView);
    }
    // ----------------------------------------

    // Update top performer card
    QLabel* recommendationText = resultsPage->findChild<QLabel*>("recommendationText");
    QLabel* performanceValue = resultsPage->findChild<QLabel*>("performanceValue");
    QLabel* warningText = resultsPage->findChild<QLabel*>("warningText");

    const auto& winner = scores[0];
    recommendationText->setText(QString::fromStdString(winner.name));
    performanceValue->setText(QString::number(winner.totalScore, 'f', 1) + "%");

    // Set warning based on structure
    if (winner.name == "HashMap") {
        warningText->setText("⚠️ Hash collisions may occur with large datasets");
    } else if (winner.name == "BST") {
        warningText->setText("⚠️ Performance degrades if tree becomes unbalanced");
    } else if (winner.name == "Heap") {
        warningText->setText("⚠️ Not suitable for searching arbitrary elements");
    } else if (winner.name == "Trie") {
        warningText->setText("⚠️ Memory intensive for long strings");
    }

    // Update analysis info
    QLabel* datasetValue = resultsPage->findChild<QLabel*>("datasetValue");
    QLabel* sizeValue = resultsPage->findChild<QLabel*>("sizeValue");
    QLabel* operationsValue = resultsPage->findChild<QLabel*>("operationsValue");

    datasetValue->setText("Generated Test Data");
    sizeValue->setText(QString::number(profile.dataSize) + " elements");

    // Update operation percentages from sliders
    QSlider* searchSlider = analysisPage->findChild<QSlider*>("searchSlider");
    QSlider* insertSlider = analysisPage->findChild<QSlider*>("insertSlider");
    QSlider* deleteSlider = analysisPage->findChild<QSlider*>("deleteSlider");

    operationsValue->setText(QString("Search %1% | Insert %2% | Delete %3%")
                                 .arg(searchSlider->value())
                                 .arg(insertSlider->value())
                                 .arg(deleteSlider->value()));

    // Update result cards
    std::vector<QLabel*> scoreLabels = {
        resultsPage->findChild<QLabel*>("hashScore"),
        resultsPage->findChild<QLabel*>("bstScore"),
        resultsPage->findChild<QLabel*>("arrayScore")
    };

    std::vector<QLabel*> tagLabels = {
        resultsPage->findChild<QLabel*>("dsTag1"),
        resultsPage->findChild<QLabel*>("dsTag2"),
        resultsPage->findChild<QLabel*>("dsTag3")
    };

    int i = 0;
    for (const auto& score : scores) {
        if (i >= 3) break;

        if (i < scoreLabels.size()) {
            scoreLabels[i]->setText(QString::number(score.totalScore, 'f', 1) + "%");
        }
        if (i < tagLabels.size()) {
            tagLabels[i]->setText(QString::fromStdString(score.name));
        }
        i++;
    }
}

void MainWindow::onExportResultsClicked()
{
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export Results", "", 
                                                    "CSV Files (*.csv);;Text Files (*.txt);;All Files (*)",
                                                    &selectedFilter);

    if (!fileName.isEmpty()) {
        bool isCsv = false;
        
        // 1. Check existing extension
        if (fileName.endsWith(".csv", Qt::CaseInsensitive)) {
            isCsv = true;
        } else if (fileName.endsWith(".txt", Qt::CaseInsensitive)) {
            isCsv = false;
        } 
        // 2. If no extension (or unknown), check the selected filter
        else {
             if (selectedFilter.contains("CSV")) {
                 fileName += ".csv";
                 isCsv = true;
             } else {
                 fileName += ".txt"; // Default to text for Text Files or All Files
                 isCsv = false;
             }
        }

        if (isCsv) {
            // Export to CSV
            std::ofstream file(fileName.toStdString());
            if (file.is_open()) {
                file << "Structure,DataSize,InsertTime(ms),SearchTime(ms),DeleteTime(ms),"
                     << "TotalTime(ms),MemoryUsed(bytes),MemoryPerElement(bytes)\n";

                for (const auto& pair : currentResults) {
                    file << pair.second.toCSV() << "\n";
                }

                file.close();
                QMessageBox::information(this, "Export Successful",
                                         "Results exported to: " + fileName);
            } else {
                 QMessageBox::critical(this, "Export Failed", "Could not open file for writing.");
            }
        } else {
            // Export as text report
            std::ofstream file(fileName.toStdString());
            if (file.is_open()) {
                file << "Data Structure Optimizer - Analysis Report\n";
                file << "==========================================\n\n";

                file << "Data Profile:\n";
                file << "Size: " << currentProfile.dataSize << " elements\n";
                file << "Type: " << currentProfile.dataType << "\n";
                file << "Sorted: " << (currentProfile.isSorted ? "Yes" : "No") << "\n\n";

                file << "Performance Results:\n";
                for (const auto& pair : currentResults) {
                    file << pair.second.toString() << "\n";
                }

                file << "\nRecommendations:\n";
                file << recommendationEngine->generateRecommendation(currentScores);

                file.close();
                QMessageBox::information(this, "Export Successful",
                                         "Report exported to: " + fileName);
            } else {
                 QMessageBox::critical(this, "Export Failed", "Could not open file for writing.");
            }
        }
    }
}

void MainWindow::onNewAnalysisFromResults()
{
    stack->setCurrentIndex(1);
}

void MainWindow::onSettingsClicked()
{
    QDialog settingsDialog(this);
    settingsDialog.setWindowTitle("Settings");
    settingsDialog.setMinimumSize(350, 280);
    
    QVBoxLayout *layout = new QVBoxLayout(&settingsDialog);
    layout->setSpacing(15);
    
    QLabel *title = new QLabel("Data Structure Optimizer", &settingsDialog);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    
    QLabel *version = new QLabel("Version 1.0.0", &settingsDialog);
    version->setStyleSheet("color: #aaa;");
    version->setAlignment(Qt::AlignCenter);
    layout->addWidget(version);
    
    layout->addSpacing(10);
    
    // User Name Section
    QLabel *userLabel = new QLabel("Your Name:", &settingsDialog);
    userLabel->setStyleSheet("color: white; font-size: 14px;");
    layout->addWidget(userLabel);
    
    QLineEdit *nameInput = new QLineEdit(&settingsDialog);
    nameInput->setPlaceholderText("Enter your name...");
    nameInput->setText(userName);
    nameInput->setStyleSheet(R"(
        QLineEdit {
            background-color: #3d3d3d;
            border: 1px solid #555;
            border-radius: 6px;
            padding: 10px;
            color: white;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 1px solid #00d4ff;
        }
    )");
    layout->addWidget(nameInput);
    
    layout->addSpacing(10);
    
    QPushButton *saveBtn = new QPushButton("Save Profile", &settingsDialog);
    saveBtn->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #00d4ff, stop:1 #0099cc);
            color: white;
            border: none;
            padding: 10px;
            border-radius: 6px;
            font-weight: bold;
        }
        QPushButton:hover {
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #33dfff, stop:1 #00b8e6);
        }
    )");
    layout->addWidget(saveBtn);
    
    // Middle Spacer
    layout->addSpacing(10);
    QFrame* line = new QFrame(&settingsDialog);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: rgba(255, 255, 255, 0.1);");
    layout->addWidget(line);
    layout->addSpacing(10);

    QPushButton *resetBtn = new QPushButton("Reset Application Data", &settingsDialog);
    resetBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(255, 255, 255, 0.05);
            border: 1px solid rgba(255, 255, 255, 0.1);
            color: rgba(255, 255, 255, 0.7);
            padding: 8px;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: rgba(239, 68, 68, 0.1);
            border: 1px solid rgba(239, 68, 68, 0.3);
            color: #ef4444;
        }
    )");
    layout->addWidget(resetBtn);
    
    connect(resetBtn, &QPushButton::clicked, [this, &settingsDialog]() {
         QMessageBox msgBox(&settingsDialog);
         msgBox.setWindowTitle("Confirm Reset");
         msgBox.setText("Are you sure you want to reset all data?");
         msgBox.setInformativeText("This will clear recent datasets and results.");
         msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
         msgBox.setDefaultButton(QMessageBox::No);
         msgBox.setStyleSheet("QLabel{ color: white; }");
         
         if (msgBox.exec() == QMessageBox::Yes) {
             recentDatasets.clear();
             currentResults.clear();
             currentScores.clear();
             updateDashboard();
             settingsDialog.accept();
         }
    });

    layout->addSpacing(10);
    
    QPushButton *closeBtn = new QPushButton("Close", &settingsDialog);
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none;
            padding: 8px;
            color: #888;
        }
        QPushButton:hover {
            color: white;
        }
    )");
    layout->addWidget(closeBtn);
    
    connect(saveBtn, &QPushButton::clicked, [this, nameInput, &settingsDialog]() {
        userName = nameInput->text().trimmed();
        if (userName.isEmpty()) {
            userName = "User";
        }
        
        // Update the sidebar user profile
        if (ui->userNameLabel) ui->userNameLabel->setText(userName);
        if (ui->userAvatarLabel) ui->userAvatarLabel->setText(userName.left(1).toUpper());
        
        settingsDialog.accept();
    });
    
    connect(closeBtn, &QPushButton::clicked, &settingsDialog, &QDialog::reject);
    
    // Theme dialog
    settingsDialog.setStyleSheet(R"(
        QDialog { background-color: #1a1e26; color: white; }
        QLabel { color: white; }
    )");
    
    settingsDialog.exec();
}

void MainWindow::onAboutClicked()
{
    stack->setCurrentIndex(3);
}

void MainWindow::setupAboutPage() {
    QVBoxLayout *mainLayout = new QVBoxLayout(aboutPage);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(25);

    // Title
    QLabel *title = new QLabel("About DSA Optimizer", aboutPage);
    title->setStyleSheet("color: #00d4ff; font-size: 32px; font-weight: bold;");
    mainLayout->addWidget(title);

    // Subtitle/Info
    QLabel *version = new QLabel("Version 1.0.0 | Release Candidate", aboutPage);
    version->setStyleSheet("color: rgba(160, 180, 210, 0.7); font-size: 15px;");
    mainLayout->addWidget(version);

    // Horizontal Line
    QFrame *line = new QFrame(aboutPage);
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("background: rgba(255, 255, 255, 0.1); max-height: 1px;");
    mainLayout->addWidget(line);

    // Description
    QLabel *desc = new QLabel(aboutPage);
    desc->setText("Welcome to the <b>Data Structure Optimizer</b>, a premium analytical tool designed to simplify complex algorithmic decisions. "
                  "Our mission is to provide developers and computer scientists with real-time performance insights through intelligent benchmarking "
                  "and advanced recommendation engines.\n\n"
                  "Built with C++ and Qt, this application utilizes modern glassmorphism aesthetics to deliver a state-of-the-art user experience "
                  "without compromising on technical depth.");
    desc->setWordWrap(true);
    desc->setStyleSheet("color: #eee; font-size: 16px; line-height: 1.6;");
    mainLayout->addWidget(desc);

    // Features Section Header
    QLabel *featuresHeader = new QLabel("Core Capabilities", aboutPage);
    featuresHeader->setStyleSheet("color: #4ade80; font-size: 20px; font-weight: 600; margin-top: 15px; background: transparent;");
    mainLayout->addWidget(featuresHeader);

    // Two-Column Features Layout - Fixed Clipping
    QGridLayout *featuresGrid = new QGridLayout();
    featuresGrid->setHorizontalSpacing(40);
    featuresGrid->setVerticalSpacing(30);

    auto addFeature = [&](int row, int col, const QString& title, const QString& text) {
        QWidget *featWidget = new QWidget(aboutPage);
        QVBoxLayout *featLayout = new QVBoxLayout(featWidget);
        featLayout->setContentsMargins(0, 0, 0, 0);
        featLayout->setSpacing(8);

        QLabel *titleLabel = new QLabel("• " + title, featWidget);
        titleLabel->setStyleSheet("color: #00d4ff; font-size: 17px; font-weight: bold; background: transparent;");
        
        QLabel *contentLabel = new QLabel(text, featWidget);
        contentLabel->setStyleSheet("color: rgba(220, 230, 245, 0.8); font-size: 14px; background: transparent;");
        contentLabel->setWordWrap(true);
        
        featLayout->addWidget(titleLabel);
        featLayout->addWidget(contentLabel);
        featuresGrid->addWidget(featWidget, row, col);
    };

    addFeature(0, 0, "Deep Analysis", "Automated profiling of dataset characteristics.");
    addFeature(0, 1, "Live Benchmarking", "Comparative performance testing of BST, Hash, Trie, and Heaps.");
    addFeature(1, 0, "Smart Decisions", "Multi-criteria reasoning for optimal DS selection.");
    addFeature(1, 1, "Modern UI", "60FPS fluid glassmorphism animations.");

    mainLayout->addLayout(featuresGrid);

    mainLayout->addStretch();

    // Footer
    QLabel *footer = new QLabel("Developed by <b>Data Structure group 9</b><br>(M Yasin khan, Rana Abdullah, Anas Mehboob)", aboutPage);
    footer->setAlignment(Qt::AlignCenter);
    footer->setStyleSheet("color: rgba(160, 180, 210, 0.6); font-size: 14px; margin-top: 30px; background: transparent;");
    mainLayout->addWidget(footer);
}
