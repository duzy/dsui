/**
 *    Copyright 2009-03-22 DuzySoft.com, by Zhan Xin-Ming��ղ������
 *    All rights reserved by Zhan Xin-Ming��ղ������
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id: image.hpp 614 2009-05-12 03:23:30Z duzy $
 *
 **/

#ifndef __DS_GRAPHICS_DETAIL_IMAGE_HPP____by_Duzy_Chan__
#define __DS_GRAPHICS_DETAIL_IMAGE_HPP____by_Duzy_Chan__ 1
#       include <boost/mpl/vector.hpp>
//#       include <boost/gil/image.hpp>
#       include <boost/gil/typedefs.hpp>
#       include <boost/gil/extension/dynamic_image/any_image.hpp>
//#       include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#       include <boost/gil/extension/dynamic_image/apply_operation.hpp>

namespace ds { namespace graphics {
    namespace detail
    {

      struct image
      {
        typedef boost::gil::gray8_image_t         gray8_image_t;
        typedef boost::gil::gray16_image_t        gray16_image_t;
        typedef boost::gil::rgb8_image_t          rgb8_image_t;
        typedef boost::gil::rgb16_image_t         rgb16_image_t;
        typedef boost::gil::rgba8_image_t         rgba8_image_t;
        typedef boost::gil::rgba16_image_t        rgba16_image_t;
        typedef boost::gil::bgr8_image_t          bgr8_image_t;
        typedef boost::gil::bgr16_image_t         bgr16_image_t;
        typedef boost::gil::bgra8_image_t         bgra8_image_t;
        typedef boost::gil::bgra16_image_t        bgra16_image_t;
        typedef boost::gil::argb8_image_t         argb8_image_t;
        typedef boost::gil::argb16_image_t        argb16_image_t;
        typedef boost::gil::abgr8_image_t         abgr8_image_t;
        typedef boost::gil::abgr16_image_t        abgr16_image_t;
        typedef boost::gil::cmyk8_image_t         cmyk8_image_t;
        typedef boost::gil::cmyk16_image_t        cmyk16_image_t;
        typedef boost::mpl::vector<
          gray8_image_t,        gray16_image_t,
          rgb8_image_t,         rgb16_image_t,
          rgba8_image_t,        rgba16_image_t,
          bgr8_image_t,         bgr16_image_t,
          bgra8_image_t,        bgra16_image_t,
          argb8_image_t,        argb16_image_t,
          abgr8_image_t,        abgr16_image_t,
          cmyk8_image_t,        cmyk16_image_t
          > supported_images;
        typedef boost::gil::any_image<supported_images> any_t;

        image();

        bool load_jpeg( const std::string & file );
        bool load_png( const std::string & file );
        bool load_tiff( const std::string & file );

        any_t::const_view_t any_view() const { return boost::gil::const_view( _anyImage ); }

        int width() const { return _anyImage.width(); }
        int height() const { return _anyImage.height(); }

      private:
        any_t _anyImage;
      };//struct image

    }//namespace detail
  }//namespace graphics
}//namespace ds

#endif//__DS_GRAPHICS_DETAIL_IMAGE_HPP____by_Duzy_Chan__
