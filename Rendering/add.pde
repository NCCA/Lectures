int xspacing = 1;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave

float theta = 0.0;  // Start angle at 0
float amplitude = 25.0;  // Height of wave
<<<<<<< HEAD
float periodRed =199-110.0;  // How many pixels before the wave repeats
float periodGreen =199-60.0;  // How many pixels before the wave repeats
float periodBlue =199-10.0;  // How many pixels before the wave repeats
=======
float periodRed =50.0;  // How many pixels before the wave repeats
float periodGreen =80.0;  // How many pixels before the wave repeats
float periodBlue =100.0;  // How many pixels before the wave repeats
>>>>>>> d7bb3bf3e385f6ce7c99bede53d000b4f5c594b4
float dxRed;  // Value for incrementing X, a function of period and xspacing
float dxGreen;  // Value for incrementing X, a function of period and xspacing
float dxBlue;  // Value for incrementing X, a function of period and xspacing
float[] yvaluesRed;  // Using an array to store height values for the wave
float[] yvaluesGreen;  // Using an array to store height values for the wave
float[] yvaluesBlue;  // Using an array to store height values for the wave
PFont f;

void setup() 
{
  size(1024, 500, P3D);
  //noStroke();
    f = createFont( "Arial", 12);

  w = width+16;
  dxRed= (TWO_PI / periodRed) ;
  dxGreen= (TWO_PI / periodGreen) ;
  dxBlue= (TWO_PI / periodBlue) ;
  yvaluesRed = new float[200];
  yvaluesGreen = new float[200];
  yvaluesBlue = new float[200];
}

void updateRed(int value)
{
  periodRed=199-(float)value;
  dxRed = (TWO_PI / periodRed) ;

}


void updateGreen(int value)
{
  periodGreen=199-(float)value;
  dxGreen = (TWO_PI / periodGreen) ;

}
void updateBlue(int value)
{
  periodBlue=199-(float)value;
  dxBlue = (TWO_PI / periodBlue) ;
}


void drawRed()
{
  pushMatrix();
  translate(-90,-60,0);
  strokeWeight(4,4,4);
  stroke(0, 0, 0);
  beginShape(LINES);
  vertex(-100, 0, 0);
  vertex(100, 0, 0);
  vertex(95, 2, 0);
  vertex(100, 0, 0);
  vertex(95, -2, 0);
  vertex(100, 0, 0); 
  endShape();
  // A simple way to draw the wave with an ellipse at each location
  stroke(0, 0, 255);
  beginShape(LINES);
  for (int x = 0; x < yvaluesRed.length-1; x++) 
  {
    vertex(-100+x*xspacing, yvaluesRed[x], 0);
    vertex(-100+x+1*xspacing, yvaluesRed[x+1], 0);
  }
  endShape();

  stroke(255, 0, 0);
  beginShape(LINES);
  for (int x = 0; x < yvaluesRed.length-1; x++) 
  {
    vertex(-100+x*xspacing, 0, yvaluesRed[x]);
    vertex(-100+x+1*xspacing, 0, yvaluesRed[x+1]);
  }
  endShape();
  popMatrix();

}


void drawGreen()
{
  pushMatrix();
  translate(-90,0,0);
  strokeWeight(4,4,4);
  stroke(0, 0, 0);
  beginShape(LINES);
  vertex(-100, 0, 0);
  vertex(100, 0, 0);
  vertex(95, 2, 0);
  vertex(100, 0, 0);
  vertex(95, -2, 0);
  vertex(100, 0, 0); 
  endShape();
  // A simple way to draw the wave with an ellipse at each location
  stroke(0, 0, 255);
  beginShape(LINES);
  for (int x = 0; x < yvaluesGreen.length-1; x++) 
  {
    vertex(-100+x*xspacing, yvaluesGreen[x], 0);
    vertex(-100+x+1*xspacing, yvaluesGreen[x+1], 0);
  }
  endShape();

  stroke(255, 0, 0);
  beginShape(LINES);
  for (int x = 0; x < yvaluesGreen.length-1; x++) 
  {
    vertex(-100+x*xspacing, 0, yvaluesGreen[x]);
    vertex(-100+x+1*xspacing, 0, yvaluesGreen[x+1]);
  }
  endShape();
  popMatrix();

}

void drawBlue()
{
  pushMatrix();
  translate(-90,60,0);
  strokeWeight(4,4,4);
  stroke(0, 0, 0);
  beginShape(LINES);
  vertex(-100, 0, 0);
  vertex(100, 0, 0);
  vertex(95, 2, 0);
  vertex(100, 0, 0);
  vertex(95, -2, 0);
  vertex(100, 0, 0); 
  endShape();
  // A simple way to draw the wave with an ellipse at each location
  stroke(0, 0, 255);
  beginShape(LINES);
  for (int x = 0; x < yvaluesBlue.length-1; x++) 
  {
    vertex(-100+x*xspacing, yvaluesBlue[x], 0);
    vertex(-100+x+1*xspacing, yvaluesBlue[x+1], 0);
  }
  endShape();

  stroke(255, 0, 0);
  beginShape(LINES);
  for (int x = 0; x < yvaluesBlue.length-1; x++) 
  {
    vertex(-100+x*xspacing, 0, yvaluesBlue[x]);
    vertex(-100+x+1*xspacing, 0, yvaluesBlue[x+1]);
  }
  endShape();
  popMatrix();

}


void drawSum()
{
  pushMatrix();
  translate(-90,20,-200);
  strokeWeight(4,4,4);
  stroke(0, 0, 0);
  beginShape(LINES);
  vertex(-100, 0, 0);
  vertex(100, 0, 0);
  vertex(95, 2, 0);
  vertex(100, 0, 0);
  vertex(95, -2, 0);
  vertex(100, 0, 0); 
  endShape();
  // A simple way to draw the wave with an ellipse at each location
  stroke(0, 0, 255);
  beginShape(LINES);
  for (int x = 0; x < yvaluesBlue.length-1; x++) 
  {
    vertex(-100+x*xspacing, yvaluesRed[x]+yvaluesGreen[x]+yvaluesBlue[x], 0);
    vertex(-100+x+1*xspacing, yvaluesRed[x+1]+yvaluesGreen[x+1]+yvaluesBlue[x+1], 0);
  }
  endShape();

  stroke(255, 0, 0);
  beginShape(LINES);
  for (int x = 0; x < yvaluesBlue.length-1; x++) 
  {
    vertex(-100+x*xspacing, 0, yvaluesRed[x]+yvaluesGreen[x]+yvaluesBlue[x]);
    vertex(-100+x+1*xspacing, 0, yvaluesRed[x+1]+yvaluesGreen[x+1]+yvaluesBlue[x+1]);
  }
  endShape();
  popMatrix();

}




void draw()
{
  
  perspective(radians(45.0), float(width/height), 0.1, 1000);
  camera(200, -100, 100, 0, 0, 0, 0, 1, 0);
  background(255);
  calcWave();
  drawRed();
  drawGreen();
  drawBlue();
  drawSum();

  pushMatrix();
  camera();
  perspective();
  textFont(f);
  textMode(MODEL);
  textSize(32);
  textAlign(LEFT);
  hint(DISABLE_DEPTH_TEST);
  fill(255, 0, 0);
  text("Red Laser", 40,100);
  fill(0, 255, 0);
  text("Green Laser", 40,200);
  fill(0, 0, 255);
  text("Blue Laser", 40,300);
  fill(0, 0, 0);
  text("Sum", 700,300);

  hint(ENABLE_DEPTH_TEST);
  popMatrix();
}


void calcWave() 
{
  // Increment theta (try different values for 'angular velocity' here
  theta += 0.02;
  // For every x value, calculate a y value with sine function
  float x = theta;
  for (int i = 0; i < yvaluesRed.length; i++) {
    yvaluesRed[i] = sin(x)*amplitude;
    x+=dxRed;
  }
  x = theta;
  for (int i = 0; i < yvaluesGreen.length; i++) {
    yvaluesGreen[i] = sin(x)*amplitude;
    x+=dxGreen;
  }
<<<<<<< HEAD
  x = theta;
=======
    x = theta;
>>>>>>> d7bb3bf3e385f6ce7c99bede53d000b4f5c594b4
  for (int i = 0; i < yvaluesBlue.length; i++) {
    yvaluesBlue[i] = sin(x)*amplitude;
    x+=dxBlue;
  }

}
