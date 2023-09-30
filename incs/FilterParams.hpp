#ifndef FILTER_PARAMS_HPP
#define FILTER_PARAMS_HPP

#include <QDate>
#include <QString>

struct FilterParams
{
    QString m_name            = "";
    QString m_description     = "";
    bool m_defaultTaskStatus  = true;
    bool m_progressTaskStatus = true;
    bool m_doneTaskStatus     = true;
    QDate m_minDate           = QDate(1900, 1, 1);
    QDate m_maxDate           = QDate(4444, 1, 1);

    FilterParams() = default;

    FilterParams(const QString& name, const QString& description, bool defaultTaskStatus, bool progressTaskStatus,
                 bool doneTaskStatus, const QDate& minDate, const QDate& maxDate) :
        m_name(name),
        m_description(description),
        m_defaultTaskStatus(defaultTaskStatus),
        m_progressTaskStatus(progressTaskStatus),
        m_doneTaskStatus(doneTaskStatus),
        m_minDate(minDate),
        m_maxDate(maxDate)
    {
    }

    bool isEqual(const FilterParams& y)
    {
        return (m_name == y.m_name && m_description == y.m_description && m_defaultTaskStatus == y.m_defaultTaskStatus &&
                m_progressTaskStatus == y.m_progressTaskStatus && m_doneTaskStatus == y.m_doneTaskStatus &&
                m_minDate == y.m_minDate && m_maxDate == y.m_maxDate);
    }
};

#endif  // FILTER_PARAMS_HPP