import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class vis extends PApplet {

float[] Dx, Dy, parent;
int MaxFrame;

int set;

int size_x = 1280;
int size_y = 800;

float ZoomFactor = 1;

float MaxZF = 10;
float MinZF = 0.05f;

float OffsetX, OffsetY;
float OffsetSpeed = 20;
  
public void setup()
{
  noStroke();
  frameRate(20);
  
  size(size_x, size_y);
  String[] List = loadStrings("/home/pero/Documents/Galaxy/out.txt");
  String[] Set = loadStrings("/home/pero/Documents/Galaxy/setup.txt");
  
  set = PApplet.parseInt(Set[0]);
    
  Dx = new float[List.length];
  Dy = new float[List.length];
  parent = new float[List.length];
  
  float[] Pair;
  for(int i = 0; i < List.length; i++)
  {
    String s = List[i];
    Pair = PApplet.parseFloat(split(s, "\t"));
    Dx[i] = Pair[0] ;
    Dy[i] = Pair[1];
    parent[i] = Pair[2];
  }
  
  MaxFrame = (List.length/set) - 1;
  
}

public void draw()
{
  int MyFrame;

  background(0);
  ProcessInput();  

  ZoomFactor = constrain(ZoomFactor, MinZF, MaxZF);

  MyFrame = frameCount % MaxFrame;
  
  //MyFrame = min(frameCount, MaxFrame);
  
  
  float MaxDist = 0;
  for(int i = MyFrame * set; i < (MyFrame + 1) * set; i++)
  {
    float Dist = max(abs(Dx[i]), abs(Dy[i]));
    if(Dist > MaxDist)
    {
      MaxDist = Dist;
    }
  }
  
  float Scale = 0.45f * height/min(MaxDist, 1e22f);
  
  Scale = Scale * ZoomFactor;
  
  float r = 25 * 3e19f * 0.04f * Scale;
  r = max(r, 2);
  
  for(int i = MyFrame * set; i < (MyFrame + 1) * set; i++)
  {
    PerinaElipsa(Dx[i], Dy[i], r, Scale, parent[i]);
  }   
}

public void ProcessInput()
{
      if(keyPressed)
  {  
    if(key == 'r')
    {
      frameCount = 0;
    }
  
    if(key == 'f')
    {
      frameCount += 10;
    }
    else
    {
      frameCount++;
    }
    
    if(key == 'z')
    {
      ZoomFactor += 0.05f;
    }
    
    if(key == 'x')
    {
      ZoomFactor -= 0.05f;
    }
    
    if(key == 'a')
    {
      OffsetX += OffsetSpeed;
    }
        
    if(key == 'd')
    {
      OffsetX -= OffsetSpeed;
    }
        
    if(key == 'w')
    {
      OffsetY += OffsetSpeed;
    }
        
    if(key == 's')
    {
      OffsetY -= OffsetSpeed;
    }
    
    if(key == 'q')
    {
      OffsetX = 0;
      OffsetY = 0; 
    }
    
    if(key == 'e')
    {
      ZoomFactor = 0;
    }
  }
}

public void PerinaElipsa(float x, float y, float r, float Scale, float parent)
{
  if(parent == 1)
    fill(255, 0 , 0);
  else
  {
    if(parent == 2)
    {
      fill(0, 255, 0);
    }
    else
    {
      fill(0, 0, 255);
    }
  }  
  ellipse(x*Scale + width/2 + OffsetX, y*Scale + height/2 + OffsetY, r, r);
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "vis" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
