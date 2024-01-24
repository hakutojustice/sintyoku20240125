#include "Map.h"
#include "BaseNumber.h"
#include "Dxlib.h"


void Map::Draw()
{
	
	//ƒQ[ƒ€ƒV[ƒ“‚Ìˆ—
	int MapHandle = LoadGraph("[A]Water3_Cave1_pipo.png");

	for (int x = 0; x< SumMapX; x++)
	{
		for (int y = 0; y < SumMapY; y++)
		{
		
                
			if (MakeMap[y][x] == 1)
			{				
			
			DrawRectGraph(GroundX, GroundY, CropX, CropY, MapIndicationX, MapIndicationY, MapHandle, true);
				
             
			//DrawRectRotaGraph(GroundX,GroundY, CropX, CropY,MapIndicationX,MapIndicationY,5,0,MapHandle,true);
				
				
			}

			
		}


	}

}


void Map::Update()
{
}



void Map::Init()
{
}

void Map::BackGround()
{
	DrawGraph(0,0,LoadGraph("pipo-battlebg009.jpg"),true);
}
