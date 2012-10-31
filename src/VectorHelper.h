#ifndef VECTORHELPER_H_
#define VECTORHELPER_H_

using namespace std;

namespace NaoExplorer
{
class VectorHelper
	{
	public:
static int twoIndexToOne(int row, int col, int width)
{
//(width * row) + col

	return (width * row) + col;


}

static vector<int> oneIndexToTwo(int index, int width)
{
	//index / width = row
	//index % width = col

	vector<int> indexes(2);
	indexes[0] = index / width;
	indexes[1] = index % width;


	return indexes;


}
	};
}

#endif /* VECTORHELPER_H_ */
