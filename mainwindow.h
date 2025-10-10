#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QProcess>
#include <QNetworkReply>
#include <QSettings>

#include "loginwindow/loginwindow.h"
#include "ssologinwebview/ssologinwebview.h"
#include "zjuconnectcontroller/zjuconnectcontroller.h"
#include "settingwindow/settingwindow.h"
#include "graphcaptchawindow/graphcaptchawindow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void addLog(const QString &log);

public slots:

    void cleanUpWhenQuit();

signals:

    void SetModeFinished();

    void WriteToProcess(const QByteArray &data);

protected:
    void closeEvent(QCloseEvent *e) override;

private:
    void checkUpdate();

    void upgradeSettings();

    void clearLog();

    void showNotification(
        const QString &title,
        const QString &content,
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon::Information
    );

    void initZjuConnect();

    void updateVersionInfo();

    struct {
        QString ui_version, ui_latest;
        QString core_version, core_latest;
    } versionInfo;

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *trayShowAction;
    QAction *trayCloseAction;
    ZjuConnectController *zjuConnectController;
    QNetworkAccessManager *checkUpdateNAM;
    QNetworkAccessManager *checkCoreUpdateNAM;
    QSettings *settings;

    QObject *diagnosisContext;

    SettingWindow *settingWindow;
    LoginWindow *loginWindow;
    SsoLoginWebView *ssoLoginWebView;
    GraphCaptchaWindow *graphCaptchaWindow;

    bool isFirstTimeSetMode;

    bool isZjuConnectLinked;
    bool isSystemProxySet;
    ZJU_ERROR zjuConnectError;
};

#endif //MAINWINDOW_H
