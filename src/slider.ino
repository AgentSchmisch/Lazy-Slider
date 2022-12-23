void slider(){
  //redirect to the slider menu page
  redirect("/slider.html");
  //get the returned values for the slider
  if(server.hasArg("direction"))
    String direction=server.arg("direction");

  String speed=server.arg("speed");
  String time=server.arg("time");
  
  
  
  //set the pins for the variables and whether they are in- or output pins
  int endstop1=9;
  int endstop2=10;
  pinMode(endstop1,INPUT_PULLUP);
  pinMode(endstop2,INPUT_PULLUP);

  






}