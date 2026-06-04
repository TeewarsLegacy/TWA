// Persistence of Vision Ray Tracer Scene Description File
// File: logo.pov
// Vers: 3.5
// Desc: Logo of Teewars Legacy
// Date: 02/14/2026
// Auth: Mykyta Polishyk
//

#version 3.5;



#include "colors.inc"

global_settings {
  assumed_gamma 1.0
}

// ----------------------------------------

camera {
  location  <0.0, 0, -4.0>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
}  

light_source {
  <0, 0, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <-30, 30, -30>
}

// ----------------------------------------
                            
// Logo text
// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "comic.ttf",  // Microsoft Windows-format TrueType font file name
  "Teewars",      // the string to create
  2,              // the extrusion depth
  0               // inter-character spacing 
  texture {
            pigment {
              rgb <0.7,0.7,0.8>
            }
            finish{
              specular 0.6 
              reflection 1
            }
          }     
  rotate <sin(clock)*2, sin(clock)*2.5,0>  
  translate <-1.95, 0, 0>
}
     
text {
  ttf             // font type (only TrueType format for now)
  "comic.ttf",  // Microsoft Windows-format TrueType font file name
  "Legacy",      // the string to create
  2,              // the extrusion depth
  0               // inter-character spacing 
  texture {
            pigment {
              rgb <0.5,0.5,0.8>
            }
            finish{
              specular 0.6 
              reflection 1
            }
          }     
  rotate <0, sin(clock)*2.5,sin(clock)*2>  
  translate <-1.55, -1, 0>
}
