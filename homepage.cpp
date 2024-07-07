#include "homepage.h"
#include "ui_homepage.h"
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include "imagebutton.h" // Include the custom button header
#include "seat_selection.h"

homepage::homepage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::homepage)
    , firstButton(nullptr)
    , secondButton(nullptr)
    , frame(nullptr)
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);
    frame=ui->frame2;

    // Access the QStackedWidget from the UI
    QStackedWidget *stackedWidget = ui->stackedWidget;
    //button at the top or menu bar
    firstButton = ui->pushButton;
    secondButton= ui->pushButton_2;

    // Connect button to switch to first widget(Premerier this week)
    connect(firstButton, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0); // Switch to first widget
    });
    // Connect button to switch to second widget(comming soon)
    connect(secondButton, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(1); // Switch to second widget
    });

    // Show the first widget initially
    stackedWidget->setCurrentIndex(0);

    // Setup the layout for the first widget
    setupFirstWidgetLayout();
}

homepage::~homepage()
{
    delete ui;
}
void homepage::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    centerFrame();  // Ensure the frame stays centered when the window is resized
}
// frame centering (window size - frame size)/2 to determine the top left (x,y) position
void homepage::centerFrame()
{
    if (frame) {
        int x = (width() - frame->width()) / 2;
        int y = (height() - frame->height()) / 2;
        frame->move(x, y);
    }
}

void homepage::setupFirstWidgetLayout()
{
    // Check and establish database connection
    if (!connectToDatabase()) {
        qDebug() << "Failed to connect to the database.";
        return;
    }
    QWidget *firstWidget = ui->stackedWidget->widget(0);
    QGridLayout *layout = new QGridLayout(firstWidget);

    QSqlQuery query("SELECT movie_name, image_path FROM movie_information");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    int row = 0;  // Number of rows in the grid
    int col = 0;  // Number of columns in the grid
    const int buttonWidth = 350; // Width of the buttons
    const int buttonHeight= 350; // Height of the buttons

    while (query.next()) {
        QString buttonText = query.value(0).toString();
        QString imagePath = query.value(1).toString();

        ImageButton *buttonWidget = new ImageButton(imagePath, firstWidget);
        // QPushButton *buttonWidget = new QPushButton(firstWidget);
        // QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);

        // QLabel *imageLabel = new QLabel(buttonWidget);
        // QPixmap pixmap(imagePath);
        // if (pixmap.isNull()) {
        //     qDebug() << "Failed to load image:" << imagePath;
        //     continue; // Skip to the next iteration if image loading fails
        // }
        // imageLabel->setPixmap(pixmap.scaled(buttonWidth, buttonHeight/*, Qt::KeepAspectRatio*/));

        // //Set the button icon
        // buttonWidget->setIcon(QIcon(pixmap));
        // buttonWidget->setIconSize(buttonWidget->size()); // Make the icon size the same as the button size

        // buttonLayout->addWidget(imageLabel);
        // buttonWidget->setLayout(buttonLayout);

        buttonWidget->setMinimumSize(0, 0);
        buttonWidget->setMaximumSize(buttonWidth, buttonHeight);

        layout->addWidget(buttonWidget, row, col);

        col++;
        if (col == 3) {  // Assuming 3 columns per row
            col = 0;
            row++;
        }

        connect(buttonWidget, &QPushButton::clicked, [=]() {
            qDebug() << buttonText << " clicked!";
            Seat_selection *dialog = new Seat_selection(buttonText, this);
            dialog->exec();

        });
        db.close();
    }


    layout->setContentsMargins(20, 20 + 60, 10, 10);  // Set margins to prevent overlapping with the label
    layout->setSpacing(10);  // Set spacing between buttons
    firstWidget->setLayout(layout);
}
// database connection
bool homepage::connectToDatabase()
{
    // QString databasePath = QDir::currentPath() + "/Cinema-Sansaar/Database/movie.db";
    // QString databasePath = QCoreApplication::applicationDirPath() + "Cinema-Sansaar/Database/movie.db";
    QString databasePath = "C:/Users/DELL/Desktop/program test/Cinema-Sansaar/Database/movie.db";
    qDebug() << "Database Path:" << databasePath;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qDebug() << "Error: Could not connect to database. Error:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection established successfully.";
    return true;
}

void homepage::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        qDebug() << "Database connection closed.";
    }
}
