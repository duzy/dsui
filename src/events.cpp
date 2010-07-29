#include <ds/event.hpp>
#include <ds/ui/events.hpp>
#include <ds/ui/display.hpp>
#include <ds/event_queue.hpp>
#include <ds/debug.hpp>

namespace ds { namespace ui {

    event_queue * get_event_queue()
    {
      static event_queue q;
      return &q;
    }

    event_loop::event_loop(const display::pointer_t & disp)
      : ds::event_loop( get_event_queue() )
      , _display( disp )
    {
    }

    event_loop::~event_loop()
    {
    }

    void event_loop::should_pump_events()
    {
      /**
       *  Pump events out of the display will actually push the events into
       *  the event queue, since at this point it's in the same thread as the
       *  event loop(see ds::event_loop::run), it must be safe to 'wait'
       *  messages.
       */
      _display->pump(); // Pump some events
    }

    void event_loop::on_event(const ds::event & evt)
    {
      // TODO: dispatch UI events
      // TODO: close _display on quit event
      dsD("event: "<<evt.type);
      ds::event_loop::on_event(evt);
    }
    
  }//namespace ui
}//namespace ds