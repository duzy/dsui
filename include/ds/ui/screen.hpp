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
#       include <ds/shared_object.hpp>
#       include "../visibility.h"

namespace ds { namespace ui {

    class display;
    class window;
    
    class DS_UI_PUBLIC screen : public shared_object<screen>
    {
      screen();
      ~screen();

      struct IMPL;
      friend class display;
      friend class window;

    public:
      shared_object<display>::pointer get_display() const;

      shared_object<window>::pointer root() const;

      int number() const;

      int width() const;
      int height() const;

      unsigned black_pixel() const;
      unsigned white_pixel() const;

      int depth() const;

    private:
      IMPL * _p;
    };//class screen
    
  }//namespace ui
}//namespace ds

#endif//__DS_UI_SCREEN_HPP____by_Duzy_Chan__
