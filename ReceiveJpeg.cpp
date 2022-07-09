
#ifdef __cplusplus
extern "C" {
#endif

#include <GL/glut.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#include "udp_io.h"
#include "ROpenGL.h"
#include "GimpImageLoader.h"
#include "jpegLoader.h"
#include "bft.h"
#include "chat.h"
#include "lib_localmap.h"
#include "lib_m2525symbols.h"


SOCKET inSocket[4];
int window0, subWindow[4];

enum {
    APP_SA=1,
    APP_JPEG=2,
    APP_CHAT=3
};

int g_subWindow[3];
int g_window_netapp[3]={APP_SA, APP_CHAT, APP_JPEG};    /* which application assigned to each window*/
int g_window_focus = 0;                                 /* which window has focus */
int g_window_port[3]={0,0,0};                           /* which port owns each window */

float g_mapCenterX=35.;
float g_mapCenterY=-117.5;
float g_mapX=0.;
float g_mapY=0.;
float g_ar=1.;
float g_zoom=1.;
float g_t=0.;
float g_mapScale = 500.;  /* pixels per degree*/
char  g_srcIP[4][20];

#define OGL_PROXY_PORT          5311
#define OGL_PROXY_PORT1_PORT    5312
#define OGL_PROXY_PORT2_PORT    5313
#define OGL_PROXY_PORT3_PORT    5314


static char routBuf[64*1024];

void du(char *c, char*s) 
{
    printf("---%s %s\n",c,s);
}

void ssPrintf (char * format, ...)
{
 /*   int       ii; */
    char      buffer[1024];
    va_list   args;
    int i;

    /* create string for output */
    va_start (args, format);
    vsprintf (buffer, format,  args);
    va_end (args);

  for (i = 0; i < strlen(buffer); i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, buffer[i]);
  }
  return ;
}

void xqt_displayList(char *dlist, int subW) 
{
    char *str;
    int cmd;
    float a,b,c,d,e,f,g,h,i;
    char s1[32],s2[32],s3[32],s4[32],s5[32],s6[32],s7[32];
    int from;
    int inLength;
    char cmdBuffer[64*1024];
    char *cmdBuf=cmdBuffer;
    static GLuint texId;    
    //strcpy(cmdBuf,dlist);
    memcpy(cmdBuf, dlist, sizeof(cmdBuffer));

    str = strtok (cmdBuf,":");

    int w1=glutGet(GLUT_WINDOW_WIDTH);
    int h1=glutGet(GLUT_WINDOW_HEIGHT);
    float ar=(float)h1/(float)w1;


    while (str != NULL) 
    {
        sscanf(str, "%d %f %f %f %f %f %f %f %f %f", &cmd, &a,&b,&c,&d,&e,&f,&g,&h,&i);
        sscanf(str, "%d %s %s %s %s %s %s %s", &cmd, s1,s2,s3,s4,s5,s6,s7);

       //printf("\ncmd = %d\n", cmd);

        switch (cmd) {
            case CMD_HEADER:            du("\n---Start Display List", str); break;
            case CMD_glBegin:           glBegin((int)a);           du("glBegin", str); break;
            case CMD_glBindTexture:     glBindTexture((GLenum)a,(GLenum)b); du("glBindTexture", str);          	break;
            case CMD_glBlendFunc:    	glBlendFunc((GLenum)a,(GLenum)b); du("glBlendFunc", str);         	  	break;
            case CMD_glClear:           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); du("glClear", str);  break;
            case CMD_glClearColor:      glClearColor(a,b,c,d); du("glClearColor", str);          break;
            case CMD_glClearDepth:      glClearDepth(a); du("glClearDepth", str); 				break;
            case CMD_glColor4f:         glColor4f(a,b,c,d); du("glColor4f", str);               break;
            case CMD_glColor3f:         glColor3f(a,b,c);   du("glColor3f", str);             break;
            case CMD_glDisable:         glDisable((GLenum) a); du("glDisable", str);      	break;
            case CMD_glDrawBuffer:      glDrawBuffer((GLenum) a); du("glDrawBuffer", str);  		break;
            case CMD_glEnable:          glEnable((GLenum) a); du("glEnable", str);      		break;
            case CMD_glEnd:             glEnd();   du("glEnd", str);                      break;
            case CMD_glLineWidth:       glLineWidth(a); du("glLineWidth", str);  				break;
            case CMD_glListBase:        glListBase((GLuint)a);  du("glListBase", str); 				break;
            case CMD_glLoadIdentity:    glLoadIdentity();  du("glLoadIdentity", str); 				break;
            case CMD_glMatrixMode:      glMatrixMode((GLenum)a); du("glMatrixMode", str);           		break;
            case CMD_glOrtho:           
            {
               glOrtho(-1, 1, -ar, 1, .1, 100.0);  //du("glOrtho", "Using: ); 
               //glOrtho(a,b,c,d,e,f); du("glOrtho", str);           
               break;
            }
            case CMD_glPopMatrix:       glPopMatrix();  du("glPopMatrix", str);                 break;
            case CMD_glPushMatrix:      glPushMatrix(); du("glPushMatrix", str);                 break;
            case CMD_glRectf:           glRectf(a,b,c,d);  du("glRectf", str); 				break;
            case CMD_glRotatef:         glRotatef(a,b,c,d);   du("glRotatef", str);           break;
//case CMD_glScalef:          glScalef(a,b,c);  du("glBegin",Untitled Folder str);
            case CMD_glScalef:          glScalef(a,b,c);  du("glBegin", str);  				break;
            case CMD_glShadeModel:      glShadeModel((GLenum)a); du("glShadeModel", str);        break;
            case CMD_glTexCoord2i:      glTexCoord2i((GLint)a,(GLint)b); du("glTexCoord2i", str);              break;
            case CMD_glTranslatef:      glTranslatef(a,b,c);  du("glTranslatef", str);           break;
            case CMD_glVertex4f:        glVertex4f(a,b,c,d); du("glVertex4f", str);                break;
            case CMD_glVertex3f:        glVertex3f(a,b,c);   du("glVertex3f", str);              break;
            case CMD_glVertex2f:        glVertex2f(a,b);    du("glVertex2f", str);             break;
            case CMD_glVertex3i:        glVertex3i((GLint)a,(GLint)b,(GLint)c); du("glVertex3i", str);                break;
            case CMD_glVertex2i:        glVertex2i((GLint)a,(GLint)b);  du("glVertex2i", str);               break;
            case CMD_glViewport:  
            {  
               glViewport (0, 0, (GLsizei)w1, (GLsizei)h1);  //du("glViewport", str);                   
               //glViewport((GLint)a,(GLint)b,(GLint)c,(GLint)d); du("glViewport", str);   
               break;
            }
            case CMD_glFogfv:           {GLfloat v[4] = {b,c,d,e}; glFogfv((GLint)a,v); du("glFogfv", str); }  break;
            case CMD_glFogf:            glFogf((GLint)a,b); du("glFogf", str);           break;
            case CMD_glFogi:            glFogi((GLint)a,(GLint)b);   du("glFogi", str);  break;
            case CMD_glRasterPos2f:     glRasterPos2f(a,b);    du("glRasterPos2f", str);             break;
            case CMD_gluLookAt:         gluLookAt(a,b,c,d,e,f,g,h,i);       du("gluLookAt", str);     break;
            case CMD_gluPerspective:    gluPerspective(a,b,c,d); du("gluPerspective", str); break;
            case CMD_glTexCoord2f:      glTexCoord2f(a,b); du("glTexCoord2f", str); break;          
            case CMD_glLoadJpegTexture_EXT:    
            {
                // Save the jpeg file to a temp file
                FILE *fp = NULL;
                // copy binary data to temporary file
                fp = fopen ("tmpJpegFile.jpg", "wb");
                if (fp) 
                {
                    int bufsize=(int)a;
                    char* strptr=&str[strlen(str)+1];  // ptr to binary data

                    // get offset to embedded jpeg file
                    fwrite(&strptr[0], 1, bufsize, fp);

                    // fixup strtok to point to next command
                    cmdBuf=&strptr[bufsize];        // point to end of binary data
                    str = strtok (cmdBuf,":");      // read & discard dummy terminating command
                    printf("\njpeg len=%d, next command=%.40s\n", bufsize, str);
                    fclose(fp);
                    
                    // Load texture from temporary jpeg file
                    texId = loadJPEGTexture ("tmpJpegFile.jpg");

                    glBindTexture (GL_TEXTURE_2D, texId);
                    printf("loadJPEGTexture texID=%d\n", texId);
                }
                else 
                {
                    printf("loadJPEG error, can't create file f=%s\n", s2);
                }  

                du("CMD_glLoadJpegTexture_EXT", str);
                printf("\n");

                break;               
            }
            case CMD_glUnloadJpegTexture_EXT:  glDeleteTextures(1, &texId); du("glDeleteTextures", str);  break;
            case CMD_glutInitWindowSize:   
            {
                int w=glutGet(GLUT_WINDOW_WIDTH);
                int h=glutGet(GLUT_WINDOW_HEIGHT);
                /* determine scale factor */
                float scaleX=(float)w/(float)a;
                float scaleY=(float)h/(float)b;
                float scale = (scaleX>scaleY)?scaleY:scaleX;
                int vw = (int) (scale*(float)a);
                int vy = (int) (scale*(float)b);
                /* center scaled viewport */
                glViewport((w-vw)/2,(h-vy)/2,vw,vy);
                printf("----viewport w=%d, h=%d, x0y0=(%d,%d), w=%d, h=%d\n", w,h, (w-vw)/2,(h-vy)/2,vw,vy); 
                du("glutInitWindowSize", str);         
                break;
            }
            case CMD_glutSwapBuffers:   /*glutSwapBuffers();*/     du("glutSwapBuffers", str);         return;
            case CMD_glutBitmapString:  /*printf("string=%s\n", str);*/ {
                int startIndex = strcspn(str,"0");
                ssPrintf("%s", &str[startIndex+2]);  
                du("ssPrintf", str);            
                break; /* extension*/
            }

            default:  printf("unknown command ->%s\n", str);
         }
         str = strtok (NULL,":");
    }
}

static void idle(void){ glutPostRedisplay(); }

static void display(void)
{
    char cmdBuf[64*1024];
    char *str;
    int cmd;
    int from;
    int inLength, outLength;
    char fromIP[20];
    static int stale_data[3][4]={0,0,0,0,0,0,0,0,0,0,0,0};
    static char displayList[3][4][64*1024];
    
    while ((inLength = recvMsg4(inSocket, cmdBuf, sizeof(cmdBuf), fromIP, &from, 1000000))>0)
    {

        //sleep(1);

        printf("\n--------------------------------------------------\n");
        printf("msgin=%.80s\n",cmdBuf);
        printf("Message size - rcd %d bytes\n", inLength);  

        int cmd;
        int a, netapp;
        char c[20];
        sscanf(cmdBuf, "%d %d %d %s ", &cmd, &a, &netapp, c); 

        printf("magic=%d, netapp=%d, from=%d, c=%d, %.20s\n", a, netapp, from, c, cmdBuf); 
        printf("----------------------------------------------------\n");

        if (a==51332) 
        {    
           /* remote OpenGL display list*/


            strcpy(g_srcIP[from], fromIP);

            int win;
            for (win=2; win<3; win++) 
            {
                if (netapp==g_window_netapp[APP_JPEG]) 
                {
                    memcpy(displayList[win][from], cmdBuf, inLength+1);

                    if ((win==0) && (from==0))printf("storing display list in dl[w.%d][p.%d] stale=%d\n",win,from,stale_data[win][from] );

                    stale_data[win][from]=50;
                  printf("storing display list in dl[w.%d][p.%d]\n",win,from);
                }               
             }
        }
        else
        {
            printf("unknown packet:magic=%d str=%.40s\n", a, cmdBuf);
        }
    }


    /* execute old windows */
    int win;
    

       int win=2;
       int port=0;
       xqt_displayList(displayList[win][port], APP_JPEG);        


       
    }
}


int jpgServer(int argc, char *argv[])
{
    
    int w=535, h=310, gap=5;
    glutInit(&argc, argv);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(60,590);   // x,y
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    printf("creating window\n");
    glutCreateWindow("Imager");

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    // initialize sockets 
    sockInit();

    inSocket[0] = recvMsgInit(OGL_PROXY_PORT);
    inSocket[1] = recvMsgInit(OGL_PROXY_PORT1_PORT);
    inSocket[2] = recvMsgInit(OGL_PROXY_PORT2_PORT);
    inSocket[3] = recvMsgInit(OGL_PROXY_PORT3_PORT);
    
    //printf("starting main loop\n");
    glutMainLoop();
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{

    // calling sequence  main dp_ip_address dp_port chat_server_ip_address chat_server_ip_port
    printf("argc=%d, argv[0]=%s, argv[1]=%s argv[2]=%s, argv[3]=%s\n", argc, argv[0], argv[1], argv[1], argv[3]);

    // initialize glut
    if (argc>=3) 
    {
        jpgServer(argc, argv);
    }

    return EXIT_SUCCESS;
}


#ifdef __cplusplus
}
#endif

