#include <QProcess>
#include <QCoreApplication>
#include <QFileInfo>

#include "utils.h"

namespace Utils {
    QString getCorePath()
    {
        QString program_filename;
        if (QSysInfo::productType() == "windows")
        {
            program_filename = "zju-connect.exe";
        }
        else
        {
            program_filename = "zju-connect";
        }
        return QCoreApplication::applicationDirPath() + "/" + program_filename;
    }

    QString checkCoreVersion(QObject* parent)
    {
        QProcess process(parent);
        process.start(Utils::getCorePath(), { "-version" });

        if (!process.waitForStarted()) {
            throw std::runtime_error("核心无法启动");
        }

        if (!process.waitForFinished()) {
            throw std::runtime_error("核心运行超时");
        }

        // 获取错误输出
        QByteArray errorOutput = process.readAllStandardError();
        if (!errorOutput.isEmpty()) {
            throw std::runtime_error(errorOutput);
        }

        // 获取标准输出
        QString output = process.readAllStandardOutput();

        const QString prefix("ZJU Connect v");
        if (!output.startsWith(prefix)) {
            throw std::runtime_error("无法解析核心版本号");
        }
        return output.mid(prefix.size()).trimmed();
    }
}


