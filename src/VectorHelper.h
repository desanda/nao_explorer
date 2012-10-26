#ifndef VECTORHELPER_H_
#define VECTORHELPER_H_

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
	};
}

#endif /* VECTORHELPER_H_ */
