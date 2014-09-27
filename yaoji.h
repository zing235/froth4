#ifndef YAOJI_H
#define YAOJI_H

#include <QObject>

class yaoji : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<int> YaojiList READ getYaojiList WRITE setYaojiList NOTIFY YaojiListChanged)

public:
    explicit yaoji(QObject *parent = 0);

QList<int> getYaojiList(void) const;
void setYaojiList(const QList<int> YaojiList);

Q_INVOKABLE void updateYaojiList();

signals:
void YaojiListChanged(void);

private:
QList<int> m_YaojiList;

public slots:

};

#endif // YAOJI_H
