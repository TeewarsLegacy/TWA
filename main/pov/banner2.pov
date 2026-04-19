// Persistence of Vision Ray Tracer Scene Description File
// File: banner2.pov
// Vers: 3.5
// Desc: Second banner for Teewars Legacy
// Date: 2026.04.19 
// Auth: Mykyta Polishyk

#version 3.5;

#include "colors.inc"
#include "woods.inc"

global_settings {
  assumed_gamma 1.0
}

camera {
  location  <9, 1, 2>
  direction 1.5*z                               
  look_at   <0.0, 0.0,  1.5>
} 
sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.6,0.7,1.0>]
      [0.25 rgb <0,0,0>]
    }
  }
}

light_source {
  <30, 2, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <30, 30, 30>
}

// ----------------------------------------

plane {
  y, -1
  texture { T_Wood2
            finish { specular 0.5 roughness 0.005 ambient 0.35 }
            translate x*1       
            scale 5
            rotate <30, 10, 20>
        }
}
      
union{          
// Tee body
union{       
      // Head
      sphere {
          <0, 0.5, 0>, 1
          texture {
            pigment {
              gradient y
                    color_map {
                      [0 rgb <0.2,0,0.2>]
                      [1 rgb <0.8,0,0.6>]
                    }
                    scale 3
                    translate <0,-1,0>
            }
            finish{
              specular 0.1
            }
          }
        }  
        sphere {
                <2.15, 0.35, -0.35>, 0.25
                scale <0.45,1.75,0.75> 
                pigment { color rgb <0,0,0> }
                finish { specular 0.25 }
            }
            
                             
        sphere {
          <2.15, 0.35, 0.45>, 0.25
          texture {
            pigment {
              color rgb <0,0,0>
            }
            finish{
              specular 0.25   
            }
          }  
          scale <0.45,1.75,0.75>
        }     
        translate <0, -0.25, 0>
        rotate <0,-10,5>      
}



// Foots
       
// right                
// CSG difference, subtract intersections of shapes 2...N from Shape1
difference {
   sphere {
          <0, 0, 0>, 0.45
          texture {
            pigment {           
              color rgb <0,0.5,0>
            }
            finish{
              specular 0.1
            }
          }               
          scale <1.5,1,1>
        }  
       box{
       <-1, 0.05, -1>                 
       <2,-1,1>                      
          scale <1,1,1> 
          texture {
            pigment {           
              color rgb <0,0.5,0>
            }
            finish{
              specular 0.1
            }
          }  
   }  
   translate <-0.25,-1.05,0.5> 
    
}
            
// left                
// CSG difference, subtract intersections of shapes 2...N from Shape1
difference {
   sphere {
          <0, 0, 0>, 0.45
          texture {
            pigment {           
              color rgb <0,0.5,0>
            }
            finish{
              specular 0.1
            }
          }               
          scale <1.5,1,1>
        }  
       box{
       <-1, 0.05, -1>                 
       <2,-1,1>                      
          scale <1,1,1> 
          texture {
            pigment {           
              color rgb <0,0.5,0>
            }
            finish{
              specular 0.1
            }
          }  
   }  
   translate <-0.25,-1.05,-0.5> 
    
}
}                         

union{          
// Tee body
union{       
      // Head
      sphere {
          <0, 0.5, 0>, 1
          texture {
            pigment {
              gradient y
                    color_map {
                      [0 rgb <0,0.2,0>]
                      [1 rgb <0,0.9,0>]
                    }
                    scale 3
                    translate <0,-1,0>
            }
            finish{
              specular 0.1
            }
          }
        }  
        sphere {
                <2.15, 0.35, -0.35>, 0.25
                scale <0.45,1.75,0.75> 
                pigment { color rgb <0,0,0> }
                finish { specular 0.25 }
            }
            
                             
        sphere {
          <2.15, 0.35, 0.45>, 0.25
          texture {
            pigment {
              color rgb <0,0,0>
            }
            finish{
              specular 0.25   
            }
          }  
          scale <0.45,1.75,0.75>
        }     
        translate <0, -0.25, 0>
        rotate <0,2,5>    
}



// Foots
       
// right                
// CSG difference, subtract intersections of shapes 2...N from Shape1
difference {
   sphere {
          <0, 0, 0>, 0.45
          texture {
            pigment {           
              color rgb <0.9,0.9,0>
            }
            finish{
              specular 0.1
            }
          }               
          scale <1.5,1,1>
        }  
       box{
       <-1, 0.05, -1>                 
       <2,-1,1>                      
          scale <1,1,1> 
          texture {
            pigment {           
              color rgb <0.9,0.9,0>
            }
            finish{
              specular 0.1
            }
          }  
   }  
   translate <-0.25,-1.05,0.5> 
    
}
            
// left                
// CSG difference, subtract intersections of shapes 2...N from Shape1
difference {
   sphere {
          <0, 0, 0>, 0.45
          texture {
            pigment {           
              color rgb <0.9,0.9,0>
            }
            finish{
              specular 0.1
            }
          }               
          scale <1.5,1,1>
        }  
       box{
       <-1, 0.05, -1>                 
       <2,-1,1>                      
          scale <1,1,1> 
          texture {
            pigment {           
              color rgb <0.9,0.9,0>
            }
            finish{
              specular 0.1
            }
          }  
   }  
   translate <-0.25,-1.05,-0.5> 
    
}             
translate <0,0,3>
}     

                                              
// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "crystal.ttf",  // Microsoft Windows-format TrueType font file name
  "ZabidenHTF",      // the string to create
  1,              // the extrusion depth
  0               // inter-character spacing   
  rotate <0,-105,0>            
  scale 0.5
  translate <1, 1.5, -1.2>
  texture {
            pigment {           
              color rgb <0,0,0>
            }
            finish{
              specular 0.1
            }
          } 
}
text {
  ttf             // font type (only TrueType format for now)
  "crystal.ttf",  // Microsoft Windows-format TrueType font file name
  "Matodor",      // the string to create
  1,              // the extrusion depth
  0               // inter-character spacing   
  rotate <0,-85,0>            
  scale 0.5
  translate <1, 1.5, 2.1>
  texture {
            pigment {           
              color rgb <0,0,0>
            }
            finish{
              specular 0.1
            }
          } 
}
