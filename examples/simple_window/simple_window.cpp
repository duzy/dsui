/**
 *    Copyright 2010-07-18 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
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
#include <ds/debug.hpp>
#include <cassert>

namespace cycle
{
  struct so_1;
  struct so_2;
  struct so_3;
  struct so_4;

  static int object_count_1 = 0;
  static int object_count_2 = 0;
  static int object_count_3 = 0;
  static int object_count_4 = 0;

  struct so_1 : ds::shared_object<so_1>
  {
    ds::shared_object<so_2>::pointer_t _2;

    so_1() { ++object_count_1; }
    ~so_1() { --object_count_1; }
  };

  struct so_2 : ds::shared_object<so_2>
  {
    ds::shared_object<so_1>::pointer_t _1;
    ds::shared_object<so_3>::pointer_t _3;

    so_2() { ++object_count_2; }
    ~so_2() { --object_count_2; }
  };

  struct so_3 : ds::shared_object<so_3>
  {
    ds::shared_object<so_1>::pointer_t _1;
    ds::shared_object<so_4>::pointer_t _4;

    so_3() { ++object_count_3; }
    ~so_3() { --object_count_3; }
  };

  struct so_4 : ds::shared_object<so_4>
  {
    ds::shared_object<so_1>::pointer_t _1;

    so_4() { ++object_count_4; }
    ~so_4() { --object_count_4; }
  };
}

struct so_test : ds::shared_object<so_test> {};

static void test_so_f( so_test::pointer_t p, int n )
{
  dsI( 0 < p->refcount() );
  dsI( p->refcount() == n + 1 );
}

static void test_shared_object()
{
  so_test *p( new so_test );
  dsI( p->refcount() == 0 );

  so_test::pointer_t sp( p );
  dsI( p->refcount() == 1 );
  dsI( p->refcount() == sp->refcount() );

  so_test::pointer_t sp2( p );
  dsI( p->refcount() == 2 );
  dsI( p->refcount() == sp2->refcount() );
  dsI( sp->refcount() == sp2->refcount() );

  {
    so_test::pointer_t sp3( p );
    dsI( p->refcount() == 3 );
  }
  dsI( p->refcount() == 2 );

  {
    so_test::pointer_t sp4( sp );
    dsI( p->refcount() == 3 );
  }
  dsI( p->refcount() == 2 );
  
  test_so_f( p, 2 );
  test_so_f( p, p->refcount() );

  /*
  so_test so;
  dsI( so.refcount() == 0 );
  {
    so_test::pointer_t p( &so );
    dsI( so.refcount() == 1 );
    dsI( p->refcount() == 1 );
  }
  */

  {
    cycle::so_1::pointer_t _1( new cycle::so_1 );
    cycle::so_2::pointer_t _2( new cycle::so_2 );
    cycle::so_3::pointer_t _3( new cycle::so_3 );
    cycle::so_4::pointer_t _4( new cycle::so_4 );
    
    /* Cycle Leak 1 */
    //_1->_2 = _2;
    //_2->_1 = _1;

    /* Cycle Leak 2 */
    //_1->_2 = _2;
    //_2->_3 = _3;
    //_3->_1 = _1;

    /* Cycle Leak 3 */
    _1->_2 = _2;
    _2->_3 = _3;
    _3->_4 = _4;
    //_4->_1 = _1;
  }
  dsI( cycle::object_count_1 == 0 );
  dsI( cycle::object_count_2 == 0 );
  dsI( cycle::object_count_3 == 0 );
  dsI( cycle::object_count_4 == 0 );
}

int main(int argc, char** argv)
{
  test_shared_object();

  // make a default display connection
  ds::ui::display::pointer_t disp = ds::ui::display::open();
  dsD("display-refs: "<<disp->refcount());

  ds::ui::screen::pointer_t scrn = disp->default_screen();
  dsD("screen-refs: "<<scrn->refcount());

  //ds::ui::window win1( disp ); // a window in the display 'disp'
  ds::ui::window::pointer_t win1( new ds::ui::window(disp) );
  assert( disp->has(win1) );

  win1->show();

  //ds::ui::window win2; // a window of no display is trivial
  ds::ui::window::pointer_t win2( new ds::ui::window );
  disp->map( win2 );
  assert( disp->has(win2) );

  win2->show(); // show it since it's belong to 'disp'

  dsD("display-refs: "<<disp->refcount());

  int n;
  {
    ds::ui::event_loop loop( disp );
    dsD("display-refs: "<<disp->refcount());
    n = loop.run();
  }

  dsD("display-refs: "<<disp->refcount());
  return n;
}
