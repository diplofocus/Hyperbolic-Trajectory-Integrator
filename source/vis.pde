float[] Dx, Dy, parent;
int MaxFrame;

int set;

int size_x = 1280;
int size_y = 800;

float ZoomFactor = 1;

float MaxZF = 10;
float MinZF = 0.05;

float OffsetX, OffsetY;
float OffsetSpeed = 20;
  
void setup()
{
  noStroke();
  frameRate(20);
  
  size(size_x, size_y);
  String[] List = loadStrings("/home/pero/Documents/Galaxy/out.txt");
  String[] Set = loadStrings("/home/pero/Documents/Galaxy/setup.txt");
  
  set = int(Set[0]);
    
  Dx = new float[List.length];
  Dy = new float[List.length];
  parent = new float[List.length];
  
  float[] Pair;
  for(int i = 0; i < List.length; i++)
  {
    String s = List[i];
    Pair = float(split(s, "\t"));
    Dx[i] = Pair[0] ;
    Dy[i] = Pair[1];
    parent[i] = Pair[2];
  }
  
  MaxFrame = (List.length/set) - 1;
  
}

void draw()
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
  
  float Scale = 0.45 * height/min(MaxDist, 1e22);
  
  Scale = Scale * ZoomFactor;
  
  float r = 25 * 3e19 * 0.04 * Scale;
  r = max(r, 2);
  
  for(int i = MyFrame * set; i < (MyFrame + 1) * set; i++)
  {
    PerinaElipsa(Dx[i], Dy[i], r, Scale, parent[i]);
  }   
}

void ProcessInput()
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
      ZoomFactor += 0.05;
    }
    
    if(key == 'x')
    {
      ZoomFactor -= 0.05;
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

void PerinaElipsa(float x, float y, float r, float Scale, float parent)
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
