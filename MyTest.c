/*
 * MyTest.c
 *
 *  Created on: 2019年4月7日
 *      Author: tom
 */


#include "MyTest.h"
typedef struct{
	GHashTable *child_table;
	GtkButton *button;
}MyTestPrivate;
G_DEFINE_TYPE_WITH_PRIVATE(MyTest,my_test,GTK_TYPE_WINDOW);

gboolean my_test_draw(MyTest *self,cairo_t *cr){
	GtkStyleContext *context=	gtk_widget_get_style_context(self);
	MyTestPrivate *priv=my_test_get_instance_private(self);

	gtk_render_background(context,cr,0,0,200,200);
	cairo_arc(cr,10,10,20,0,2*G_PI);
	cairo_set_source_rgba(cr,1.,0,0,1.);
	cairo_fill(cr);
	//GTK_WIDGET_CLASS(my_test_parent_class)->draw(priv->button,cr);
	//gtk_widget_draw(priv->button,cr);
	gtk_container_propagate_draw(self,priv->button,cr);
	g_print("draw\n");
	return TRUE;
}

static void my_test_class_init(MyTestClass *klass){
g_print("Class init\n");
}

static void my_test_init(MyTest *self){
	GtkAllocation alloc;
MyTestPrivate *priv=my_test_get_instance_private(self);
priv->button=gtk_button_new_with_label("Good Morning");
gtk_widget_set_parent_window(priv->button,self);
gtk_widget_set_parent(priv->button,self);
gtk_widget_show_all(priv->button);
alloc.width=200;
alloc.height=80;
alloc.x=20;
alloc.y=20;
gtk_widget_size_allocate(priv->button,&alloc);
g_signal_connect(self,"draw",my_test_draw,NULL);
}
