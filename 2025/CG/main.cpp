////////////////////////////////////////////////////////////////////////////////////        
// canvas.cpp
//
// This program allows the user to draw simple shapes on a canvas.
//
// Interaction:
// Left click on a box on the left to select a primitive.
// Then left click on the drawing area: once for point, twice for line or rectangle.
// Right click for menu options.
//
//  Sumanta Guha.
//////////////////////////////////////////////////////////////////////////////////// 

// Com alterações de Igor Roberto M. de Souza - 2025/05
// Como compilar:
// g++ main.cpp -o main -lglut -lGL -lGLU -lm

// Como executar:
// ./main

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

#include <chrono>
//Limitei pra não dar problema com algo depois
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

auto lastClickTime = high_resolution_clock::now();

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define BISSETRIZ 4
#define TEXT 5
#define NUMBERPRIMITIVES 5

// Use the STL extension of C++.
using namespace std;

// Globals.
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int tempX2, tempY2; // Co-ordinates of clicked point.
static int tempX3, tempY3;
static int isGrid = 1; // Is there grid?

static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
int currentcolor = 5;
int currentStipple = 0;
float gridSlice = 0.1;

void setColor(int id)
{
   if (id==3) glColor3f(1.0, 0.0, 0.0);
   if (id==4) glColor3f(0.0, 0.0, 1.0);
   if (id==5) glColor3f(0.0, 0.0, 0.0);
}

void setStipple(int id){
   glEnable(GL_LINE_STIPPLE);
   switch (id)
   {
   case 0:
      glDisable(GL_LINE_STIPPLE);
      break;
   
   case 1:
      glLineStipple(1, 0x5555);
      break;
   
   case 2:
      glLineStipple(1, 0x0101);
      break;

   case 3:
      glLineStipple(1, 0x00FF);
      break;

   case 4:
      glLineStipple(5, 0x5555);
      break;
      
   default:
      break;
   }
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
} 

// Point class.
class Point
{
public:
   Point(int xVal, int yVal, int colorIdVal)
   {
	  x = xVal; y = yVal; colorId = colorIdVal;
   }
   void drawPoint(void); // Function to draw a point.
private:
   int x, y; // x and y co-ordinates of point.
   static float size; // Size of point.
   int colorId; //Cor do Ponto
};

float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint()
{  
   setColor(this->colorId);
   glPointSize(size);
   glBegin(GL_POINTS);
      glVertex3f(x, y, 0.0);
   glEnd();   
}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator; 

// Function to draw all points in the points array.
void drawPoints(void)
{
   // Loop through the points array drawing each point.
   pointsIterator = points.begin();
   while(pointsIterator != points.end() )
   {
      pointsIterator->drawPoint();
	  pointsIterator++;
   }
}

// Line class.
class Line
{
public:
   Line(int x1Val, int y1Val, int x2Val, int y2Val, int colorIdVal, int StippleVal)
   {
	  x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val; colorId = colorIdVal; StippleId = StippleVal;
   }
   void drawLine();
   //Temos Gets para retornar os pontos das linhas que são usados para achar a bissetriz
   int getX1() const { return x1; }
   int getY1() const { return y1; }
   int getX2() const { return x2; }
   int getY2() const { return y2; }

private:
   int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
   int colorId;
   int StippleId; 
};


// Function to draw a line.
void Line::drawLine()
{
   setColor(this->colorId);
   setStipple(this->StippleId);
   glBegin(GL_LINES);
      glVertex3f(x1, y1, 0.0);
      glVertex3f(x2, y2, 0.0);
   glEnd();
   glDisable(GL_LINE_STIPPLE);
}

// Vector of lines.
vector<Line> lines;

// Iterator to traverse a Line array.
vector<Line>::iterator linesIterator;

// Function to draw all lines in the lines array.
void drawLines(void)
{
   // Loop through the lines array drawing each line.
   linesIterator = lines.begin();
   while(linesIterator != lines.end() )
   {
      linesIterator->drawLine();
	  linesIterator++;
   }
}

//Função para saber se o click é perto de uma linha
bool isNearLine(const Line& line, int mouseX, int mouseY, float threshold = 10.0f) {
   float x1 = line.getX1();
   float y1 = line.getY1();
   float x2 = line.getX2();
   float y2 = line.getY2();

   float dx = x2 - x1;
   float dy = y2 - y1;

   float lengthSquared = dx * dx + dy * dy;
   if (lengthSquared == 0.0f) return false; //linha é um ponto

   float t = ((mouseX - x1) * dx + (mouseY - y1) * dy) / lengthSquared;
   t = max(0.0f, min(1.0f, t));

   float projX = x1 + t * dx;
   float projY = y1 + t * dy;

   float dist = sqrt((projX - mouseX) * (projX - mouseX) + (projY - mouseY) * (projY - mouseY));

   return dist < threshold;
}

//Ponteiros para armazenar as linhas clicadas.
Line* selectedLine1 = nullptr;
Line* selectedLine2 = nullptr;

//TEXT class
class Text{
   private:
      int x, y;
      string textData;
      int colorId;

   public:
      Text(int xVal, int yVal, string textVal, int colorIdVal){
         x = xVal;
         y = yVal;
         textData = textVal;
         colorId = colorIdVal;
      }

   void drawText();
};

void Text::drawText(){
   setColor(this->colorId);
   glRasterPos3f(x, y, 0.0);
   writeBitmapString((void*)font, (char*)textData.c_str());
}

vector<Text> text;

vector<Text>::iterator textIterator;

void drawText(void){
   textIterator = text.begin();
   while(textIterator != text.end()){
      textIterator->drawText();
      textIterator++;
   }
}

//BISSETRIZ class
class Bissetriz{
   public:
      Bissetriz(int x1Val, int y1Val, int x2Val, int y2Val, int x3Val, int y3Val, int colorIdVal, int StippleIdVal, int is3PointsVal){
         x1 = x1Val; 
         y1 = y1Val; 
         x2 = x2Val; 
         y2 = y2Val; 
         x3 = x3Val; 
         y3 = y3Val; 
         colorId = colorIdVal;
         StippleId = StippleIdVal;
         is3Points = is3PointsVal;
      }
      Bissetriz(){};
      void drawBissetriz();
      void setCoords(int x, int y){
         x3 = x;
         y3 = y;
      }

   private:
      int x1, x2, x3;
      int y1, y2, y3;
      int colorId;
      int StippleId;
      int is3Points;
};

void Bissetriz::drawBissetriz()
{
   setColor(this->colorId);
   setStipple(this->StippleId);
   if(is3Points){ //Faz o desenho inteiro de uma bissetriz, isso serve para caso eu tenha 2 retas ele não completar
      glBegin(GL_LINES);
         glVertex3f(x1, y1, 0.0);
         glVertex3f(x2, y2, 0.0);
         glVertex3f(x2, y2, 0.0);
         glVertex3f(x3, y3, 0.0);
      glEnd();
   }

   //encontrando bissetriz

   float v1x = x1 - x2;
   float v1y = y1 - y2;

   float v2x = x3 - x2;
   float v2y = y3 - y2;

   //Normaliza os vetores
   float len1 = std::sqrt(v1x * v1x + v1y * v1y);
   float len2 = std::sqrt(v2x * v2x + v2y * v2y);

   float u1x = v1x / len1;
   float u1y = v1y / len1;

   float u2x = v2x / len2;
   float u2y = v2y / len2;

   //Soma dos vetores unitários -> direção da bissetriz
   float bx = u1x + u2x;
   float by = u1y + u2y;

   //Normaliza a direção da bissetriz
   float bLen = std::sqrt(bx * bx + by * by);
   float ubx = bx / bLen;
   float uby = by / bLen;

   //Define o comprimento da bissetriz
   float bisLength = 1000;

   //Calcula os pontos de Bissetriz apartir de P2
   float bxFinal = x2 + ubx * bisLength;
   float byFinal = y2 + uby * bisLength;

   float bxFinalOp = x2 - ubx * bisLength;
   float byFinalOp = y2 - uby * bisLength;

   glBegin(GL_LINES); //Trocar para ficar para 100% da tela
      glVertex3f(bxFinalOp, byFinalOp, 0.0f);
      glVertex3f(bxFinal, byFinal, 0.0f);
   glEnd();
   glDisable(GL_LINE_STIPPLE);
}

vector<Bissetriz> bissetriz;

vector<Bissetriz>::iterator bissetrizIterator;

Bissetriz currentBissetriz;

void drawBissetrizes(void)
{
   bissetrizIterator = bissetriz.begin();
   while(bissetrizIterator != bissetriz.end() ){
      bissetrizIterator->drawBissetriz();
      bissetrizIterator++;
   }

   currentBissetriz.drawBissetriz();
   glFlush();
}

// Rectangle class.
class Rectangle
{
public:
   Rectangle(int x1Val, int y1Val, int x2Val, int y2Val, int colorIdVal,  int StippleIdVal)
   {
	  x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val; colorId = colorIdVal; StippleId = StippleIdVal; // Terminar isso aqui
   }
   void drawRectangle();
private:
   int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
   int colorId;
   int StippleId;
};

// Function to draw a rectangle.
void Rectangle::drawRectangle()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   setStipple(this->StippleId);
   setColor(this->colorId);
   glRectf(x1, y1, x2, y2);
   glDisable(GL_LINE_STIPPLE);
}

// Vector of rectangles.
vector<Rectangle> rectangles;

// Iterator to traverse a Rectangle array.
vector<Rectangle>::iterator rectanglesIterator;

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
   // Loop through the rectangles array drawing each rectangle.
   rectanglesIterator = rectangles.begin();
   while(rectanglesIterator != rectangles.end() )
   {
      rectanglesIterator->drawRectangle();
	  rectanglesIterator++;
   }
}

// Function to draw point selection box in left selection area.
void drawPointSelectionBox(void)
{  
   if (primitive == POINT) glColor3f(1.0, 1.0, 1.0); // Highlight.
   else glColor3f(0.8, 0.8, 0.8); // No highlight.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.9*height, 0.1*width, height);

   // Draw black boundary.
   glColor3f(0.0, 0.0, 0.0); 
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.9*height, 0.1*width, height); 

   // Draw point icon.
   glPointSize(pointSize);
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_POINTS);
      glVertex3f(0.05*width, 0.95*height, 0.0);
   glEnd();  
}

// Function to draw line selection box in left selection area.
void drawLineSelectionBox(void)
{  
   if (primitive == LINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
   else glColor3f(0.8, 0.8, 0.8); // No highlight.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

   // Draw black boundary.
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

   // Draw line icon.
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_LINES);
      glVertex3f(0.025*width, 0.825*height, 0.0);
      glVertex3f(0.075*width, 0.875*height, 0.0);
   glEnd();  
}

// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionBox(void)
{  
   if (primitive == RECTANGLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
   else glColor3f(0.8, 0.8, 0.8); // No highlight.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

   // Draw black boundary.
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

   // Draw rectangle icon.
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.025*width, 0.735*height, 0.075*width, 0.765*height);
   glEnd();  
}

void drawBissetrizSelectionBox(void)
{  
   if (primitive == BISSETRIZ) glColor3f(1.0, 1.0, 1.0); // Highlight.
   else glColor3f(0.8, 0.8, 0.8); // No highlight.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

   // Draw black boundary.
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

   // Draw BISSETRIZ icon. - Trocar dps
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_LINES);
      glVertex3f(0.025*width, 0.625*height, 0.0);
      glVertex3f(0.025*width, 0.665*height, 0.0);
      glVertex3f(0.025*width, 0.665*height, 0.0);
      glVertex3f(0.075*width, 0.665*height, 0.0);

      //Linha bissetriz
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0.025*width, 0.665*height, 0.0);
      glVertex3f(width * 0.0532, height * 0.6367, 0.0);
   glEnd();
   glColor3f(0.0, 0.0, 0.0);
}

void drawTextSelectionBox(void)
{  
   if (primitive == TEXT) glColor3f(1.0, 1.0, 1.0); // Highlight.
   else glColor3f(0.8, 0.8, 0.8); // No highlight.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

   // Draw black boundary.
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

   //Draw TEXT icon. - Trocar dps
   glColor3f(0.0, 0.0, 0.0);
   glRasterPos3f(0.025*width, 0.545*height, 0.0);
   writeBitmapString((void*)font, (char*)"TEXT");
}

// Function to draw unused part of left selection area.
void drawInactiveArea(void)
{
   glColor3f(0.6, 0.6, 0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.0, 0.1*width, (1-NUMBERPRIMITIVES*0.1)*height);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.0, 0.1*width, (1-NUMBERPRIMITIVES*0.1)*height);
}

// Function to draw temporary point.
void drawTempPoint(void)
{
   glColor3f(1.0, 0.0, 0.0);
   glPointSize(pointSize);
   glBegin(GL_POINTS);
      glVertex3f(tempX, tempY, 0.0);
      if(pointCount == 2)
      glVertex3f(tempX2, tempY2, 0.0);
   glEnd(); 
}

// Function to draw a grid.
void drawGrid(void)
{   
   glEnable(GL_LINE_STIPPLE);
   glLineStipple(1, 0x5555); 
   glColor3f(0.75, 0.75, 0.75);

   glBegin(GL_LINES);
	  for (float x = 0.1 + gridSlice; x  <= 1.0; x += gridSlice)
	  {
         glVertex3f(x*width, 0.0, 0.0);
         glVertex3f(x*width, height, 0.0);
	  }
	  for (float y = gridSlice; y  <= 1.0; y += gridSlice)
	  {   
         glVertex3f(0.1 * width, y * height, 0.0);
         glVertex3f(width, y*height, 0.0);
	  }
   glEnd();
   glDisable(GL_LINE_STIPPLE);
}


// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0); 

   drawBissetrizes(); //Importante essa linha ser chamado antes do desenho da barra lateral
   //currentBissetriz.drawBissetriz();
   
   drawPointSelectionBox();
   drawLineSelectionBox();
   drawRectangleSelectionBox();
   drawBissetrizSelectionBox();
   drawTextSelectionBox();
   drawInactiveArea();
   
   //color_menu(currentcolor);

   drawPoints();
   drawLines();
   drawRectangles();
   drawText();

   if (
      (
          ((primitive == LINE) || (primitive == RECTANGLE)) && (pointCount == 1)
      ) || 
      (
          (primitive == BISSETRIZ) && ((pointCount == 1) || (pointCount == 2))
      )
      ) 
      {
      drawTempPoint();
      }
   if (isGrid) drawGrid();
   glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
   if ( y < (1- NUMBERPRIMITIVES*0.1)*height ) primitive = INACTIVE;
   else if ( y < (1 - 4*0.1)*height ) primitive = TEXT; 
   else if ( y < (1 - 3*0.1)*height ) primitive = BISSETRIZ; 
   else if ( y < (1 - 2*0.1)*height ) primitive = RECTANGLE;
   else if ( y < (1 - 1*0.1)*height ) primitive = LINE;
   else primitive = POINT;
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
   // Update the location of the current point as the mouse moves with button pressed.
   currentBissetriz.setCoords(x, height - y);
   glutPostRedisplay();
}



void primitiveBissetriz(int x, int y, int button, int state){

}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      y = height - y; // Correct from mouse to OpenGL co-ordinates.

	  // Click outside canvas - do nothing.
      if ( x < 0 || x > width || y < 0 || y > height ) ;

	  // Click in left selection area.
      else if ( x < 0.1*width ) 
	  {
	     pickPrimitive(y);
		 pointCount = 0;
	  }

	  // Click in canvas.
      else
	  {
	     if (primitive == POINT) points.push_back( Point(x,y, currentcolor));
         else if (primitive == LINE) 
		 { 
	        if (pointCount == 0)
			{
               tempX = x; tempY = y;
		       pointCount++;
			}
	        else 
			{
               lines.push_back( Line(tempX, tempY, x, y, currentcolor, currentStipple) );
		       pointCount = 0;
			}
		 }
         else if (primitive == RECTANGLE) 
		 { 
	        if (pointCount == 0)
			{
               tempX = x; tempY = y;
		       pointCount++;
			}
	        else 
			{
               rectangles.push_back( Rectangle(tempX, tempY, x, y, currentcolor, currentStipple) );
		       pointCount = 0;
			}
		 }
         else if (primitive == BISSETRIZ)
       {
         
         
         auto currentTime = high_resolution_clock::now();
         auto duration = duration_cast<milliseconds>(currentTime - lastClickTime).count();
      
         if (duration < 250) //Se for double click
         {
            bool found = false;
            Line* clickedLine = nullptr;
      
            for (Line& line : lines) {
                if (isNearLine(line, x, y)) {
                  clickedLine = &line;
                  found = true;
                  break;
                }
            }
        
            if (!found) {
                cout << "Nenhuma linha próxima encontrada." << endl;
                pointCount = 0;
                selectedLine1 = nullptr;
                selectedLine2 = nullptr;
            }
      
            if(pointCount == 2 && found && selectedLine1 != clickedLine){ // para nao selecionar 2x a mesma linha
               //Pegou segunda linha
               selectedLine2 = clickedLine;
               //cout << "Segunda linha selecionada!" << endl;
      
               // Calcular interseção (P2)
               float x1 = selectedLine1->getX1(), y1 = selectedLine1->getY1(); 
               float x2 = selectedLine1->getX2(), y2 = selectedLine1->getY2();
               float x3 = selectedLine2->getX1(), y3 = selectedLine2->getY1();
               float x4 = selectedLine2->getX2(), y4 = selectedLine2->getY2();
      
               float denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
      
               if (denom == 0) {
                   cout << "As linhas são paralelas ou coincidentes. Não há interseção." << endl;
               } else {
                  float Px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
                  float Py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;
              
                  //Função lambda para verificar se dois pontos são iguais (com tolerância)
                  auto isSamePoint = [](float ax, float ay, float bx, float by, float tol = 1.0f) {
                      return hypot(ax - bx, ay - by) < tol;
                  };
              
                  // P1 = ponto da primeira linha que não é P2
                  float p1x = isSamePoint(x1, y1, Px, Py) ? x2 : x1;
                  float p1y = isSamePoint(x1, y1, Px, Py) ? y2 : y1;
              
                  // P3 = ponto da segunda linha que não é P2
                  float p3x = isSamePoint(x3, y3, Px, Py) ? x4 : x3;
                  float p3y = isSamePoint(x3, y3, Px, Py) ? y4 : y3;
              
                  //cout << "P1: (" << p1x << ", " << p1y << ")" << endl;
                  //cout << "P2 (Interseção): (" << Px << ", " << Py << ")" << endl;
                  //cout << "P3: (" << p3x << ", " << p3y << ")" << endl;
                  bissetriz.push_back( Bissetriz(p1x, p1y, Px, Py, p3x, p3y, currentcolor, currentStipple, 0));
                  pointCount = 0;
               }
               pointCount = 0;
               selectedLine1 = nullptr;
               selectedLine2 = nullptr;  
            }else if(found){
               //cout << "Primeira Linha" << random() << endl;
               selectedLine1 = clickedLine;
               //cout << "P1: (" << selectedLine1->getX1() << ", " << selectedLine1->getY1() << ") ";
               //cout << "P2: (" << selectedLine1->getX2() << ", " << selectedLine1->getY2() << ")" << endl;      
               //Pegou primeira linha
            }
         }
         else //Clique normal segue lógica dos pontos
         {
            if (pointCount == 0){
               tempX = x; tempY = y;
               pointCount++;
            }
            else if (pointCount == 2) 
            {
               currentBissetriz = Bissetriz(tempX, tempY, tempX2, tempY2, x, y, currentcolor, currentStipple, 1);  
               pointCount++;
            
            }
            else {
               tempX2 = x; tempY2 = y;   
               pointCount++;
            }
         }
         lastClickTime = currentTime;
       }

       else if (primitive == TEXT)
       {
         string textIn;
         cout << "Digite o texto: " << endl;
         getline(std::cin, textIn); 
         text.push_back( Text(x,y,textIn, currentcolor));
       }
	  }
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && primitive == BISSETRIZ && pointCount > 2){
      cout << "Teste "  << random() << endl; //PROBLEMA AQUI
      bissetriz.push_back(currentBissetriz);
      pointCount = 0;
   }
   glutPostRedisplay();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h;  

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
   points.clear();
   lines.clear();
   rectangles.clear();
   bissetriz.clear();
   text.clear();
   currentBissetriz = Bissetriz();
   primitive = INACTIVE;
   pointCount = 0;
}

// The right button menu callback function.
void rightMenu(int id)
{
   if(id==7){
      currentStipple++;
      if(currentStipple > 4){
         currentStipple = 0;
      }
      //cout << currentStipple << endl;
   }
   if (id==1) 
   {
	  clearAll();
	  glutPostRedisplay();
   }
   if (id==2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
   if (id==3) isGrid = 1;
   if (id==4) isGrid = 0;
   glutPostRedisplay();
}

void changeColor(int id)
{
   currentcolor = id;
}

void gridUpdate(int id){
   if (id==4) 
      if (gridSlice >= 0.1)   
         gridSlice -= 0.05;

      if (id==3) 
         if(gridSlice < 0.5)
            gridSlice += 0.05;
   glutPostRedisplay();
}

// Function to create menu.
void makeMenu(void)
{
   int sub_menu, sub_menu_color, sub_menu_grid;
   sub_menu = glutCreateMenu(grid_menu);
   glutAddMenuEntry("On", 3);
   glutAddMenuEntry("Off",4);

   sub_menu_color = glutCreateMenu(changeColor);
   glutAddMenuEntry("Red", 3);
   glutAddMenuEntry("Blue",4);
   glutAddMenuEntry("Black",5);

   sub_menu_grid = glutCreateMenu(gridUpdate);
   glutAddMenuEntry("+", 3);
   glutAddMenuEntry("-", 4);

   glutCreateMenu(rightMenu);
   glutAddSubMenu("Grid", sub_menu);
   glutAddSubMenu("Color", sub_menu_color);
   glutAddSubMenu("Grid", sub_menu_grid);
   glutAddMenuEntry("Stipple", 7);
   glutAddMenuEntry("Clear",1);
   glutAddMenuEntry("Quit",2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Left click on a box on the left to select a primitive." << endl
        << "Then left click on the drawing area: once for point, twice for line or rectangle." << endl
        << "Right click for menu options." <<  endl; 
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("canvas.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl); 

   glutMotionFunc(mouseMotion);

   makeMenu(); // Create menu.

   glutMainLoop(); 

   return 0;  
}
