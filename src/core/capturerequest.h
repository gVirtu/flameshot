// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#pragma once

#include <QPixmap>
#include <QString>
#include <QVariant>

class CaptureRequest
{
public:
    enum CaptureMode
    {
        FULLSCREEN_MODE,
        GRAPHICAL_MODE,
        SCREEN_MODE,
    };

    enum ExportTask
    {
        NO_TASK = 0,
        COPY_TASK = 1,
        SAVE_TASK = 2,
        PRINT_RAW_TASK = 4,
        PRINT_GEOMETRY_TASK = 8,
    };

    CaptureRequest(CaptureMode mode,
                   const uint delay = 0,
                   const QVariant& data = QVariant(),
                   ExportTask tasks = NO_TASK);

    void setStaticID(uint id);

    uint id() const;
    QByteArray serialize() const;
    static CaptureRequest deserialize(const QByteArray& data);
    uint delay() const;
    QString path() const;
    QVariant data() const;
    CaptureMode captureMode() const;
    ExportTask tasks() const;

    void addTask(ExportTask task);
    void addSaveTask(const QString& path = QString());
    void exportCapture(const QPixmap& p);

private:
    CaptureMode m_mode;
    uint m_delay;
    QString m_path;
    ExportTask m_tasks;
    QVariant m_data;

    bool m_forcedID;
    uint m_id;

    CaptureRequest() {}
};

using eTask = CaptureRequest::ExportTask;

inline eTask operator|(const eTask& a, const eTask& b)
{
    return static_cast<eTask>(static_cast<int>(a) | static_cast<int>(b));
}

inline eTask operator&(const eTask& a, const eTask& b)
{
    return static_cast<eTask>(static_cast<int>(a) & static_cast<int>(b));
}

inline eTask& operator|=(eTask& a, const eTask& b)
{
    a = static_cast<eTask>(static_cast<int>(a) | static_cast<int>(b));
    return a;
}
