#ifndef ITEM_H
#define ITEM_H

#include <QString>
//#include <QFileInfo>

class Item
{
public:
    Item(int id, const QString &item_name, const QString &image_path);
    Item(const QString &item_name, const QString &image_path);

    int id() const { return mId; }
    QString itemName() const { return mItem_name; }
    QString imagePath() const { return mImage_path; }

private:
    int mId;
    QString mItem_name;
    QString mImage_path;
};

#endif // ITEM_H
