// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GXWMM_SELECTOR_H
#define _GXWMM_SELECTOR_H


#include <glibmm.h>

/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gxwmm/regler.h>
#include <gtkmm/treemodel.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GxSelector GxSelector;
typedef struct _GxSelectorClass GxSelectorClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gxw
{ class Selector_Class; } // namespace Gxw
namespace Gxw {


class Selector: public Gxw::Regler {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Selector CppObjectType;
  typedef Selector_Class CppClassType;
  typedef GxSelector BaseObjectType;
  typedef GxSelectorClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Selector();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Selector_Class;
  static CppClassType selector_class_;

  // noncopyable
  Selector(const Selector&);
  Selector& operator=(const Selector&);

protected:
  explicit Selector(const Glib::ConstructParams& construct_params);
  explicit Selector(GxSelector* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GxSelector*       gobj()       { return reinterpret_cast<GxSelector*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GxSelector* gobj() const { return reinterpret_cast<GxSelector*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

	public:
	Selector();
	
  void set_model(Glib::RefPtr<Gtk::TreeModel>);;
	
  Glib::RefPtr<Gtk::TreeModel> get_model();;
	#ifdef GLIBMM_PROPERTIES_ENABLED
/** The model for the selector.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Gtk::TreeModel> property_model() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The model for the selector.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Gtk::TreeModel> property_model() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


};

} // namespace Gxw


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gxw::Selector
   */
  Gxw::Selector* wrap(GxSelector* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_SELECTOR_H */

