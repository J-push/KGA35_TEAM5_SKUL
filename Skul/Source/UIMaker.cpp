#include "UIMaker.h"


void UIMaker::Init()
{
	spriteMainFrame.setTexture(*ResourceMgr::instance()->GetTexture("MAINFRAMETEX"));
	spriteMainFrame.setPosition(500, 500);
	spriteMainFrame.setScale(2.5, 2.5);


	spriteHpBar.setTexture(*ResourceMgr::instance()->GetTexture("HPBARTEX"));
	spriteHpBar.setPosition(608, 610);
	spriteHpBar.setScale(0.5, 2.5);

	SpriteGrimReaperIcon.setTexture(*ResourceMgr::instance()->GetTexture("REAPERICONTEX"));
	SpriteGrimReaperIcon.setPosition(480, 500);
	SpriteGrimReaperIcon.setScale(2.0, 2.0);

	SpriteGrimReaperSkill.setTexture(*ResourceMgr::instance()->GetTexture("REAPERSKILLTEX"));
	SpriteGrimReaperSkill.setPosition(642, 533);
	SpriteGrimReaperSkill.setScale(2.8, 2.8);


	
}

void UIMaker::Draw(sf::RenderWindow *window)
{
	window->draw(spriteMainFrame);
	window->draw(spriteHpBar);
	window->draw(SpriteGrimReaperIcon);
	window->draw(SpriteGrimReaperSkill);


}
