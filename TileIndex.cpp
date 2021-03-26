#include "TileIndex.hpp"

TileIndex::TileIndex() noexcept :
    mRow{0},
    mColumn{0}
{

}

TileIndex::TileIndex(int row, int column) noexcept :
    mRow{row},
    mColumn{column}
{

}

void TileIndex::setRow(int row) noexcept
{
    mRow = row;
}

void TileIndex::setColumn(int column) noexcept
{
    mColumn = column;
}

int TileIndex::getRow() const noexcept
{
    return mRow;
}

int TileIndex::getColumn() const noexcept
{
    return mColumn;
}

bool TileIndex::operator==(const TileIndex& index) const noexcept
{
    return (mRow == index.mRow) && (mColumn == index.mColumn);
}

bool TileIndex::operator!=(const TileIndex& index) const noexcept
{
    return !(*this == index);
}
