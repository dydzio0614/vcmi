#pragma once

#include "../gui/CIntObject.h"

/*
 * MiscWidgets.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

class CLabel;
class CCreatureAnim;
class CComponent;
class CGGarrison;
class CSelectableComponent;
struct InfoAboutArmy;
class CArmedInstance;
class IBonusBearer;
class CAnimImage;

/// Shows a text by moving the mouse cursor over the object
class CHoverableArea: public virtual CIntObject
{
public:
	std::string hoverText;

	void hover(bool on) override;

	CHoverableArea();
	virtual ~CHoverableArea();
};

/// Can interact on left and right mouse clicks, plus it shows a text when by hovering over it
class LRClickableAreaWText: public CHoverableArea
{
public:
	std::string text;

	LRClickableAreaWText();
	LRClickableAreaWText(const Rect & Pos, const std::string & HoverText = "", const std::string & ClickText = "");
	virtual ~LRClickableAreaWText();
	void init();

	void clickLeft(tribool down, bool previousState) override;
	void clickRight(tribool down, bool previousState) override;
};

/// base class for hero/town/garrison tooltips
class CArmyTooltip : public CIntObject
{
	void init(const InfoAboutArmy & army);
public:
	CArmyTooltip(Point pos, const InfoAboutArmy & army);
	CArmyTooltip(Point pos, const CArmedInstance * army);
};

/// Class for hero tooltip. Does not have any background!
/// background for infoBox: ADSTATHR
/// background for tooltip: HEROQVBK
class CHeroTooltip : public CArmyTooltip
{
	void init(const InfoAboutHero & hero);
public:
	CHeroTooltip(Point pos, const InfoAboutHero & hero);
	CHeroTooltip(Point pos, const CGHeroInstance * hero);
};

/// Class for town tooltip. Does not have any background!
/// background for infoBox: ADSTATCS
/// background for tooltip: TOWNQVBK
class CTownTooltip : public CArmyTooltip
{
	void init(const InfoAboutTown & town);
public:
	CTownTooltip(Point pos, const InfoAboutTown & town);
	CTownTooltip(Point pos, const CGTownInstance * town);
};

/// draws picture with creature on background, use Animated=true to get animation
class CCreaturePic : public CIntObject
{
private:
	CPicture * bg;
	CCreatureAnim * anim; //displayed animation
	CLabel * amount;

	void show(SDL_Surface * to) override;
public:
	CCreaturePic(int x, int y, const CCreature * cre, bool Big = true, bool Animated = true); //c-tor

	void setAmount(int newAmount);
};

/// Resource bar like that at the bottom of the adventure map screen
class CMinorResDataBar : public CIntObject
{
public:
	SDL_Surface * bg; //background bitmap
	void show(SDL_Surface * to) override;
	void showAll(SDL_Surface * to) override;
	CMinorResDataBar(); //c-tor
	~CMinorResDataBar(); //d-tor
};

/// Opens hero window by left-clicking on it
class CHeroArea: public CIntObject
{
	const CGHeroInstance * hero;
public:

	CHeroArea(int x, int y, const CGHeroInstance * _hero);

	void clickLeft(tribool down, bool previousState) override;
	void clickRight(tribool down, bool previousState) override;
	void hover(bool on) override;
};

/// Can interact on left and right mouse clicks
class LRClickableAreaWTextComp: public LRClickableAreaWText
{
public:
	int baseType;
	int bonusValue, type;
	void clickLeft(tribool down, bool previousState) override;
	void clickRight(tribool down, bool previousState) override;

	LRClickableAreaWTextComp(const Rect & Pos = Rect(0, 0, 0, 0), int BaseType = -1);
	CComponent * createComponent() const;
};

/// Opens town screen by left-clicking on it
class LRClickableAreaOpenTown: public LRClickableAreaWTextComp
{
public:
	const CGTownInstance * town;
	void clickLeft(tribool down, bool previousState) override;
	void clickRight(tribool down, bool previousState) override;
	LRClickableAreaOpenTown(const Rect & Pos, const CGTownInstance * Town);
};

class MoraleLuckBox : public LRClickableAreaWTextComp
{
	CAnimImage * image;
public:
	bool morale; //true if morale, false if luck
	bool small;

	void set(const IBonusBearer * node);

	MoraleLuckBox(bool Morale, const Rect & r, bool Small = false);
};
