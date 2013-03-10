#include <stdio.h>
#include <string>
#include "game.h"
#include <cstdlib>
#include <iostream>
#include <wchar.h>
using namespace std;
using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

static wchar_t* charToWChar(const char* text)
{
    size_t size = strlen(text) + 1;
    wchar_t* wa = new wchar_t[size];
    mbstowcs(wa,text,size);
    return wa;
}

bool Game::SaveSettings()
    {



		//create xml writer
		IXMLWriter* xwriter = device->getFileSystem()->createXMLWriter( "config.xml" );

		if (!xwriter)
			return false;

		//write out the obligatory xml header. Each xml-file needs to have exactly one of those.
		xwriter->writeXMLHeader();

		//start element	mygame, you replace the label "mygame" with anything you want
		xwriter->writeElement(L"settings");
		xwriter->writeLineBreak();					//new line

		//start section with video settings
		xwriter->writeElement(L"video");
		xwriter->writeLineBreak();					//new line
/*
stringw posx=temp.X;
xml->writeText(posx.c_str());
stringw xvalue= gui.XresField->getValue();*/


        xwriter->writeElement(L"resolution",true,
                              L"x",stringw((int)gui.XresField->getValue()).c_str(),
                              L"y",stringw((int)gui.YresField->getValue()).c_str());
        xwriter->writeLineBreak();
        xwriter->writeElement(L"fullscreen",true, L"value",
                              stringw((int)gui.FullscreenCheckbox->isChecked()).c_str());
		xwriter->writeLineBreak();
        xwriter->writeElement(L"antialias",true, L"value",
                              stringw((int)gui.AntiAliasCheckbox->isChecked()).c_str());
		xwriter->writeLineBreak();

/*.<?xml version="1.0"?>.
<mygame>..
	<video>
		<setting name="driver" value="OpenGL"/>...
		<setting name="fullscreen" value="0" />
		<setting name="resolution" value="640x480" />..
 	</video>.
</mygame>
*/


		//close video section
		xwriter->writeClosingTag(L"video");
		xwriter->writeLineBreak();

		//..
		// You can add writing sound settings, savegame information etc
		//..

		//close mygame section
		xwriter->writeClosingTag(L"mygame");

		//delete xml writer
		xwriter->drop();

		return true;
    }
bool Game::LoadSettings()
    {
        printf("\nLoading settings...\n");
    IrrlichtDevice *devicenull =  createDevice(EDT_NULL);
    if (!devicenull){printf("\nCould not create nulldevice for xml-reading\n");return false;}

    IXMLReader* xml = devicenull->getFileSystem()->createXMLReader("config.xml");
    if (!xml){printf("\nLoading settings failed :( \n");}

    //int driverint= xml->getAttributeValueAsInt(L"driver");
cfg_settings.DriverType = video::EDT_OPENGL;

    while(xml && xml->read())
   {
      if (core::stringw("resolution") == xml->getNodeName())
      {
          cfg_settings.WindowSize = core::dimension2d<u32>(xml->getAttributeValueAsInt(L"x"),xml->getAttributeValueAsInt(L"y"));
      }
       if (core::stringw("fullscreen") == xml->getNodeName())
      {
          cfg_settings.Fullscreen = xml->getAttributeValueAsInt(L"value");
      }
      if (core::stringw("antialias") == xml->getNodeName())
      {
          cfg_settings.AntiAlias = xml->getAttributeValueAsInt(L"value");
      }
          cfg_settings.Vsync =false;
   }

    //settings have been loaded, now drop the parser+nulldevice
    devicenull->drop();
    xml->drop();
    }
