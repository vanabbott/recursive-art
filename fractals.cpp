// sierpmain.cpp
// main driver to test the Sierpinski fractal
// NOTE:
// you may only use this code if you fully understand how it works.
#include "gfx.h"
#include <cmath>
using namespace std;

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkingSquares(int x, int y, float s);
void drawSquare(int x, int y, float s);
void spiralSquares(int x, int y, float s,float theta);
void circularLace(int x, int y, float r);
void snowflake(int x, int y, float r);
void tree(int x, int y, int x2, int y2, float r ,float theta);
void fern(int x, int y, float r, float theta);
void bigSpiral(int x, int y, float r, float theta);
void spiral(int x, int y, float r, float theta);

int main()
{
		char c;
		int width = 700, height = 700, mrgn = 20;

		gfx_open(width, height, "Fractals");
		while(c!='q') {
				gfx_clear();
				switch(c){
						case '1':
								sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
								break;
						case '2':
								shrinkingSquares(width/2,height/2,(float)width/2);
								break;
						case '3':
								spiralSquares(width/2,height/2, (float)width/6, 0);
								break;
						case '4':
								circularLace(width/2,height/2, (float)width/3);
								break;
						case '5':
								snowflake(width/2,height/2, (float)width/3);
								break;
						case '6':
								tree(width/2,height,width/2,height*2/3,height/4,M_PI/2);
								break;
						case '7':
								fern(width/2,height,height*5/8,M_PI/2);
								break;
						case '8':
								bigSpiral(width/2,height/2,(float)width*4/8,0);
								break;	
				}
				//if(gfx_event_waiting()){
				c = gfx_wait();
				//}	
		}
}


void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case. 
		if( abs(x2-x1) < 5 ) return;

  // Draw the triangle
		drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
		sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
		sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
		sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
		gfx_line(x1,y1,x2,y2);
		gfx_line(x2,y2,x3,y3);
		gfx_line(x3,y3,x1,y1);
}

void shrinkingSquares(int x, int y, float s){
		if(s<0.5)return;

		drawSquare(x,y,s);

		shrinkingSquares(x+s/2,y+s/2,s*5/12);
		shrinkingSquares(x+s/2,y-s/2,s*5/12);
		shrinkingSquares(x-s/2,y+s/2,s*5/12);
		shrinkingSquares(x-s/2,y-s/2,s*5/12);
		

}
void drawSquare(int x, int y, float s){
		gfx_line(x+s/2,y+s/2,x-s/2,y+s/2);
		gfx_line(x+s/2,y-s/2,x-s/2,y-s/2);
		gfx_line(x+s/2,y+s/2,x+s/2,y-s/2);
		gfx_line(x-s/2,y+s/2,x-s/2,y-s/2);
		
}

void spiralSquares(int x, int y, float s, float theta){
		if(s<1)return;
		drawSquare(x+cos(theta*M_PI/180)*3*s, y+sin(theta*M_PI/180)*3*s,s);
		spiralSquares(x,y,s*0.9,theta+36);
}

void circularLace(int x, int y, float r){
		if(r<0.5)return;
		
		gfx_circle(x,y,r);
		
		for(int i = 0; i <6; i++){
				circularLace(x+cos(i*M_PI/3)*r,y+sin(i*M_PI/3)*r,r/3);
		}
}
void snowflake(int x, int y, float r){
		if(r<0.5)return;
		
		for(int i = 0; i <5; i++){
				gfx_line(x,y,x+cos((i*72*M_PI/180)-(M_PI/2))*r,y+sin((i*72*M_PI/180)-(M_PI/2))*r);
				snowflake(x+cos((i*72*M_PI/180)-(M_PI/2))*r, y+sin((i*72*M_PI/180)-(M_PI/2))*r,r/3);
		}
		
}

void tree(int x, int y, int x2, int y2, float r ,float theta){
		if(r<1)return;
		gfx_line(x,y,x2,y2);

		for(int i = 1; i<=2; i++){
				
				tree(x2, y2, x2+cos((theta-M_PI/2)+(i*60*M_PI/180))*r, y2-sin((theta-M_PI/2)+(i*60*M_PI/180))*r, r*0.65,theta+pow(-1,i)*M_PI/6);
		}
}

void fern(int x, int y, float r, float theta){
		if(r<1)return;
		
		gfx_line(x,y,x-cos(theta)*r,y-sin(theta)*r);
		//gfx_line(x,y,x-cos(theta)*r,y-sin(theta)*r);

		for(int i = 1; i<=4;i++){
				fern(x-cos(theta)*(r/4)*i, y-sin(theta)*(r/4)*i,r/3,theta-M_PI/6);
				fern(x-cos(theta)*(r/4)*i, y-sin(theta)*(r/4)*i,r/3,theta+M_PI/6);
		}
}

void bigSpiral(int x, int y, float r, float theta){
		if(r<0.1)return;
		spiral(x+cos(theta)*r,y+sin(theta)*r,r*0.6,theta);
		bigSpiral(x,y,r*0.9, theta+(M_PI+0.1)/5);

}
void spiral(int x, int y, float r, float theta){
		if(r<0.1)return;
		gfx_point(x+cos(theta)*r,y+sin(theta)*r);
		bigSpiral(x,y,r*0.6,theta+(M_PI+0.1)/5);
}


