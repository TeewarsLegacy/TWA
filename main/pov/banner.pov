#version 3.5;

#include "colors.inc"

global_settings {
  assumed_gamma 1.0
}

camera {
  location  <9, 3, 5>
  direction 1.5*z                               
  look_at   <0.0, 0.0,  0.0>
}

sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.6,0.7,1.0>]
      [0.7 rgb <0.0,0.1,0.8>]
    }
  }
}

light_source {
  <0, 0, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <30, 30, 30>
}

// ----------------------------------------

plane {
  y, -1
  pigment { color rgb <0.7,0.5,0.3> }
}

// Tee body
union{       
      // Head
      sphere {
          <0, 0.5, 0>, 1
          texture {
            pigment {
              color rgb <0.55,0.5,0.25>
            }
            finish{
              specular 0.1
            }
          }
        }  
        difference {
            sphere {
                <2.15, 0.35, -0.35>, 0.25
                scale <0.45,1.75,0.75>
            } 
            box {
                <0.5,0.6,-1>
                <2.5,1.5,1>
                rotate <20,0,0>
            } 
        
            texture {
                pigment { color rgb <0,0,0> }
                finish { specular 0.25 }
            }
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
        rotate <-5,-10.5,17.5>    
}



// Foots
       
// right                
// CSG difference, subtract intersections of shapes 2...N from Shape1
difference {
   sphere {
          <0, 0, 0>, 0.45
          texture {
            pigment {           
              color rgb <0.4,0.3,0.15>
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
              color rgb <0.4,0.3,0.15>
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
              color rgb <0.4,0.3,0.15>
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
              color rgb <0.4,0.3,0.15>
            }
            finish{
              specular 0.1
            }
          }  
   }  
   translate <-0.25,-1.05,-0.5> 
    
}
            
           
