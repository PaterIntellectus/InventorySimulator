#include "inventory.h"

Inventory::Inventory(int id, int rows_num, int columns_num, const QString &inventory_name, bool is_source)
    : mId{ id },
      mInventoryName{ inventory_name },
      mRowsNum{ rows_num },
      mColumnsNum{ columns_num },
      mIsSource{ is_source }
{

}
