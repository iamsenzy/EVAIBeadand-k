#include "esemenytabledelegate.h"

#include <QStyleOptionViewItem>
#include <QByteArray>
#include <QVector>
#include <QtGui>

EsemenyTableDelegate::EsemenyTableDelegate(QObject *parent) :
        QSqlRelationalDelegate(parent)
{
}

void EsemenyTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const
{

   QItemDelegate::paint(painter, option, index);

}

QWidget *EsemenyTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

  return QSqlRelationalDelegate::createEditor(parent, option, index); // különben a szokványos szerkesztõmezõt használjuk

}

void EsemenyTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QSqlRelationalDelegate::setEditorData(editor, index);

}

void EsemenyTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

   QSqlRelationalDelegate::setModelData(editor, model, index);

}
