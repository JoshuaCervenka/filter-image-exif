#include </usr/include/glib-2.0/glib.h>
#include </usr/include/gdk-pixbuf-2.0/gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
//#include <iostream>
using namespace std;

GtkWidget *file_button;
GtkWidget *receive_button;
GtkWidget *fixed;
GtkWidget *window;
GtkWidget *image;
GtkWidget *scroll_window;
GtkWidget *jpeg_box;
GtkWidget *button_hbox;
GtkWidget *txt_view;
GtkTextBuffer *buffer;
GtkTextIter iter;

void on_destroy (GtkWidget *widget G_GNUC_UNUSED, gpointer user_data G_GNUC_UNUSED)
{
    gtk_main_quit();
}

/*void load_JPEG (GtkWidget *file_button)
{
    FILE *f;
    GtkWidget *file_dialog;
    GtkWidget *toplevel;
    char *filename;
    char line[256];
    char str[100];
    //guint8 buffer[500000];
    //gsize length;
    GdkPixbufLoader *loader;
    //GdkPixbuf *pixbuf;
    GtkFileFilter *filter = gtk_file_filter_new ();
    GtkWindow *parent_window;

    //image = gtk_image_new ();

    ***** Opens File chooser dialog *****
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    file_dialog = gtk_file_chooser_dialog_new ("Select JPEG Image",
                                                parent_window,
                                                action,
                                                GTK_STOCK_CANCEL,
                                                GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_OPEN,
                                                GTK_RESPONSE_ACCEPT,
                                                NULL);
    gtk_file_filter_add_pixbuf_formats(filter);
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (file_dialog), filter);
    if (gtk_dialog_run (GTK_DIALOG (file_dialog)) == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_dialog));
        gtk_image_set_from_file(GTK_IMAGE(image), filename);
        
        ***Load EXIF data that is linked to the file chosen***
        strcpy (str, "exiftool ");
        strcat (str, filename);
        f = popen(str, "r");
        while ( fgets( line, sizeof line, f))
        {
            gtk_text_buffer_get_end_iter (buffer, &iter);
            gtk_text_buffer_insert (buffer, &iter, line, -1);
        }
        pclose(f);
        //gtk_box_pack_start (GTK_BOX (jpeg_box), image, FALSE, FALSE, 0);
        //open_file (filename);
        //gtk_widget_queue_draw(image);
        g_free (filename);
    }
    gtk_widget_destroy (file_dialog);

    //f = fopen (filename, "r");
    //length = fread (buffer, 1, sizeof(buffer), f);
    //fclose (f);

    //loader = gdk_pixbuf_loader_new();
    //gdk_pixbuf_loader_write(loader, buffer, length, NULL);
    //pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
    //image = gtk_image_new_from_pixbuf(pixbuf);

    //gtk_container_add (GTK_CONTAINER (window), image);
}
*/
void widget_set_style(GtkWidget *widget, const char *style){
	GtkStyleContext * context;
	context = gtk_widget_get_style_context(widget);
	GtkCssProvider* provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, style, NULL);
	gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void receive_clicked(GtkWidget *widget, gpointer data){
  FILE *f;
  GtkWidget *file_dialog;
  char line[256];
  char str[100];

  system("./receive_vm");  //runs the send jpeg app
  
  usleep(300000);

  gtk_image_set_from_file(GTK_IMAGE(image), "tmpJpegFile.jpg");
        
  /***Load EXIF data that is linked to the file chosen***/
  strcpy (str, "exiftool tmpJpegFile.jpg");
  f = popen(str, "r");
  while ( fgets( line, sizeof line, f))
  {
      gtk_text_buffer_get_end_iter (buffer, &iter);
      gtk_text_buffer_insert (buffer, &iter, line, -1);
  }
  pclose(f);
 
  //g_free ('tmpJpegFile.jpg');
  gtk_widget_set_sensitive(widget, TRUE);
}

int main (int argc, char *argv[])
{

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), "Receive JPEG");
    gtk_window_set_default_size (GTK_WINDOW (window), 1150, 600);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    g_signal_connect (window, "destroy", G_CALLBACK(on_destroy), NULL);
    //gtk_container_border_width (GTK_CONTAINER (window), 10);
    //std::cout << "Here" << std::endl;

    /***initialize 'fixed' widget to place other widgets in the window***/
    fixed = gtk_fixed_new();                                    
    gtk_container_add(GTK_CONTAINER(window), fixed);

    /***vbox to hold the loaded JPEG***/
    jpeg_box = gtk_vbox_new(FALSE, 5);

    /***Hbox to hold buttons***/
    button_hbox = gtk_hbox_new(TRUE, 3);

    /***initialize scroll window***/
    scroll_window = gtk_scrolled_window_new(NULL, NULL);

    /***Add scroll window to the Fixed widget, X value of 600, Y value of 5 to specify where it is placed on the GUI***/
    gtk_fixed_put(GTK_FIXED(fixed), scroll_window, 600, 5);
    gtk_widget_set_size_request(scroll_window, 545, 590);

    /***initialize text view where EXIF data is loaded***/
    txt_view = gtk_text_view_new();
    gtk_text_view_set_overwrite(GTK_TEXT_VIEW(txt_view), TRUE);
    gtk_container_add(GTK_CONTAINER(scroll_window), txt_view);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt_view));

    //exif_button = gtk_button_new_with_label("Load EXIF Data");
    //gtk_fixed_put(GTK_FIXED(fixed), exif_button, 350, 450);
    //gtk_widget_set_size_request(exif_button, 140, 25);

    receive_button = gtk_button_new_with_label("Receive JPEG");
    //gtk_fixed_put(GTK_FIXED(fixed), send_button, 200, 450);
    gtk_widget_set_size_request(receive_button, 140, 25);

    file_button = gtk_button_new_with_label("Load JPEG");
    //gtk_fixed_put(GTK_FIXED(fixed), file_button, 50, 450);
    gtk_widget_set_size_request(file_button, 140, 25);

    /***Add buttons to Hbox***/
    gtk_container_add(GTK_CONTAINER(button_hbox), file_button);
    gtk_container_add(GTK_CONTAINER(button_hbox), receive_button);
    //gtk_container_add(GTK_CONTAINER(button_hbox), exif_button);
    //gtk_widget_set_size_request(jpeg_box, 550, 590);

    /***Loads a placeholder image***/
    image = gtk_image_new_from_file("GD.jpg");

    /***Add HBox and Image to the Vbox***/
    gtk_box_pack_start(GTK_BOX(jpeg_box), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(jpeg_box), button_hbox, FALSE, FALSE, 0);
    gtk_fixed_put(GTK_FIXED(fixed), jpeg_box, 5, 5);

    //gtk_container_add(GTK_CONTAINER(window), jpeg_box);

    /***signals functions connected to buttons***/
    //g_signal_connect (file_button, "clicked", G_CALLBACK(load_JPEG), NULL);
    g_signal_connect (receive_button, "clicked", G_CALLBACK(receive_clicked), NULL);
    //std::cout << "initialized button" << std::endl;
    //gtk_widget_show (file_button);
    //std::cout << "should show button" << std::endl;
    //gtk_container_add (GTK_CONTAINER (window), file_button);


    gtk_widget_show_all (window);

    gtk_main();

    return 0;

}
