#pragma once

class TileIndex final
{
public:
	TileIndex() noexcept;
	TileIndex(int row, int column) noexcept;

	void setRow(int row) noexcept;
	void setColumn(int row) noexcept;

	int getRow() const noexcept;
	int getColumn() const noexcept;

	bool operator==(const TileIndex& index) const noexcept;
	bool operator!=(const TileIndex& index) const noexcept;

private:
	int mRow;
	int mColumn;
};
