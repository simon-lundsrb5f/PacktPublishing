/*
 * main.c
 *
 *  Created on: 2019年4月5日
 *      Author: tom
 */
#include <gtk/gtk.h>
#include "MyLogoResource.h"
#include "MyLogo.h"


void my_custom_draw(MyLogo *self,cairo_t *cr) {
	cairo_save(cr);
	cairo_set_source_rgba(cr,1,0,0,0.5);
	cairo_arc(cr,100,100,30,0,2*G_PI);
	cairo_set_line_width(cr,5.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,1,0.5,0,0.5);
	cairo_arc(cr,512-60-30,100,60,0,2*G_PI);
	cairo_set_line_width(cr,10.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0,1.,0.5,0.5);
	cairo_arc(cr,300,180,80,0,2*G_PI);
	cairo_set_line_width(cr,30.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0.25,0.8,0.5,0.5);
	cairo_arc(cr,412-50,412-50,100,0,2*G_PI);
	cairo_set_line_width(cr,30.);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr,0.5,0,0.8,0.5);
	cairo_arc(cr,150,512-120-20,120,0,2*G_PI);
	cairo_set_line_width(cr,20.);
	cairo_stroke(cr);

	cairo_restore(cr);

}

cairo_status_t cairo_read_png_from_gresource (GInputStream *in,
					     unsigned char	*data,
					     unsigned int	length){
	gsize read=g_input_stream_read(in,data,length,NULL,NULL);
	if(read==0) {
		g_input_stream_close(in,NULL,NULL);
		g_object_unref(in);
	}
	return CAIRO_STATUS_SUCCESS;
};

void load_png(MyLogo *self,cairo_t *cr) {
	cairo_save(cr);
	GFile *file=g_file_new_for_uri("resource:///org/gtk/gimp.png");
	GInputStream *in=g_file_read(file,NULL,NULL);
	g_object_unref(file);
	cairo_surface_t *surf=cairo_image_surface_create_from_png_stream(cairo_read_png_from_gresource,in);
	//cairo_surface_t *surf=cairo_image_surface_create_from_png("gimp.png");
	cairo_set_source_surface(cr,surf,0,0);
	cairo_paint(cr);
	cairo_surface_destroy(surf);
	cairo_restore(cr);
}



int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	/*Create the Main Window*/
	GtkWindow *mwin=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(mwin,512,512);
	/*Disable the decorate to make it have a good look.*/
	gtk_window_set_decorated(mwin,FALSE);

	/*Create the logo widget and add it to the Main Window
	 * It need the root_window to apply additional setting.
	 * and the last parameter 'TRUE' to make it can be move by the it's content.*/
	MyLogo *logo = my_logo_new(mwin,TRUE);
	gtk_container_add(mwin,logo);

	/*Create a button to exit*/
	GtkButton *button = gtk_button_new_with_label("Close");

	/*Add the button to the logo widget;
	 *And set the position and size in the logo widget.
	 *With the last parameter 'TRUE' to make it's size and position is relate to the parent size allocation(it will change while the allocation was modify)*/
	my_logo_pack(logo,button,40/*40% parent allocation distance to the left*/,100-40*100/512,20/*20% width to the parent allocation*/,40*100/512,TRUE);

	g_signal_connect(logo,"logo_draw",my_custom_draw,NULL);
	g_signal_connect(logo,"logo_draw",load_png,NULL);
	g_signal_connect(button,"clicked",gtk_main_quit,NULL);


	gtk_widget_show_all(mwin);
	gtk_main();
	return 0;
}
