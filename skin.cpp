#include "skin.h"

skin::skin(QObject *parent)
    : QObject{parent}
{

}

QString skin::titleBackground() const
{
    return m_titleBackground;
}

void skin::setTitleBackground(const QString &newTitleBackground)
{
    if (m_titleBackground == newTitleBackground)
        return;
    m_titleBackground = newTitleBackground;
    emit titleBackgroundChanged();
}

QString skin::background() const
{
    return m_background;
}

void skin::setBackground(const QString &newBackground)
{
    if (m_background == newBackground)
        return;
    m_background = newBackground;
    emit backgroundChanged();
}

QString skin::reserverColor() const
{
    return m_reserverColor;
}

void skin::setReserverColor(const QString &newReserverColor)
{
    if (m_reserverColor == newReserverColor)
        return;
    m_reserverColor = newReserverColor;
    emit reserverColorChanged();
}

QString skin::textColor() const
{
    return m_textColor;
}

void skin::setTextColor(const QString &newTextColor)
{
    if (m_textColor == newTextColor)
        return;
    m_textColor = newTextColor;
    emit textColorChanged();
}
