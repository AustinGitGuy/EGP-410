#include "GridVisualizer.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Grid.h"
#include <Vector2D.h>
#include "Game.h"

GridVisualizer::GridVisualizer( Grid* pGrid )
:grid(pGrid)
,mDirty(true)
{
}

GridVisualizer::~GridVisualizer()
{
}

void GridVisualizer::refresh()
{
	const Color& color = BLACK_COLOR; 
	if( mDirty )
	{
		//remove old entries first
		removeAllEntriesOfColor( color );

		int size = grid->getGridWidth() * grid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for( int i=0; i<size; i++ )
		{
			if( grid->getValueAtIndex(i) != 0 )
			{
				addColor( i, color );
			}
		}
	}
	mDirty = false;
}

void GridVisualizer::addColor( int index, const Color& color )
{
	//set dirty flag
	mDirty = true;

	//find the existing entry in the map (if it exists)
	std::map< Color, std::vector<int>>::iterator iter = mColormap.find( color );

	if(iter != mColormap.end())//found the existing entry
	{
		iter->second.push_back( index );
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back( index );

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

void GridVisualizer::removeAllEntriesOfColor( const Color& color )
{
	//find the existing entry in the map (if it exists)
	std::map< Color, std::vector<int>>::iterator iter = mColormap.find( color );
	
	if( iter != mColormap.end() )
	{
		mColormap.erase( iter );
	}
}

void GridVisualizer::removeAllEntries()
{
	mColormap.clear();
}

void GridVisualizer::Draw( GraphicsBuffer& dest )
{
	if( mDirty )
	{
		refresh();
	}

	int gridHeight = grid->getGridHeight();
	int gridWidth = grid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = grid->getSquareSize();

	std::map< Color, std::vector<int>>::iterator iter;
	for( iter = mColormap.begin(); iter != mColormap.end(); ++iter )
	{
		std::vector<int> theIndices = iter->second;

		for( unsigned int i=0; i<theIndices.size(); i++ )
		{
			Vector2D ulPos = grid->getULCornerOfSquare( theIndices[i] );
			gpGame->getGraphicsSystem()->fillRegion(dest, ulPos, Vector2D( ulPos.getX() + squareSize, ulPos.getY() + squareSize ), iter->first );
		}
	}
}