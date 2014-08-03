float[] Dx, Dy;
int MaxFrame;

int set;

int size_x = 1280;
int size_y = 800;

void setup()
{
  noStroke();
  frameRate(20);
  
  size(size_x, size_y);
  String[] List = loadStrings("/home/pero/Documents/Take2/out.txt");
  String[] Set = loadStrings("/home/pero/Documents/Take2/setup.txt");
  
  set = int(Set[0]);
    
  Dx = new float[List.length];
  Dy = new float[List.length];
  
  float[] Pair;
  for(int i = 0; i < List.length; i++)
  {
    String s = List[i];
    Pair = float(split(s, "\t"));
    Dx[i] = Pair[0] ;
    Dy[i] = Pair[1];
  }
  
  MaxFrame = (List.length/set) - 1;
  
}

void draw()
{
  int MyFrame; 
  background(0);
  
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
} 
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
  
  float Scale = 0.45 * height/MaxDist;
  
  float r = 25 * 3e19 * 0.04 * Scale;
  r = max(r, 2);
  
  for(int i = MyFrame * set; i < (MyFrame + 1) * set; i++)
  {
    ellipse(Dx[i]*Scale + width/2, Dy[i]*Scale + height/2, r, r);
  }   
}
