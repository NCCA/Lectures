int xspacing = 1;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave

float theta = 0.0;  // Start angle at 0
float amplitude = 25.0;  // Height of wave
float period =50.0;  // How many pixels before the wave repeats
float dx;  // Value for incrementing X, a function of period and xspacing
float[] yvalues;  // Using an array to store height values for the wave
PFont f;

void setup() 
{
  size(1024, 400, P3D);
  //noStroke();
  
  w = width+16;
  dx = (TWO_PI / period) ;
  yvalues = new float[200];
      f = createFont( "Arial", 12);
}

void updateValue(int value)
{
  period=199-(float)value;
  dx = (TWO_PI / period) ;

}

void draw() 
{
  
  camera(200, -30, 100, 0, 0, 0, 0, 1, 0);
  perspective(radians(45.0), float(width/height), 0.1, 1000);
  background(255);
  calcWave();
  pushMatrix();
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
  popMatrix();
  // A simple way to draw the wave with an ellipse at each location
  stroke(0, 0, 255);
  beginShape(LINES);
  for (int x = 0; x < yvalues.length-1; x++) 
  {
    vertex(-100+x*xspacing, yvalues[x], 0);
    vertex(-100+x+1*xspacing, yvalues[x+1], 0);
  }
  endShape();

  stroke(255, 0, 0);
  beginShape(LINES);
  for (int x = 0; x < yvalues.length-1; x++) 
  {
    vertex(-100+x*xspacing, 0, yvalues[x]);
    vertex(-100+x+1*xspacing, 0, yvalues[x+1]);
  }
  endShape();



  pushMatrix();
  camera();
  perspective();
  textFont(f);
  textMode(MODEL);
  textSize(22);
  textAlign(LEFT);
  hint(DISABLE_DEPTH_TEST);
  fill(255, 0, 0);
  text("Electric Wave", 40,100);
  fill(0,0, 255);
  text("Magnetic Wave", 40,150);

  hint(ENABLE_DEPTH_TEST);
  popMatrix();
  
}


void calcWave() 
{
  // Increment theta (try different values for 'angular velocity' here
  theta += 0.02;
  // For every x value, calculate a y value with sine function
  float x = theta;
  for (int i = 0; i < yvalues.length; i++) {
    yvalues[i] = sin(x)*amplitude;
    x+=dx;
  }
}
