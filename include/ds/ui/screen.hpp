/**
 *    Copyright 2010-05-26 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/
#ifndef __DS_UI_SCREEN_HPP____by_Duzy_Chan__
#define __DS_UI_SCREEN_HPP____by_Duzy_Chan__ 1

namespace ds { namespace ui {

    class display;
    
    class screen
    {
      screen();
      ~screen();

      struct IMPL;

    public:
      display *get_display() const;

      int width() const;
      int height() const;

      unsigned black_pixel() const;
      unsigned white_pixel() const;

    private:
      IMPL * _p;
    };//class screen
    
  }//namespace ui
}//namespace ds

#endif//__DS_UI_SCREEN_HPP____by_Duzy_Chan__