import processing.serial.*;

Serial myPort;
float currentAngle = 0;
float currentDistance = 0;

ArrayList<Float> dotX_list = new ArrayList<Float>();
ArrayList<Float> dotY_list = new ArrayList<Float>();
ArrayList<Integer> dotTime_list = new ArrayList<Integer>();

void setup() {
  size(600, 600);
  myPort = new Serial(this, "COM4", 9600);
}

void draw() {
  noStroke();
  fill(0, 25);
  rect(0, 0, 600, 600);

  noFill();
  stroke(0, 100, 0);
  ellipse(300, 600, 125, 125);
  ellipse(300, 600, 250, 250);
  ellipse(300, 600, 375, 375);
  ellipse(300, 600, 500, 500);

  stroke(0, 100, 0);
  for (int a = 0; a <= 180; a += 45) {
    float markRad = radians(a);
    float mx = 300 + 250 * cos(markRad);
    float my = 600 - 250 * sin(markRad);
    line(300, 600, mx, my);
  }

  for (int i = 0; i < 30; i++) {
    float trailAngle = currentAngle - i * 0.5;
    float alpha = map(i, 0, 30, 255, 0);
    stroke(0, 255, 0, alpha);
    float tRad = radians(trailAngle);
    float tx = 300 + 250 * cos(tRad);
    float ty = 600 - 250 * sin(tRad);
    line(300, 600, tx, ty);
  }

  for (int j = dotTime_list.size() - 1; j >= 0; j--) {
    int age = millis() - dotTime_list.get(j);
    if (age > 1500) {
      dotX_list.remove(j);
      dotY_list.remove(j);
      dotTime_list.remove(j);
    } else {
      float dotAlpha = map(age, 0, 1500, 255, 0);
      fill(255, 0, 0, dotAlpha);
      noStroke();
      ellipse(dotX_list.get(j), dotY_list.get(j), 8, 8);
    }
  }

  fill(0, 255, 0);
  textSize(16);
  text("Angle: " + currentAngle, 20, 30);
  text("Distance: " + currentDistance + " cm", 20, 55);

  if (myPort.available() > 0) {
    String incoming = myPort.readStringUntil('\n');
    if (incoming != null) {
      String[] parts = split(incoming, ',');
      if (parts.length == 2) {
        currentAngle = float(parts[0]);
        currentDistance = float(parts[1]);

        float pixelRadius = constrain((currentDistance / 100.0) * 250, 0, 250);
        float newRad = radians(currentAngle);
        float newDotX = 300 + pixelRadius * cos(newRad);
        float newDotY = 600 - pixelRadius * sin(newRad);
        dotX_list.add(newDotX);
        dotY_list.add(newDotY);
        dotTime_list.add(millis());
      }
    }
  }
}
