/**
 *    Copyright 2010-08-06 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <ds/ui/display.hpp>
#include <ds/ui/screen.hpp>
#include <ds/ui/window.hpp>
#include <ds/ui/events.hpp>
#include <ds/event_queue.hpp>
#include <X11/Xlib.h>
#include "display_impl.h"
#include "screen_impl.h"
#include "window_impl.h"
#include <ds/debug.hpp>

namespace ds { namespace ui {

    void display::IMPL::push_event( event_queue *eq, XEvent * event )
    {
      /* filter events catchs XIM events and sends them to the correct
         handler */
      if ( XFilterEvent(event, None) == True ) {
        return;
      }

      window_map_t::iterator wit = _winmap.find( event->xany.window );
      if (wit == _winmap.end()) {
        if (event->type == PropertyNotify) {
          //char *name = XGetAtomName(_xdisp, event->xproperty.atom);
          //dsD("property: "<<name);
          return;
        }
        dsE("no window: "<<event->xany.window<<" for "<<event->type);
        return;
      }

      window::pointer win( wit->second );
      dsI( win );

      // TODO: push parsed-event into the event_queue

      switch (event->type) {
      case PropertyNotify:
        // Should be used for debug reasons.
        break;

      case MapNotify: {
        event::window::shown *evt1( new event::window::shown );
        event::window::restored *evt2( new event::window::restored );
        evt1->win = win.get();
        evt2->win = win.get();
        eq->push( evt1 );
        eq->push( evt2 );
      } break;

      case UnmapNotify: {
        event::window::hidden *evt1( new event::window::hidden );
        event::window::minimized *evt2( new event::window::minimized );
        evt1->win = win.get();
        evt2->win = win.get();
        eq->push( evt1 );
        eq->push( evt2 );
      } break;

      case Expose: {
        event::window::exposed *evt( new event::window::exposed );
        evt->win = win.get();
        evt->param1 = event->xexpose.x;
        evt->param2 = event->xexpose.y;
        evt->param3 = event->xexpose.width;
        evt->param4 = event->xexpose.height;
        eq->push( evt );
      } break;

      case ConfigureNotify: {
        event::window::moved *evt1( new event::window::moved );
        event::window::resized *evt2( new event::window::resized );
        evt1->win = win.get();
        evt1->param1 = event->xconfigure.x;
        evt1->param2 = event->xconfigure.y;
        evt2->win = win.get();
        evt2->param3 = event->xconfigure.width;
        evt2->param4 = event->xconfigure.height;
        eq->push( evt1 );
        eq->push( evt2 );
      } break;

      case KeyPress: {
        event::keyboard *evt( new event::keyboard );
        evt->window = win.get();
        evt->is_pressed = 1;
        evt->is_repeat = 0;
        evt->code = event->xkey.keycode; // TODO: layout[event->xkey.keycode]
        eq->push( evt );

        // TODO: convert key into text, send text_input
      } break;

      case KeyRelease: {
        event::keyboard *evt( new event::keyboard );
        evt->window = win.get();
        evt->is_pressed = 0;
        evt->is_repeat = 0;
        evt->code = event->xkey.keycode; // TODO: layout[event->xkey.keycode]
        eq->push( evt );
      } break;

      case KeymapNotify: { /* Generated upon EnterWindow and FocusIn */
        // TODO: ...
      } break;

      case MappingNotify: {
        // TODO: ...
      } break;

      case EnterNotify: {
        event::window::enter *evt( new event::window::enter );
        evt->win = win.get();
        evt->param1 = event->xcrossing.x;
        evt->param2 = event->xcrossing.y;
        eq->push( evt );
      } break;

      case LeaveNotify: {
        event::window::leave *evt( new event::window::leave );
        evt->win = win.get();
        evt->param1 = event->xcrossing.x;
        evt->param2 = event->xcrossing.y;
        eq->push( evt );
      } break;

      case FocusIn: {
        event::window::focus *evt( new event::window::focus );
        evt->win = win.get();
        evt->param1 = 1;
        eq->push( evt );
      } break;

      case FocusOut: {
        event::window::focus *evt( new event::window::focus );
        evt->win = win.get();
        evt->param1 = 0;
        eq->push( evt );
      } break;

      case MotionNotify: {
        // TODO: ...
      } break;

      case ButtonPress: {
        // TODO: ...
      } break;

      case ButtonRelease: {
        // TODO: ...
      } break;

      case SelectionRequest: {
        // TODO: ...
      } break;

      case SelectionNotify: {
        // TODO: ...
      } break;

      case ClientMessage:
        if (event->xclient.format == 32 &&
            event->xclient.data.l[0] == WM_DELETE_WINDOW) {
          /** Window closed */

          dsE("WM_DELETE_WINDOW");

          event::window::close * evt(new event::window::close);
          evt->win = win.get();
          eq->push( evt );
        }
        break;

      case CreateNotify: {
        // TODO: ...
      } break;

      case DestroyNotify: {
        // TODO: should notify the window of the destroy event
        win->_p->_xwin = NULL;
        win->_p->_disp = NULL;
        _winmap.erase( wit->first );
        if ( _winmap.empty() ) {
          eq->push(new ds::event::quit);
        }
      } break;

      default:
        eq->push(new ds::event::test);
        break;
      }
    }

  }//namespace ui
}//namespace ds