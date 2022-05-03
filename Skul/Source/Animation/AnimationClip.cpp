#include "AnimationClip.h"

/**********************************************************
* 설명 : AnimationFrame구조체의 객체 초기화
***********************************************************/
AnimationFrame::AnimationFrame(const Texture tex, const IntRect coord)\
	:texture(tex), texCoord(coord)
{
}
