#include "item.h"

Item::Item(int id, const QString &item_name, const QString &image_path)
    : mId{ id }, mItem_name{ item_name }, mImage_path{ image_path }
{

}

Item::Item(const QString &item_name, const QString &image_path)
    : Item(0, item_name, image_path)
{

}
