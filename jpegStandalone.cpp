/*
 * Standalone JPEG Transmit Demo
 *
 */

//#define JPEG_TRANSFER_HEADER            0 51332 2 %netapp %label :                 
//                                        6 0.100000 0.050000 0.000000 1.000000:    // glClearColor (0.1f, 0.05f, 0.0f, 1.0f);
//                                        27 7425:                                  // glShadeModel (GL_SMOOTH);
//x                                        10 2929:                                  // glEnable (GL_DEPTH_TEST);
//x                                        10 3042:                                  // glEnable (GL_BLEND);
//x                                        3 770 771:                                // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//                                        37 0 0 719 312:                           // glViewport (0, 0, (GLsizei)w, (GLsizei)h);
//                                        18 5889:                                  // glMatrixMode (GL_PROJECTION);
//                                        16:                                       // glLoadIdentity ();
//                                        44 20.000000 2.304487 0.100000 100.000:   // glOrtho(-1, 1, -ar, 1, .1, 100.0);
//                                        18 5888:                                  // glMatrixMode (GL_MODELVIEW);
//                                        16:                                       // glLoadIdentity ();
//                                        5 16640:                                  // glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//x                                        16:                                       // glLoadIdentity ();
//                                        10 3553:                                  // glEnable (GL_TEXTURE_2D);
//JPEG_TRANSFER_DATA_HEADER               51 %d test2.jpg :                         // glLoadJpegTexture_EXT(g_filename, sizeof(g_filename));
//                                        jpeg data here
//JPEG_TRANSFER_TRAILER                   9999 :                                    // NOP
//                                        30 0.000000 0.000000 -5.000000 0.000000:  // glTranslatef (0.0, 0.0, -5.0);
//                                        1 7:                                      // glBegin (GL_QUADS);
//                                        50 0.000000 0.000000:                     // glTexCoord2f (0.0f, 0.0f);
//                                        32 -1.00 -1.00 0.00:                      // glVertex3f (-1, -1, 0); 
//                                        50 1.000000 0.000000:                     // glTexCoord2f (1.0f, 0.0f);
//                                        32 1.00 -1.00 0.00:                       // glVertex3f (1, -1, 0);
//                                        50 1.000000 1.000000:                     // glTexCoord2f (1.0f, 1.0f);
//                                        32 1.00 1.00 0.00:                        // glVertex3f (1, 1, 0);
//                                        50 0.000000 1.000000:                     // glTexCoord2f (0f, 1.0f);
//                                        32 -1.00 1.00 0.00:                       // glVertex3f (-1, -1, 0);
//                                        11:                                       // glEnd  ();
//                                        9 3553:                                   // glDisable (GL_TEXTURE_2D);
//                                        52 :                                      // glUnloadJpegTexture_EXT();
//                                        45 :                                      // glutSwapBuffers ();

//#define JPEG_TRANSFER_HEADER        "0 51332 2 42146 312 312 :6 0.100000 0.050000 0.000000 1.000000:27 7425:10 2929:10 3042:3 770 771:37 0 0 719 312:18 5889:16:44 20.000000 2.304487 0.100000 100.000000:18 5888:16:5 16640:16:10 3553:"

//#define JPEG_TRANSFER_HEADER        "0 51332 2 42146 312 312 :6 0.100000 0.050000 0.000000 1.000000:27 7425:37 0 0 719 312:18 5889:16:44 20.000000 2.304487 0.100000 100.000000:18 5888:16:5 16640:10 3553:"

#define JPEG_TRANSFER_HEADER        "0 51332 %d %s :6 0.100000 0.050000 0.000000 1.000000:27 7425:37 0 0 719 312:18 5889:16:20 -1 1 0 1 .1 100.0:18 5888:16:5 16640:10 3553:"

//#define JPEG_TRANSFER_HEADER        "0 51332 %d %s :6 0.100000 0.050000 0.000000 1.000000:27 7425:37 0 0 719 312:18 5889:16:44 20.000 2.304487 0.100000 100.000000:18 5888:16:5 16640:10 3553:"

//37 0 0 719 312

// 6 =glClearColor
// 27=glShadeModel
// 37=glViewport
// 18=glMatrixMode
// 16=glLoadIdentity
// 44=gluPerspective 
// 18=glMatrixMode
// 16=glLoadIdentity
//  5=glClear
// 10=glEnable


#define JPEG_TRANSFER_DATA_HEADER   "51 %d test2.jpg :"

//#define JPEG_TRANSFER_TRAILER       "9999 :30 0.000000 0.000000 -5.000000 0.000000:1 7:52 0.000000 0.000000:32 -1.00 -1.00 0.00:52 1.000000 0.000000:32 1.00 -1.00 0.00:52 1.000000 1.000000:32 1.00 1.00 0.00:52 0.000000 1.000000:32 -1.00 1.00 0.00:11:9 3553:52 :45 :"

#define JPEG_TRANSFER_TRAILER       "9999 :30 0.000000 0.000000 -5.000000:1 7:52 0.000000 0.000000:32 -1.00 -1.00 0.00:52 1.000000 0.000000:32 1.00 -1.00 0.00:52 1.000000 1.000000:32 1.00 1.00 0.00:52 0.000000 1.000000:32 -1.00 1.00 0.00:11:9 3553:50 :45 :"

// 30=glTranslatef
//  1=glBegin
// 50=glTexCoord2f
// 32=glVertex3f
// 50=glTexCoord2f
// 32=glVertex3f
// 50=glTexCoord2f
// 32=glVertex3f
// 50=glTexCoord2f
// 32=glVertex3f
// 11=glEnd
//  9=glDisable
// 45=glutSwapBuffers

#if 0
#include "glut.h"
#include "ROpenGL.h"
#else
#include <GL/glut.h>
#include "udp_io.h"
#include <stdarg.h>

  void glutBitmapString(void *a, const unsigned char *string)
    {
	    char c;
	    while((c = *(string++))) {
		    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
	    }
    }
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jpegLoader.h"

static void idle(void){
    glutPostRedisplay();
}

/* Texture id for the demo */
char g_filename[80];
char g_dst_ip_address[80];
char g_dst_ip_address2[80];
int  g_dst_ip_port;
static int g_transmit =1;
char g_label[20];
int g_netAppId;


void ssPrintf (char * format, ...)
{
 /*   int       ii; */
    char      buffer[1024];
    va_list   args;
    unsigned int i;

    /* create string for output */
    va_start (args, format);
    vsprintf (buffer, format,  args);
    va_end (args);

  for (i = 0; i < strlen(buffer); i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer[i]);
  }
  return ;
}

void draw_button(int x, int y, char *label, int boxX, int boxY, int focus) {
    GLubyte boxImage[boxX][boxY][4];
    memset (boxImage,30, sizeof(boxImage));

    glRasterPos2f(x,y);
    glDrawPixels(boxX, boxY, GL_RGBA, GL_BYTE, boxImage);

    glRasterPos2f(x+3,y+boxY/2.5);
    ssPrintf(label);
}

static void resize(int width, int height) 
{
    float ar=(float)height/(float)width;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -ar, 1, .1, 100.0);
}

static void display(void) {
  int w=glutGet(GLUT_WINDOW_WIDTH);
  int h=glutGet(GLUT_WINDOW_HEIGHT);
  float ar=(float)h/(float)w;

  /* Initialize OpenGL */
  glClearColor (0.1f, 0.05f, 0.0f, 1.0f);
  glShadeModel (GL_SMOOTH);

 // glEnable (GL_DEPTH_TEST);

 // glEnable (GL_BLEND);
 // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glViewport (0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-1, 1, -ar, 1, .1, 100.0);
//  gluPerspective (20.0, w/(GLdouble)h, 0.1, 100.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glLoadIdentity ();

  glEnable (GL_TEXTURE_2D);

/////////////////////////////////////////
#ifdef __RemoteOGL__

    glLoadJpegTexture_EXT(g_filename, sizeof(g_filename));
#else

  GLuint texId;
  texId = loadJPEGTexture (g_filename);
  glBindTexture (GL_TEXTURE_2D, texId);
#endif
//  printf("texID=%d\n", texId);
///////////////////////////////////////
  /* Draw textured quad */
  glTranslatef (0.0, 0.0, -5.0);
  glBegin (GL_QUADS);
    glTexCoord2f (0.0f, 0.0f);
    glVertex3f (-1.0f, -1.0f, 0.0f);

    glTexCoord2f (1.0f, 0.0f);
    glVertex3f (1.0f, -1.0f, 0.0f);

    glTexCoord2f (1.0f, 1.0f);
    glVertex3f (1.0f, 1.0f, 0.0f);

    glTexCoord2f (0.0f, 1.0f);
    glVertex3f (-1.0f, 1.0f, 0.0f);
  glEnd  ();

  glDisable (GL_TEXTURE_2D);

///////////////////////////////////////
#ifdef __RemoteOGL__
    glUnloadJpegTexture_EXT();
#else
    glDeleteTextures(1, &texId);
#endif
///////////////////////////////////////
    static int old_time=0;
    int new_time = glutGet(GLUT_ELAPSED_TIME)/2000;
    if ((new_time !=old_time) && (g_transmit))
    {
        old_time=new_time;

        // construct message buffer and send to ROGL server
        FILE *fp = fopen (g_filename, "rb");
        if (fp) {
            char tbuf[64*1024];
//            int len = strlen(JPEG_TRANSFER_HEADER);
//            memcpy(tbuf,JPEG_TRANSFER_HEADER,len);
            int len = sprintf(&tbuf[0],JPEG_TRANSFER_HEADER, g_netAppId, g_label);
            fseek ( fp , 0 , SEEK_END );
            int bufsize=ftell (fp);
            fseek ( fp , 0 , SEEK_SET );
            if ((bufsize+len)<60000) 
            {
               len += sprintf(&tbuf[len],JPEG_TRANSFER_DATA_HEADER, bufsize);

               len += fread(&tbuf[len], 1, bufsize, fp);
               strcat(&tbuf[len],JPEG_TRANSFER_TRAILER);
               len += sizeof(JPEG_TRANSFER_TRAILER);
               fclose(fp);

               printf("dest ip = %s ; dest port = %d", g_dst_ip_address, g_dst_ip_port);

               sendMsg(g_dst_ip_address, g_dst_ip_port, tbuf, len+1);
               
               if (strlen(g_dst_ip_address2)) sendMsg(g_dst_ip_address2, g_dst_ip_port, tbuf, len+1);
               
               printf("Sending %d bytes to %s.%d\n", len+1, g_dst_ip_address, g_dst_ip_port);
            }
            else 
            {
            	printf("Dropping transfer, file too big\n");
            }
        }
    }
  glutSwapBuffers ();
}

void processMouse(int button, int state, int x, int y)
{
    if (state == GLUT_UP)
	{
        printf("MOUSE x=%d, y=%d\n", x,y);
	}
}

static void key(unsigned char key, int x, int y)
{
    switch (key) {
        case 27 :   exit(0);    break;
    }
    glutPostRedisplay();
}

int jpgClient(int argc, char *argv[])
{
    /* initialize glut     */
    g_transmit=1;
   strncpy(g_dst_ip_address, argv[1], sizeof(g_dst_ip_address)-1);

   if (argc > 6) strcpy(g_dst_ip_address2, argv[6]);
   else strcpy(g_dst_ip_address2, "");

   g_dst_ip_port = atoi(argv[2]);
   g_netAppId = atoi(argv[3]);
   strncpy(g_label, argv[4], sizeof(g_label)-1);
   strncpy(g_filename, argv[5], sizeof(g_filename)-1);
   printf("target=%s.%d, filename=%s\n", g_dst_ip_address, g_dst_ip_port, g_filename);

    glutInit(&argc, argv);
    glutInitWindowSize(375,219);      // w,h
    glutInitWindowPosition(0,610);   // x,y
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    printf("creating window\n");
    glutCreateWindow("Imager");

    /* initialize the glut call backs functions */
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    printf("creating window1\n");
    /*run */
    printf("starting main loop\n");
    glutMainLoop();
    return EXIT_SUCCESS;
}

#ifndef __vxworks

int main(int argc, char *argv[])
{
printf("\n HERE 0 \n");

    sockInit();

    /* calling sequence  main dp_ip_address dp_port */
    /* calling sequence  main 127.0.0.1 5111 */
    printf("argc=%d, argv[1]=%s, argv[2]=%s \n", argc, argv[1], argv[2]);
    /* initialize glut */
    char partition[80];
    if (argc>5) {
        jpgClient(argc, argv);
    }
    printf("jpegStandalone dest_ip_addr dest_ip_port 0 0 filename, args=%d\n",argc);
    return EXIT_SUCCESS;
}

#endif
////////////////////////////////////////////////////////////////

