/*#ifndef GUI_H_INCLUDED
#def GUI_H_INCLUDED

struct GUI
{
	GUI ()
	{
		memset ( this, 0, sizeof ( *this ) );
	}

	void drop()
	{
		dropElement ( Window );
		dropElement ( Logo );
	}

	IGUIComboBox* VideoDriver;
	IGUIComboBox* VideoMode;
	IGUICheckBox* FullScreen;
	IGUICheckBox* Bit32;
	IGUIScrollBar* MultiSample;
	IGUIButton* SetVideoMode;

	IGUIScrollBar* Tesselation;
	IGUIScrollBar* Gamma;
	IGUICheckBox* Collision;
	IGUICheckBox* Visible_Map;
	IGUICheckBox* Visible_Shader;
	IGUICheckBox* Visible_Fog;
	IGUICheckBox* Visible_Unresolved;
	IGUICheckBox* Visible_Skydome;
	IGUIButton* Respawn;

	IGUITable* ArchiveList;
	IGUIButton* ArchiveAdd;
	IGUIButton* ArchiveRemove;
	IGUIFileOpenDialog* ArchiveFileOpen;
	IGUIButton* ArchiveUp;
	IGUIButton* ArchiveDown;

	IGUIListBox* MapList;
	IGUITreeView* SceneTree;
	IGUIStaticText* StatusLine;
	IGUIImage* Logo;
	IGUIWindow* Window;
};



class CQuake3EventHandler : public IEventReceiver
{
public:

	CQuake3EventHandler( GameData *gameData );
	virtual ~CQuake3EventHandler ();

	void Animate();
	void Render();

	void AddArchive ( const path& archiveName );
	void LoadMap ( const stringw& mapName, s32 collision );
	void CreatePlayers();
	void AddSky( u32 dome, const c8 *texture );
	Q3Player *GetPlayer ( u32 index ) { return &Player[index]; }

	void CreateGUI();
	void SetGUIActive( s32 command);

	bool OnEvent(const SEvent& eve);


private:

	GameData *Game;

	IQ3LevelMesh* Mesh;
	ISceneNode* MapParent;
	ISceneNode* ShaderParent;
	ISceneNode* ItemParent;
	ISceneNode* UnresolvedParent;
	ISceneNode* BulletParent;
	ISceneNode* FogParent;
	ISceneNode * SkyNode;
	IMetaTriangleSelector *Meta;

	c8 buf[256];

	Q3Player Player[2];

	struct SParticleImpact
	{
		u32 when;
		vector3df pos;
		vector3df outVector;
	};
	array<SParticleImpact> Impacts;
	void useItem( Q3Player * player);
	void createParticleImpacts( u32 now );

	void createTextures ();
	void addSceneTreeItem( ISceneNode * parent, IGUITreeViewNode* nodeParent);

	GUI gui;
	void dropMap ();
};
















#endif //GUI_H_INCLUDED
*/
