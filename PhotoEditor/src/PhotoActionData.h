#pragma once

#include <QObject>
#include <QUndoCommand>

class PhotoActionData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(QStringList args READ args WRITE setArgs NOTIFY argsChanged)
public:
    PhotoActionData(const QString& text, const QString& action, const QStringList& args, QObject* parent=0);

    QString text() const;
    void setText(const QString& text);

    QString action() const;
    void setAction(const QString& action);

    QStringList args() const;
    void setArgs(const QStringList& args);

signals:
    void textChanged();
    void actionChanged();
    void argsChanged();
private:
    QString m_text;
    QString m_action;
    QStringList m_args;
};
