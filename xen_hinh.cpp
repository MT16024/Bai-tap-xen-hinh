#include<gl/glut.h>
#include <math.h>

using namespace std;

const int max_ver = 20;
const float borderx1 = 100.0f, bordery1 = 50.0f, borderx2 = 700.0f, bordery2 = 550.0f;

//Toa do ccasdiem cua da giac
float x[max_ver] = { 200.0f, 400.0f, 300.0f };
float y[max_ver] = { 200.0f, 200.0f, 400.0f };
int n = 3;

//Toa do cac dinh cua hinh chu nhat bao quanh
float X1 = borderx1, X2 = borderx2;
float Y1 = bordery1, Y2 = bordery2;

// Thuat toan Sutherland hodman
bool inside(float xi, float yi, int pos, float a, float b, float c, float d)
{
float res = a * xi + b * yi + c;
if (pos == 1)
return res >= 0;
else if (pos == 2)
return res <= 0;
else if (pos == 3)
return res > 0;
else
return res < 0;
}

void draw_square()
{
// Ve duong bao quanh hinh chu nhat
glColor3f(0.8f, 0.8f, 0.8f);
glBegin(GL_LINE_LOOP);
glVertex2f(X1, Y1);
glVertex2f(X1, Y2);
glVertex2f(X2, Y2);
glVertex2f(X2, Y1);
glEnd();
}

void draw_poly()
{
// Ve da giac
glColor3f(0.2f, 0.2f, 1.0f);
glBegin(GL_POLYGON);
for (int i = 0; i < n; ++i)
glVertex2f(x[i], y[i]);
glEnd();
}

void Sutherland_hodman()
{
// Lap qua tat ca cac canh cua hinh chu nhat
for (int edge = 1; edge <= 4; ++edge)
{
int i1 = n - 1;
for (int i2 = 0; i2 < n; ++i2)
{
// Tinh toan dieu kien cat
float a = Y1 - Y2;
float b = X2 - X1;
float c = X1 * Y2 - X2 * Y1;
int cond = inside(x[i2], y[i2], edge, a, b, c, 0.0f);

if (inside(x[i1], y[i1], edge, a, b, c, 0.0f) != cond)
{
// Tinh toan toa do cua diem cat
float d1 = a * x[i1] + b * y[i1] + c;
float d2 = a * x[i2] + b * y[i2] + c;
float xi = (d1 * x[i2] - d2 * x[i1]) / (d1 - d2);
float yi = (d1 * y[i2] - d2 * y[i1]) / (d1 - d2);

// Them diem moi
x[n] = xi;
y[n] = yi;
++n;
}

// Kiem tra diem hien tai
if (cond)
{
// Them diem moi
x[n] = x[i2];
y[n] = y[i2];
++n;
}

// Cap nhat vi tri cua diem truoc do
i1 = i2;
}

// Cap nhat so luong diem cua da giac
n -= (n > 3);
}
}

void display ()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f (0.0,0.4,0.3);




// Ve hinh chu nhat va da giac da duoc cat
draw_square();
draw_poly();

glFlush();
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(800, 600);
glutCreateWindow("thuat toan xen da giac = Sutherland Hodgman ");
gluOrtho2D(0, 800, 0, 600);
glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

glutDisplayFunc(display);

glutMainLoop();

return 0;
}
