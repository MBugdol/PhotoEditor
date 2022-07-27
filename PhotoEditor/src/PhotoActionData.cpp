#include "src/PhotoActionData.h"

PhotoActionData::PhotoActionData(const QString& text, const QString& action, const QStringList& args, QObject* parent)
    : QObject(parent), m_text(text), m_action(action), m_args(args) {}

QString PhotoActionData::text() const {
    return m_text;
}
void PhotoActionData::setText(const QString& text) {
    m_text = text;
    emit textChanged();
}

QString PhotoActionData::action() const {
    return m_action;
}
void PhotoActionData::setAction(const QString& action) {
    m_action = action;
    emit actionChanged();
}

QStringList PhotoActionData::args() const {
    return m_args;
}
void PhotoActionData::setArgs(const QStringList& args) {
    m_args = args;
    emit argsChanged();
}
