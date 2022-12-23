// functions for the turntable
//TODO: change the library from <stepper.h> to the A4988 library

void turntable(){
  redirect("/turntable.html");
  if(server.hasArg("direction"))
  String direction=server.arg("direction");


  String speed=server.arg("speed");
  String time=server.arg("time");
  stepper.setspeed(int(speed)*(int(time)*60));
  
  if(direction=="right")
    stepper.step(-500);
  
  else
  stepper.step(500);


}

