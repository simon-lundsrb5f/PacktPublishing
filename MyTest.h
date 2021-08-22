/*
 * MyTest.h
 *
 *  Created on: 2019年4月7日
 *      Author: tom
 */

#ifndef MYTEST_H_
#define MYTEST_H_
#include <glib-object.h>
#include <gtk/gtk.h>
G_BEGIN_DECLS
#define MY_TYPE_TEST my_test_get_type()
G_DECLARE_DERIVABLE_TYPE(MyTest,my_test,MY,TEST,GtkWindow);
typedef struct _MyTestClass{
	GtkWindowClass Parent_class;
};
G_END_DECLS


#endif /* MYTEST_H_ */
