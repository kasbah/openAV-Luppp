
#ifndef LUPPP_G_TRACK_H
#define LUPPP_G_TRACK_H

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Native_File_Chooser.H>

#include "avtk/avtk_dial.h"
#include "avtk/avtk_volume.h"
#include "avtk/avtk_button.h"
#include "avtk/avtk_background.h"
#include "avtk/avtk_clip_selector.h"


#include "config.hxx"
#include "worker.hxx"
#include "audiobuffer.hxx"
#include "eventhandler.hxx"

using namespace std;

static string choose_file()
{
  string path;
  Fl_Native_File_Chooser fnfc;
  fnfc.title("Pick a file");
  fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
  //fnfc.filter("Wav\t*.wav");
  fnfc.directory( getenv("HOME") ); // default directory to use
  // Show native chooser
  switch ( fnfc.show() ) {
   case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
   case  1: printf("CANCEL\n");                      break;  // CANCEL
   default: printf("Loading directory: %s\n", fnfc.filename());    
    
    // update path and load it
    path = fnfc.filename();
    
    break;  // FILE CHOSEN
  }
  return path;
}

extern void gtrack_button_callback(Fl_Widget *w, void *data);

class GTrack : public Fl_Group
{
  public:
    GTrack(int x, int y, int w, int h, const char* l = 0 ) :
      Fl_Group(x, y, w, h),
      title( strdup(l) ),
      bg( x, y , w, h, title ),
      
      clipSel(x + 5, y + 26 + 26, 100, 294,""),
      
      button1(x + 5, y + 324 + 26, 100, 18,"Rec"),
      button2(x + 5, y + 344 + 26, 100, 18,"Play"),
      button3(x + 5, y + 364 + 26, 100, 18,"Stop"),
      button4(x + 5, y + 384 + 26,  48, 18,"-"),
      button5(x +57, y + 384 + 26,  48, 18,"+"),
      
      button6(x + 5, y + 404 + 26, 100, 18,"Load"),
      
      volume(x+68, y +495 + 26, 36, 150, "Vol"),
      
      dial1(x+15, y +452 + 26, 24, 24, "REV"),
      dial2(x+45, y +452 + 26, 24, 24, "SC"),
      dial3(x+75, y +452 + 26, 24, 24, "POST"),
      
      progress(x+5, y+428 + 26, 100, 18, "")
    {
      ID = privateID++;
      
      button1.callback( gtrack_button_callback, &ID );
      button2.callback( gtrack_button_callback, &ID );
      button3.callback( gtrack_button_callback, &ID );
      button4.callback( gtrack_button_callback, &ID );
      button5.callback( gtrack_button_callback, &ID );
      button6.callback( gtrack_button_callback, &ID );
      
      volume.callback( gtrack_button_callback, 0 );
      
      volume.amplitude( 0.75, 0.5 );
      
      progress.maximum(1.0f);
      progress.minimum(0.0f);
      progress.color( FL_BLACK );
      progress.selection_color( FL_BLUE );
      
      end(); // close the group
    }
    
    ~GTrack()
    {
      free(title);
    }
    
    int ID;
    
    char* title;
    
    Avtk::Background bg;
    
    Avtk::ClipSelector clipSel;
    
    Avtk::Button button1;
    Avtk::Button button2;
    Avtk::Button button3;
    Avtk::Button button4;
    Avtk::Button button5;
    Avtk::Button button6;
    
    
    Avtk::Volume volume;
    
    Avtk::Dial   dial1;
    Avtk::Dial   dial2;
    Avtk::Dial   dial3;
    
    Fl_Progress  progress;
    
    static int privateID;
};

#endif // LUPPP_G_TRACK_H

