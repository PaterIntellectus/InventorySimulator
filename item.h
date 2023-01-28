#ifndef ITEM_H
#define ITEM_H

#include <QString>
//#include <QFileInfo>

class Item
{
public:
    Item(int id, const QString &item_name, const QString &image_path);

    int id() const { return mId; }
    QString item_name() const { return mItem_name; }
    QString image_path() const { return mImage_path; }

private:
    int mId;
    QString mItem_name;
    QString mImage_path;
};

#endif // ITEM_H
