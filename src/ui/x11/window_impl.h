/**
 *    Copyright 2010-07-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <ext/slist>
#include <cstring>

namespace ds { namespace ui {
    
    struct window::IMPL
    {
      display * _disp; // Never hold a display::pointer_t(will leak)!

      Window _xwin; // Window and Pixmap are Drawable

      XVisualInfo _visual;
      XImage _image; 
      Drawable _drawable; // Pixmap, Window, etc...
      GC _gc;

      __gnu_cxx::slist<ds::graphics::rect> _dirtyRects;

      IMPL( display * d )
        : _disp( d )
        , _xwin( NULL )
        , _visual()
        , _image()
        , _drawable( NULL )
        , _gc( NULL )
        , _dirtyRects()
      {
        std::memset( &_visual, 0, sizeof(_visual) );
        std::memset( &_image, 0, sizeof(_image) );
      }

      void get_visual( const screen::pointer & scrn );

      void create( const window::pointer & );
      void destroy();
    };//struct window::IMPL
    
  }//namespace ui
}//namespace ds
