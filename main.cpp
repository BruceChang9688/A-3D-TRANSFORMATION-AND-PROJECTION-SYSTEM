//Dingheng Zhang
//Project 2 test


#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define PI acos(-1)


class wcPt3D {
public:
GLfloat x, y, z;
};

class edgePoint{
public:
    GLint x1, x2;
};

int num_poly;
int num_point_init = 3000;
int num_edge_init = 8000;
int num_axis = 3;
int num_edge_point = 2;

int width=200;
int length=200;
float pixel_size;
int win_width=200;
int win_height=200;

int RotAxisSign;
wcPt3D P1,P2;


wcPt3D **MainVec;
edgePoint **MainEdge;
int *num_point;
int *num_edge;
wcPt3D *GravityP;

void WriteFile();
string File_Address;

int Initialize(GLfloat num1)
{
    num1 = (num1 + 1)/2*width;
    int num2;
    num2 = int(num1);
    return num2;
}

void GravityPt()
{
    for(int i=0;i<num_poly;i++)
    {
        GravityP[i].x = GravityP[i].y =GravityP[i].z =0;
        for(int j=0;j<num_point[i];j++)
        {
            GravityP[i].x = GravityP[i].x + MainVec[i][j].x;
            GravityP[i].y = GravityP[i].y + MainVec[i][j].y;
            GravityP[i].z = GravityP[i].z + MainVec[i][j].z;
        }
        GravityP[i].x = GravityP[i].x/num_point[i];
        GravityP[i].y = GravityP[i].y/num_point[i];
        GravityP[i].z = GravityP[i].z/num_point[i];
    }
    
}


void drawpoly()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, 2*win_width, 2*win_height);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(width/2, 0);
    glVertex2f(width/2, length);
    glVertex2f(0, length/2);
    glVertex2f(width, length/2);
    glEnd();
    
    //xy up left
    glViewport(0, win_height, win_width, win_height);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<num_poly;i++)
        for(int j=0;j<num_edge[i];j++)
        {
            int point1 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x1-1].x),Initialize(MainVec[i][MainEdge[i][j].x1-1].y)};
            int point2 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x2-1].x),Initialize(MainVec[i][MainEdge[i][j].x2-1].y)};
            glVertex2iv (point1);
            glVertex2iv (point2);
        }
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(Initialize(-0.5),Initialize(0));
    glVertex2f(Initialize(0.5),Initialize(0));
    glVertex2f(Initialize(0),Initialize(-0.5));
    glVertex2f(Initialize(0),Initialize(0.5));
    glEnd();
    if(RotAxisSign == 1)
    {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(Initialize(P1.x),Initialize(P1.y));
        glVertex2f(Initialize(P2.x),Initialize(P2.y));
        glEnd();
    }
    
    
    //yz bottom left
    glViewport(0, 0, win_width, win_height);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<num_poly;i++)
        for(int j=0;j<num_edge[i];j++)
        {
            int point1 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x1-1].y),Initialize(MainVec[i][MainEdge[i][j].x1-1].z)};
            int point2 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x2-1].y),Initialize(MainVec[i][MainEdge[i][j].x2-1].z)};
            glVertex2iv (point1);
            glVertex2iv (point2);
        }
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(Initialize(-0.5),Initialize(0));
    glVertex2f(Initialize(0.5),Initialize(0));
    glVertex2f(Initialize(0),Initialize(-0.5));
    glVertex2f(Initialize(0),Initialize(0.5));
    glEnd();
    if(RotAxisSign == 1)
    {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(Initialize(P1.y),Initialize(P1.z));
        glVertex2f(Initialize(P2.y),Initialize(P2.z));
        glEnd();
    }
    
    //xz up right
    glViewport(win_width, win_height, win_width, win_height);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<num_poly;i++)
        for(int j=0;j<num_edge[i];j++)
        {
            int point1 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x1-1].x),Initialize(MainVec[i][MainEdge[i][j].x1-1].z)};
            int point2 [ ] = {Initialize(MainVec[i][MainEdge[i][j].x2-1].x),Initialize(MainVec[i][MainEdge[i][j].x2-1].z)};
            glVertex2iv (point1);
            glVertex2iv (point2);
        }
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(Initialize(-0.5),Initialize(0));
    glVertex2f(Initialize(0.5),Initialize(0));
    glVertex2f(Initialize(0),Initialize(-0.5));
    glVertex2f(Initialize(0),Initialize(0.5));
    glEnd();
    if(RotAxisSign == 1)
       {
           glBegin(GL_LINES);
           glColor3f(1.0, 0.0, 0.0);
           glVertex2f(Initialize(P1.x),Initialize(P1.z));
           glVertex2f(Initialize(P2.x),Initialize(P2.z));
           glEnd();
       }
    
    
    glFlush();
    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
}

void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  /* glViewport(0 , 0 , 640 , 480); */
  glMatrixMode(GL_PROJECTION);
  /* glLoadIdentity(); */
  gluOrtho2D(0, win_width , 0 , win_height);
}

void reshape(int reshape_width, int reshape_height)
{
    /*set up projection matrix to define the view port*/
    //update the ne window width and height
    win_width = reshape_width;
    win_height = reshape_height;
    
    //creates a rendering area across the window
    glViewport(0,0,reshape_width,reshape_height);
    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,width,0,length,-10,10);
    
    //clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //set pixel size based on width, if the aspect ratio
    //changes this hack won't work as well
    pixel_size = reshape_width/(float)width;
    
    //set pixel size relative to the grid cell size
    glPointSize(pixel_size);
    //check for opengl errors
}


typedef GLfloat Matrix4x4 [4][4];
Matrix4x4 matComposite;
typedef GLfloat Matrix4x1 [4][1];
Matrix4x1 matPoint;
/* Construct the 4 x 4 identity matrix. */

void matrix4x1SetIdentity (Matrix4x1 matIdent4x1)
{
    GLint row;
    for (row=0;row<4;row++)
    {
        if(row==3) matIdent4x1[row][0] = 1;
        else matIdent4x1[row][0] = 0;
    }
}

void matrix4x4SetIdentity (Matrix4x4 matIdent4x4)
{
    GLint row, col;
    for (row = 0; row < 4; row++)
        for (col = 0; col < 4 ; col++)
        {
            matIdent4x4 [row][col] = (row == col);
        }
}

/* Premultiply matrix m1 by matrix m2, store result in m2. */
void matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 m2)
{
    GLint row, col;
    Matrix4x4 matTemp;
    matrix4x4SetIdentity(matTemp);
    for (row = 0; row < 4; row++)
        for (col = 0; col < 4 ; col++)
            matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
    for (row = 0; row < 4; row++)
        for (col = 0; col < 4; col++)
            matComposite[row][col] = matTemp[row][col];
}

void matrix4x1Multiply(Matrix4x4 m1, Matrix4x1 m2)
{
    GLint row;
    Matrix4x1 matTemp;
    matrix4x1SetIdentity(matTemp);
    for(row=0;row<4;row++)
        matTemp[row][0] = m1[row][0]*m2[0][0]+m1[row][1]*m2[1][0]+m1[row][2]*m2[2][0]+m1[row][3]*m2[3][0];
    for(row=0;row<4;row++)
        matPoint[row][0] = matTemp[row][0];
    
}

/* Procedure for generating 3-D translation matrix. */
void translate3D (GLfloat tx, GLfloat ty, GLfloat tz,int PloySign)
{
    int i = PloySign;
    Matrix4x4 matTransl3D;
/* Initialize translation matrix to identity. */
    matrix4x4SetIdentity (matTransl3D);
    matTransl3D [0][3] = tx;
    matTransl3D [1][3] = ty;
    matTransl3D [2][3] = tz;
    cout<<tx<<ty<<tz<<endl;
/* Concatenate matTransl3D with composite matrix. */
        for(int j=0;j<num_point[i];j++)
        {
            matrix4x1SetIdentity(matPoint);
            matPoint[0][0] = MainVec[i][j].x;
            matPoint[1][0] = MainVec[i][j].y;
            matPoint[2][0] = MainVec[i][j].z;
            matrix4x1Multiply(matTransl3D, matPoint);
            MainVec[i][j].x = matPoint[0][0];
            MainVec[i][j].y = matPoint[1][0];
            MainVec[i][j].z = matPoint[2][0];
        }
}

/* Procedure for generating a quaternion rotation matrix. */
void rotate3D (wcPt3D p1, wcPt3D p2, GLfloat radianAngle,int PloySign)
{
    int i = PloySign;
    Matrix4x4 matTransl3D;
    Matrix4x4 matQuatRot;
    matrix4x4SetIdentity(matComposite);
    matrix4x4SetIdentity (matTransl3D);
    matTransl3D [0][3] = p1.x;
    matTransl3D [1][3] = p1.y;
    matTransl3D [2][3] = p1.z;
    
    float axisVectLength = sqrt ((p2.x - p1.x) * (p2.x - p1.x) +
                                 (p2.y - p1.y) * (p2.y - p1.y) +
                                 (p2.z - p1.z) * (p2.z - p1.z));
    float cosA = cosf (radianAngle);
    float oneC = 1 - cosA;
    float sinA = sinf (radianAngle);
    float ux = (p2.x - p1.x) / axisVectLength;
    float uy = (p2.y - p1.y) / axisVectLength;
    float uz = (p2.z - p1.z) / axisVectLength;

    
    matrix4x4SetIdentity (matQuatRot);
    matQuatRot [0][0] = ux*ux*oneC + cosA;
    matQuatRot [0][1] = ux*uy*oneC - uz*sinA;
    matQuatRot [0][2] = ux*uz*oneC + uy*sinA;
    matQuatRot [1][0] = uy*ux*oneC + uz*sinA;
    matQuatRot [1][1] = uy*uy*oneC + cosA;
    matQuatRot [1][2] = uy*uz*oneC - ux*sinA;
    matQuatRot [2][0] = uz*ux*oneC - uy*sinA;
    matQuatRot [2][1] = uz*uy*oneC + ux*sinA;
    matQuatRot [2][2] = uz*uz*oneC + cosA;
/* Concatenate matQuatRot with composite matrix. */
    matrix4x4PreMultiply (matTransl3D, matQuatRot);
    matrix4x4SetIdentity (matTransl3D);
    matTransl3D [0][3] = -p1.x;
    matTransl3D [1][3] = -p1.y;
    matTransl3D [2][3] = -p1.z;
    matrix4x4PreMultiply (matComposite, matTransl3D);
    
    for(int j=0;j<num_point[i];j++)
    {
        matrix4x1SetIdentity(matPoint);
        matPoint[0][0] = MainVec[i][j].x;
        matPoint[1][0] = MainVec[i][j].y;
        matPoint[2][0] = MainVec[i][j].z;
        matrix4x1Multiply(matComposite, matPoint);
        MainVec[i][j].x = matPoint[0][0];
        MainVec[i][j].y = matPoint[1][0];
        MainVec[i][j].z = matPoint[2][0];
    }
}
/* Procedure for generating a 3-D scaling matrix. */
void scale3D (GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt,int PolySign)
{
    Matrix4x4 matScale3D;
/* Initialize scaling matrix to identity. */
    matrix4x4SetIdentity (matScale3D);
    matScale3D [0][0] = sx;
    matScale3D [0][3] = (1 - sx) * fixedPt.x;
    matScale3D [1][1] = sy;
    matScale3D [1][3] = (1 - sy) * fixedPt.y;
    matScale3D [2][2] = sz;
    matScale3D [2][3] = (1 - sz) * fixedPt.z;
/* Concatenate matScale3D with composite matrix. */
    int i = PolySign;
    for(int j=0;j<num_point[i];j++)
    {
        matrix4x1SetIdentity(matPoint);
        matPoint[0][0] = MainVec[i][j].x;
        matPoint[1][0] = MainVec[i][j].y;
        matPoint[2][0] = MainVec[i][j].z;
        matrix4x1Multiply(matScale3D, matPoint);
        MainVec[i][j].x = matPoint[0][0];
        MainVec[i][j].y = matPoint[1][0];
        MainVec[i][j].z = matPoint[2][0];
    }
}

void ThreeDTrans()
{
    GravityPt();
    RotAxisSign = 0;
    int trans_sign=0;
    int poly_trans=0;
    RotAxisSign = 0;
    cout<<"Here are "<<num_poly<<" objects."<<endl;
    cout<<"Which object you want to transform."<<endl;
    cin>>poly_trans;
    cout<<"Please type in '1' for translation, '2' for rotation, '3' for scailing."<<endl;
    cin>>trans_sign;
    poly_trans--;
    cout<<"In order to make transformation easier, here is this object's gravity point:"<<endl;
    cout<<GravityP[poly_trans].x<<" "<<GravityP[poly_trans].y<<" "<<GravityP[poly_trans].z<<endl;
    if(trans_sign==1)
    {
        GLfloat tx, ty, tz;
        cout<<"Type in the translation parameters: tx, ty, tz."<<endl;
        cin>>tx>>ty>>tz;
        translate3D(tx, ty, tz,poly_trans);
    }
    if(trans_sign==2)
    {
        P1.x = P1.y=P1.z = P2.x=P2.y=P2.z=0;
        GLfloat RotateAngle;
        cout<<"Please type in the first point on the rotation axis."<<endl;
        cin>>P1.x>>P1.y>>P1.z;
        cout<<"Please type in the first point on the rotation axis."<<endl;
        cin>>P2.x>>P2.y>>P2.z;
        RotAxisSign = 1;
        drawpoly();
        cout<<"The rotation axis is showing as the red line."<<endl;
        cout<<"Please type in the rotation angle."<<endl;
        cin>>RotateAngle;
        RotateAngle = RotateAngle*PI/180;
        rotate3D(P1, P2, RotateAngle, poly_trans);
    }
    if(trans_sign==3)
    {
        GLfloat sx,sy,sz;
        wcPt3D fixedPts;
        cout<<"Please type in the scaling parameters: sx,sy,sz."<<endl;
        cin>>sx>>sy>>sz;
        cout<<"Please type in the fix point parameters: x,y,z."<<endl;
        cin>>fixedPts.x>>fixedPts.y>>fixedPts.z;
        scale3D(sx, sy, sz, fixedPts,poly_trans);
        
    }
    drawpoly();
    WriteFile();
    cout<<"finish"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"Press 't' to continue transforming"<<endl;
}

void key(unsigned char ch, int x, int y)
{
    if(ch=='t')
    {
        ThreeDTrans();
        glutPostRedisplay();
    }
}

void ReadFile()
{
    cout<<"WELCOME TO PROJECT2 - 3D TRANSFORMATION AND PROJECTION STSTEM"<<endl;
    cout<<"Please input the file address. Input like '/Users/bruce/Documents/ECS175/project/project2/testb.txt' "<<endl;
    cin>>File_Address;
    std::ifstream infile;
    infile.open(File_Address.c_str());
    cout<<"I am reading the file."<<endl;
    
    infile>>num_poly;

    MainVec = new wcPt3D*[num_poly];
    MainEdge = new edgePoint*[num_poly];
    num_point = new int[num_poly];
    num_edge = new int[num_poly];
    GravityP = new wcPt3D[num_poly];
    for (int i=0;i<num_poly;i++) MainVec[i] = new wcPt3D [num_point_init];
    for (int i=0;i<num_poly;i++) MainEdge[i] = new edgePoint [num_edge_init];
    
    

    for(int i=0;i<num_poly;i++)
    {
        infile>>num_point[i];
        for(int j=0;j<num_point[i];j++)
        {
            infile>>MainVec[i][j].x;
            infile>>MainVec[i][j].y;
            infile>>MainVec[i][j].z;
        }
        infile>>num_edge[i];
        for(int j=0;j<num_edge[i];j++)
        {
                infile>>MainEdge[i][j].x1;
                infile>>MainEdge[i][j].x2;
        }
    }
    
    cout<<"The projection is here. There are three blocks that show the object in Three planes."<<endl;
    cout<<"The up left one is the xy-plane, and the blue axis is the x axis and y axis."<<endl;
    cout<<"The bottom left one is the yz-plane, and the blue axis is the y axis and z axis."<<endl;
    cout<<"The up right one is the xz-plane, and the blue axis is the x axis and z axis."<<endl;
    cout<<"Let's start transforming."<<endl;
    cout<<"Press 't' to continue transforming."<<endl;
}

void WriteFile()
{
    ofstream outfile;
    outfile.open("/Users/bruce/Documents/ECS175/project/project2/Output_file.txt");
    outfile<<num_poly<<'\t'<<"number of objects"<<endl;
    for(int i=0;i<num_poly;i++)
        {
            if(i==0)
            {
                outfile<<'\t'<<"definition of 1st object:"<<endl;
            }
            else if(i==1)
            {
                outfile<<'\t'<<"definition of 2nd object:"<<endl;
            }
            else if(i==2)
            {
                outfile<<'\t'<<"definition of 3rd object:"<<endl;
            }
            else
            {
                outfile<<'\t'<<"definition of "<<(i+1)<<"th object:"<<endl;
            }
            
            outfile<<num_point[i];
            if(i==0)
            {
                outfile<<'\t'<<"number of points of 1st object"<<endl;
            }
            else if(i==1)
            {
                outfile<<'\t'<<"number of points of 2nd object"<<endl;
            }
            else if(i==2)
            {
                outfile<<'\t'<<"number of points of 3rd object"<<endl;
            }
            else
            {
                outfile<<'\t'<<"number of points of "<<(i+1)<<"object"<<endl;
            }
            
            for(int j=0;j<num_point[i];j++)
            {
                outfile<<MainVec[i][j].x<<" "<<MainVec[i][j].y<<" "<<MainVec[i][j].z<<'\t';
                if((j%10==0)&&(j!=10))
                {
                    outfile<<"coordinates of "<<(j+1)<<"st point"<<endl;
                }
                else if((j%10==1)&&(j!=11))
                {
                    outfile<<"coordinates of "<<(j+1)<<"nd point"<<endl;
                }
                else if((j%10==2)&&(j!=12))
                {
                    outfile<<"coordinates of "<<(j+1)<<"rd point"<<endl;
                }
                else
                {
                    outfile<<"coordinates of "<<(j+1)<<"th point"<<endl;
                }
            }
            
            outfile<<num_edge[i];
            if(i==0)
            {
                outfile<<'\t'<<"number of edges of 1st object"<<endl;
            }
            else if(i==1)
            {
                outfile<<'\t'<<"number of edges of 2nd object"<<endl;
            }
            else if(i==2)
            {
                outfile<<'\t'<<"number of edges of 3rd object"<<endl;
            }
            else
            {
                outfile<<'\t'<<"number of edges of "<<(i+1)<<"object"<<endl;
            }
            
            for(int j=0;j<num_edge[i];j++)
            {
                outfile<<MainEdge[i][j].x1<<" "<<MainEdge[i][j].x2<<'\t';
                outfile<<"edge from point "<<MainEdge[i][j].x1<<" to "<<MainEdge[i][j].x2<<endl;
            }
            
        }
    
}

int main(int argc, char **argv)
{
    ReadFile();
    WriteFile();
    /* Initialise GLUT library */
        glutInit(&argc,argv);
    /* Set the initial display mode */
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    /* Set the initial window position and size */
        glutInitWindowPosition(100,100);
        glutInitWindowSize(win_width,win_height);
        glutCreateWindow("Project2");
    /* Initialize drawing colors */
        Init();
    /* Call the displaying function */
        glutDisplayFunc(drawpoly);
    glutReshapeFunc(reshape);
    /* Keep displaying untill the program is closed */
    glutKeyboardFunc(key);
        glutMainLoop();
    
    for(int i=0;i<num_poly;i++)
    {
        delete [] MainVec[i];
        delete [] MainEdge[i];
    }
    delete [] MainVec;
    delete [] MainEdge;
    delete [] num_point;
    delete [] num_edge;
    delete [] GravityP;
}
