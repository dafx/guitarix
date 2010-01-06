/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 * --------------------------------------------------------------------------
 *
 *
 *	This are the cairo callbacks to draw the guitarix UI
 *
 *
 * --------------------------------------------------------------------------
 */



    // set cairo color related to the used skin
    void gx_skin_color(cairo_pattern_t *pat)
    {
      int skin_is = int(float(gx_current_skin));

      switch (skin_is)
        {
        case 0:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
          break;
        case 1:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
          break;
        case 2:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.3, 0.2, 0.3, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
          break;
        case 3:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.5, 0.02, 0.03, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.1, 0.6);
          break;
        case 4:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.5, 0.2, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.1, 0.05, 0.6);
          break;
        case 5:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.8, 0.2, 0.02, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.09, 0.005, 0.6);
          break;
        case 6:
          cairo_pattern_add_color_stop_rgba (pat, 0, 0.8, 0.3, 0.02, 0.6);
          cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.06, 0.005, 0.6);
          break;
        }

    }

    //----- paint boxes with cairo -----
    gboolean box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+2;
      double y0      = wi->allocation.y+2;
      double rect_width  = wi->allocation.width-4;
      double rect_height = wi->allocation.height-4;
      double radius = 25.;

      double x1,y1;

      x1=x0+rect_width;
      y1=y0+rect_height;

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
      cairo_close_path (cr);

      cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
      cairo_set_line_width (cr, 5.0);
      cairo_stroke (cr);

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
      cairo_close_path (cr);

      cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
      cairo_set_line_width (cr, 1.0);
      cairo_stroke (cr);

      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box1_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;
      cairo_pattern_t *pat;

      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+5;
      double y0      = wi->allocation.y+5;
      double rect_width  = wi->allocation.width-10;
      double rect_height = wi->allocation.height-10;
      double radius = 36.;
      double x1,y1;
      x1=x0+rect_width;
      y1=y0+rect_height;

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);

      cairo_close_path (cr);

      pat = cairo_pattern_create_linear (0, y0, 0, y1);

      cairo_pattern_add_color_stop_rgba (pat, 1, 0., 0., 0., 0.8);
      cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0.4);
      cairo_set_source (cr, pat);
      cairo_fill_preserve (cr);

      cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
      cairo_set_line_width (cr, 9.0);
      cairo_stroke (cr);

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
      cairo_close_path (cr);

      cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
      cairo_set_line_width (cr, 1.0);
      cairo_stroke (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box2_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;
      cairo_pattern_t *pat;

      gint x, y;
      gint w, h;

      /* get the dimensions */
      x = wi->allocation.x+2;
      y = wi->allocation.y+2;
      w = wi->allocation.width-4;
      h = wi->allocation.height-4;

      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      cairo_move_to (cr, x, y);
      cairo_curve_to (cr, x+w*0.66, y, x+w*0.33, y+h, x+w, y+h);
      cairo_line_to (cr, x+w , y);
      cairo_set_line_width (cr, 3.0);
      cairo_close_path (cr);

      pat = cairo_pattern_create_linear (0, y, 0, y+h);
      cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
      cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0);
      cairo_set_source (cr, pat);
      cairo_fill_preserve (cr);
      cairo_stroke (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;

    }

    gboolean box3_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-11;

      cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
      cairo_set_source_rgb (cr, 0, 0, 0);
      cairo_fill (cr);

      cairo_pattern_t*pat =
        cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
      cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
      cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);
      gx_skin_color(pat);
      cairo_set_source (cr, pat);
      cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
      cairo_fill (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box4_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;
      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-2;

      cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
      cairo_set_source_rgb (cr, 0, 0, 0);
      cairo_fill (cr);

      cairo_pattern_t*pat =
        cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
      gx_skin_color(pat);
      cairo_set_source (cr, pat);
      cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
      cairo_fill (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box5_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;


      /* create a cairo black arc to given widget */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-2;

      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
      cairo_set_source_rgb (cr, 0, 0, 0);
      cairo_fill (cr);

      cairo_pattern_t*pat =
        cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
      gx_skin_color(pat);
      cairo_set_source (cr, pat);
      cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
      cairo_fill (cr);

      cairo_move_to (cr, x0+10, y0 + (rect_height*0.5));
      cairo_curve_to (cr, x0+30,y0 + (rect_height*0.005), x0+50, y0 + (rect_height*0.995), x0+70, y0 + (rect_height*0.5));
      cairo_set_source_rgb (cr, 1, 1, 1);
      cairo_set_line_width (cr, 1.0);
      cairo_stroke (cr);
      cairo_move_to (cr, x0+10, y0 + (rect_height*0.5));
      cairo_line_to (cr, x0+75 , y0 + (rect_height*0.5));
      cairo_move_to (cr, x0+10, y0 + (rect_height*0.2));
      cairo_line_to (cr, x0+10 , y0 + (rect_height*0.8));
      cairo_set_source_rgb (cr, 0.2, 0.8, 0.2);
      cairo_set_line_width (cr, 1.0);
      cairo_stroke (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box6_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-11;

      cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
      cairo_pattern_t*pat =
        cairo_pattern_create_radial (200, rect_height*0.5, 5,200,  rect_height*0.5, 200.0);
      cairo_pattern_add_color_stop_rgb (pat, 0, 0.8, 0.8, 0.8);
      cairo_pattern_add_color_stop_rgb (pat, 1, 0.3, 0.3, 0.3);
      cairo_set_source (cr, pat);
      cairo_fill (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box7_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;

      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);
      cairo_set_font_size (cr, 7.0);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+2;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-4;

      int  db_points[] = { -50, -40, -20, -30, -10, -3, 0, 4 };
      char  buf[32];

      cairo_rectangle (cr, x0,y0,rect_width,rect_height+2);
      cairo_set_source_rgb (cr, 0, 0, 0);
      cairo_fill (cr);

      cairo_pattern_t*pat =
        cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
      cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
      cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);
      cairo_set_source (cr, pat);
      cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
      cairo_fill (cr);

      for (uint32_t i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
        {
          float fraction = log_meter (db_points[i]);
          cairo_set_source_rgb (cr, 0.12*i, 1, 0.1);

          cairo_move_to (cr, x0+rect_width*0.2,y0+rect_height - (rect_height * fraction));
          cairo_line_to (cr, x0+rect_width*0.8 ,y0+rect_height -  (rect_height * fraction));
          if (i<6)
            {
              snprintf (buf, sizeof (buf), "%d", db_points[i]);
              cairo_move_to (cr, x0+rect_width*0.32,y0+rect_height - (rect_height * fraction));
            }
          else
            {
              snprintf (buf, sizeof (buf), " %d", db_points[i]);
              cairo_move_to (cr, x0+rect_width*0.34,y0+rect_height - (rect_height * fraction));
            }
          cairo_show_text (cr, buf);
        }

      cairo_set_source_rgb (cr, 0.4, 0.8, 0.4);
      cairo_set_line_width (cr, 0.5);
      cairo_stroke (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box8_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-10;

      cairo_move_to (cr, x0, y0+rect_height*0.6);
      cairo_curve_to (cr, x0+rect_width, y0+rect_height*0.7, x0+rect_width, y0+rect_height*0.7, x0+rect_width, y0+rect_height);
      cairo_line_to (cr, x0 , y0+rect_height);
      cairo_set_line_width (cr, 1.0);
      cairo_close_path (cr);
      cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
      cairo_fill_preserve (cr);
      cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
      cairo_stroke (cr);

      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box9_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-10;

      cairo_move_to (cr, x0+rect_width, y0+rect_height*0.6);
      cairo_curve_to (cr, x0, y0+rect_height*0.7, x0, y0+rect_height*0.7, x0, y0+rect_height);
      cairo_line_to (cr, x0+rect_width , y0+rect_height);
      cairo_set_line_width (cr, 1.0);
      cairo_close_path (cr);
      cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
      cairo_fill_preserve (cr);
      cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
      cairo_stroke (cr);

      cairo_destroy(cr);

      return FALSE;
    }

    gboolean box10_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {
      if (int(float(gx_current_skin)==1))
        {
          cairo_t *cr;

          /* create a cairo context */
          cr = gdk_cairo_create(wi->window);

          double x0      = wi->allocation.x+1;
          double y0      = wi->allocation.y+1;
          double rect_width  = wi->allocation.width-2;
          double rect_height = wi->allocation.height-3;

          cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
          cairo_set_source_rgb (cr, 0, 0, 0);
          cairo_fill (cr);

          cairo_pattern_t*pat =
            cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
          cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
          cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);

          cairo_set_source (cr, pat);
          cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
          cairo_fill (cr);

          cairo_pattern_destroy (pat);
          cairo_destroy(cr);
        }
       /* else if (int(float(gx_current_skin)==0))
                 box11_expose(wi,ev,user_data); */

      return FALSE;
    }

    gboolean box11_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {

      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-3;

      _image = gdk_pixbuf_scale_simple(gx_gui::tribeimage,rect_width,rect_height,GDK_INTERP_HYPER);

      cairo_pattern_t*pat;

      gdk_draw_pixbuf(GDK_DRAWABLE(wi->window), gdk_gc_new(GDK_DRAWABLE(wi->window)),
                      _image, 0, 0,
                      x0, y0, rect_width,rect_height,
                      GDK_RGB_DITHER_NORMAL, 0, 0);

      double radius = 38.;
      if (rect_width<38) radius = rect_width;
      else if (rect_height<38) radius = rect_height;
      double x1,y1;

      x1=x0+rect_width;
      y1=y0+rect_height;

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
      cairo_close_path (cr);
      pat = cairo_pattern_create_linear (0, y0, 0, y1);
      cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
      cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.05, 0.05, 0.6);
      cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.2, 0.4);
      cairo_set_source (cr, pat);
      cairo_fill (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);
      g_object_unref(_image);

      return FALSE;
    }

    gboolean box12_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
    {

      cairo_t *cr;


      /* create a cairo context */
      cr = gdk_cairo_create(wi->window);

      double x0      = wi->allocation.x+1;
      double y0      = wi->allocation.y+1;
      double rect_width  = wi->allocation.width-2;
      double rect_height = wi->allocation.height-3;


      cairo_pattern_t*pat;

      double radius = 38.;
      if (rect_width<38) radius = rect_width;
      else if (rect_height<38) radius = rect_height;
      double x1,y1;

      x1=x0+rect_width;
      y1=y0+rect_height;

      cairo_move_to  (cr, x0, y0 + radius);
      cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
      cairo_line_to (cr, x1 - radius, y0);
      cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
      cairo_line_to (cr, x1 , y1 - radius);
      cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
      cairo_line_to (cr, x0 + radius, y1);
      cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
      cairo_close_path (cr);
      pat = cairo_pattern_create_linear (0, y0, 0, y1);
      cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
      cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.05, 0.05, 0.6);
      cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.2, 0.4);
      cairo_set_source (cr, pat);
      cairo_fill (cr);

      cairo_pattern_destroy (pat);
      cairo_destroy(cr);

      return FALSE;
    }

    void gx_init_pixmaps()
    {
      /* XPM */
      static const char * tribe_xpm[] =
      {
        "65 20 3 1",
        " 	c None",
        ".	c #656565",
        "+	c #646464",
        "                                                                 ",
        "                                                                 ",
        "                                                                 ",
        "                                                                 ",
        "                          .           +                          ",
        "                    ..  ++.+++     .   ...++                     ",
        "                    . ++.    +     + +  +.+                      ",
        "   +                 ++  .+ .+     +. +.  ..+                ++  ",
        "  +..    .+        . ++  .+. +       +..  +. .         +    ++.+ ",
        " +   +    .         .   +  .+       +.      +  .      .+   ..  + ",
        " +       +.   .   .  .  +  +.++    .++. +.    +   +.   +    .  + ",
        " ++   .. . +++++.   +  ++.... .   + .++.+   .   ....... ++.   +. ",
        "   + ++ +..+++.++. +      ..          +       . + +.++.++  .+.   ",
        "   .  .+                                                     .   ",
        "   +..                                                      ++   ",
        "   +.                                                        .   ",
        "                                                                 ",
        "                                                                 ",
        "                                                                 ",
        "                                                                 "
      };

      tribeimage = gdk_pixbuf_new_from_xpm_data(tribe_xpm);
    }
