// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GXWMM_KNOB_H
#define _GXWMM_KNOB_H


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


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GxKnob GxKnob;
typedef struct _GxKnobClass GxKnobClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gxw
{ class Knob_Class; } // namespace Gxw
namespace Gxw {


class Knob: public Gxw::Regler {
	public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Knob CppObjectType;
  typedef Knob_Class CppClassType;
  typedef GxKnob BaseObjectType;
  typedef GxKnobClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Knob();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Knob_Class;
  static CppClassType knob_class_;

  // noncopyable
  Knob(const Knob&);
  Knob& operator=(const Knob&);

protected:
  explicit Knob(const Glib::ConstructParams& construct_params);
  explicit Knob(GxKnob* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GxKnob*       gobj()       { return reinterpret_cast<GxKnob*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GxKnob* gobj() const { return reinterpret_cast<GxKnob*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

	public:
	#ifdef GLIBMM_PROPERTIES_ENABLED
/** The id of the linked variable.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_var_id() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The id of the linked variable.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_var_id() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

	static void set_jump_to_mouse(bool value);
	static bool get_jump_to_mouse();
	protected:
	Knob();


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
   * @relates Gxw::Knob
   */
  Gxw::Knob* wrap(GxKnob* object, bool take_copy = false);
} //namespace Glib


#endif /* _GXWMM_KNOB_H */

