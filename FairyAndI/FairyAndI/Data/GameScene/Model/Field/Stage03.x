xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Stage03 {
    FrameTransformMatrix {
      1000.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 5.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Stage03 mesh
      8;
       0.000000;-1.000000;-2.000000;,
       0.000000;-1.000000; 0.000000;,
       0.000000; 1.000000;-2.000000;,
       0.000000; 1.000000; 0.000000;,
       2.000000;-1.000000;-2.000000;,
       2.000000;-1.000000; 0.000000;,
       2.000000; 1.000000;-2.000000;,
       2.000000; 1.000000; 0.000000;;
      6;
      4;2,3,1,0;,
      4;6,7,3,2;,
      4;4,5,7,6;,
      4;0,1,5,4;,
      4;0,4,6,2;,
      4;5,1,3,7;;
      MeshNormals { // Stage03 normals
        6;
        -1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000;-1.000000; 0.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-0.000000; 1.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Stage03 normals
      MeshMaterialList { // Stage03 material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material material {
           0.125947; 0.125947; 0.125947; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Stage03 material list
    } // End of Stage03 mesh
  } // End of Stage03
} // End of Root
