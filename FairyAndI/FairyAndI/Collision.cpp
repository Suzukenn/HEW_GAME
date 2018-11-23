#include "Collision.h"

//‹…‚Æ‚Ì“–‚½‚è”»’è
bool CollisionBall(LPD3DXVECTOR3 pos1, LPD3DXVECTOR3 pos2, float radius1, float radius2)
{
	float r = radius1 + radius2;
	r *= r;
	D3DXVECTOR3 v = *pos1 - *pos2;
	float d = D3DXVec3LengthSq(&v);
	if (d <= r)
	{
		return true;
	}
	return false;
}