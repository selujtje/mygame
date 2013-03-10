#ifndef _game_h_included_
#define _game_h_included_
#define dropElement(x)	if (x) { x->remove(); x = 0; }
//#define _IRR_STATIC_LIB_
#include <irrlicht.h>
#include <irrXML.h>
using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
/* RakNet, need to remove some
#include "RakNetStuff.h"
#include "DS_Multilist.h"
#include "RakString.h"
#include "RakNetTime.h"
*/
struct GUI
{
	GUI ()
	{
		memset ( this, 0, sizeof ( *this ) );
	}

	void drop()
	{
		dropElement ( QuitButton );

	}
    IGUIButton* QuitButton;
    IGUIButton* SettingsButton;
    IGUIButton* SinglePlayerButton;
    IGUISpinBox* XresField;
    IGUISpinBox* YresField;
    IGUICheckBox* FullscreenCheckbox;
    IGUICheckBox* AntiAliasCheckbox;
};

enum //GUI_IDs
{
        GUI_ID_SINGLE_PLAYER_BUTTON = 101,
        GUI_ID_SETTINGS_BUTTON,
        GUI_ID_QUIT_BUTTON,
        GUI_ID_XRES_FIELD,
        GUI_ID_YRES_FIELD,
        GUI_ID_FULLSCREEN_CHECKBOX,
        GUI_ID_ANTIALIAS_CHECKBOX
        //GUI_ID_TRANSPARENCY_SCROLL_BAR
};

enum//
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,


	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};

enum
{
    //0-63 reserved (not sure for what)
    //64-19materials like rock wood water and lava
    //128-255 plants and trees
    //


};

class Game : public IEventReceiver
{
public:

    Game();
    virtual bool OnEvent(const SEvent& event);
    int  GetGUIActive();
    void SetGUIActive( s32 command);
    void updatescreen();
    void createeventtimer();
    void updateeventtimer();
    bool init();
    bool mainmenu();
    bool takescreenshot();
    bool settingsmenu();
    bool singleplayer();
    bool SaveSettings();
    bool LoadSettings();
    bool loadresources();
    bool savegame();
    bool loadgame();
    void createProgressBar();
    void displayProgressBar(bool val);
    void updateProgressBar(int newValue, stringw msg);

    /////////////////////////////////////////////////////////
    bool playing;
    IrrlichtDevice* device;
    ICameraSceneNode* camera;
    IVideoDriver* driver;
    ISceneManager* smgr;
    IGUIEnvironment* env;
    io::IFileSystem* filesystem;
    SKeyMap keyMap[10];

    u32 now;
    //images
    IGUIImage* background,* progBar,* progBox,* menubackground,* oxygenBar,* oxygenBox,* inventoryBox;
    IGUIImage* inventoryselected,* inventory1,* inventory2,* inventory3,* inventory4,* inventory5,* inventory6,* inventory7;
    //animated mesh scenenodes
    IAnimatedMeshSceneNode* node,* node2;
    //scenenodes
    ISceneNode* collisionscenenode,* highlightedSceneNode;
    //animated meshes
    IAnimatedMesh* current_inventory_mesh,* crate_mesh;
    //billboard
    IBillboardSceneNode * bill;
    //guitext
    IGUIStaticText* fps,* clock,* progText;
    //collisionmanager and triangleselector
    ISceneCollisionManager* collMan;
    ITriangleSelector* selector,* selector1;

    SIrrlichtCreationParameters cfg_settings;
    vector3df intersection,pickupintersection;

    IMetaTriangleSelector* metaselector;
    ISceneNodeAnimatorCollisionResponse * anim1;
    ISceneNodeAnimator* anim;
    float oxygendecreasefactor;//value between -1 and one
    int buttonxlocend, buttonxlocstart, buttonylocspace;
    int xloc, yloc, zloc, lastFPS;
    bool doneloading;


    GUI gui;


};

#endif
