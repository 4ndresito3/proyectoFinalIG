#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "MaterialLoader.h"

void configScene();
void renderScene();
void setLights (glm::mat4 P, glm::mat4 V);
void drawMatrix(glm::mat4 P, glm::mat4 V);
void drawBook(glm::mat4 P, glm::mat4 V, glm::mat4 M, bool control);
void drawMago(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCrystal1(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCrystal2(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectMat(Model &model, Material material, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawObjectTex(Model &model, Textures textures, glm::mat4 P, glm::mat4 V, glm::mat4 M);

void funFramebufferSize(GLFWwindow* window, int width, int height);
void funKey            (GLFWwindow* window, int key  , int scancode, int action, int mods);
void funScroll         (GLFWwindow* window, double xoffset, double yoffset);
void funCursorPos      (GLFWwindow* window, double xpos, double ypos);
void funTimer          (double seconds, double &t0);

// Shaders
  Shaders shaders;

// Modelos
  Model sphere;
  Model plane;
  Model cube;
  Model staff;
  Model cylinder;
  Model cone;
  Model crystal1;
  Model crystal2;

// Imagenes (texturas)
  TextureLoader textureLoader; 
  MaterialLoader materialLoader;

// Luces y materiales
  #define   NLD 1
  #define   NLP 1
  #define   NLF 2
  Light     lightG;
  Light     lightD[NLD];
  Light     lightP[NLP];
  Light     lightF[NLF];
  Material  mluz;
  Material  ruby;
  Material  gold;

// Viewport
  int w = 500;
  int h = 500;

// Animaciones
  float desX = 0.0;
  float desY = 0.0;
  float desZ = 0.0;
  float rotZBook = 0.0;
  bool  rotZUp = true;
  float autoYBook = 1.0;
  bool  autoYUp = true;
  float autoXBook = 0.0;
  bool  autoXleft = true;
  float cameraMovX = 0.0;
  float cameraMovY = 0.0;
  float cameraMovZ = 0.0;
  //Mejorar rotacion camara
  bool firstMouse = true;
  double lastX, lastY;
  float sensitivity = 0.1f;

// Movimiento de camara
  float fovy   = 60.0;
  float alphaX =  0.0;
  float alphaY =  0.0;

int main() {

 // Inicializamos GLFW
  if(!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

 // Creamos la ventana
  GLFWwindow* window;
  window = glfwCreateWindow(w, h, "Sesion 7", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

 // Inicializamos GLEW
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if(GLEW_OK != err) {
    std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    return -1;
  }
  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  const GLubyte *oglVersion = glGetString(GL_VERSION);
  std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;

// Configuramos los CallBacks
  glfwSetFramebufferSizeCallback(window, funFramebufferSize);
  glfwSetKeyCallback      (window, funKey);
  glfwSetScrollCallback   (window, funScroll);
  glfwSetCursorPosCallback(window, funCursorPos);

 // Entramos en el bucle de renderizado
  configScene();
  double t0 = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {
    renderScene();
    glfwSwapBuffers(window);
    glfwPollEvents();
    funTimer(0.01,t0);
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void configScene() {

 // Test de profundidad
  glEnable(GL_DEPTH_TEST);

// Transparencias
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Shaders
  shaders.initShaders("resources/shaders/vshader.glsl","resources/shaders/fshader.glsl");

// Modelos
  sphere.initModel("resources/models/sphere.obj");
  plane.initModel("resources/models/plane.obj");
  cube.initModel("resources/models/cube.obj");
  cylinder.initModel("resources/models/cylinder.obj");
  staff.initModel("resources/models/staff.obj");
  cone.initModel("resources/models/cone.obj");
  crystal1.initModel("resources/models/crystal1.obj");
  crystal2.initModel("resources/models/crystal2.obj");

  // Imagenes (texturas)
  textureLoader.loadTextures();

  // Cargar materiales
  materialLoader.loadMaterials();

// Luz ambiental global
  lightG.ambient = glm::vec3(0.5, 0.5, 0.5);

// Luces direccionales
  lightD[0].direction = glm::vec3(-1.0, 0.0, 0.0);
  lightD[0].ambient   = glm::vec3( 0.1, 0.1, 0.1);
  lightD[0].diffuse   = glm::vec3( 0.7, 0.7, 0.7);
  lightD[0].specular  = glm::vec3( 0.7, 0.7, 0.7);

// Luces posicionales
  lightP[0].position    = glm::vec3(0.0, 3.0, 3.0);
  lightP[0].ambient     = glm::vec3(0.2, 0.2, 0.2);
  lightP[0].diffuse     = glm::vec3(0.9, 0.9, 0.9);
  lightP[0].specular    = glm::vec3(0.9, 0.9, 0.9);
  lightP[0].c0          = 1.00;
  lightP[0].c1          = 0.22;
  lightP[0].c2          = 0.20;

// Luces focales
  lightF[0].position    = glm::vec3(-2.0,  2.0,  5.0);
  lightF[0].direction   = glm::vec3( 2.0, -2.0, -5.0);
  lightF[0].ambient     = glm::vec3( 0.2,  0.2,  0.2);
  lightF[0].diffuse     = glm::vec3( 0.9,  0.9,  0.9);
  lightF[0].specular    = glm::vec3( 0.9,  0.9,  0.9);
  lightF[0].innerCutOff = 10.0;
  lightF[0].outerCutOff = lightF[0].innerCutOff + 5.0;
  lightF[0].c0          = 1.000;
  lightF[0].c1          = 0.090;
  lightF[0].c2          = 0.032;
  lightF[1].position    = glm::vec3( 2.0,  2.0,  5.0);
  lightF[1].direction   = glm::vec3(-2.0, -2.0, -5.0);
  lightF[1].ambient     = glm::vec3( 0.2,  0.2,  0.2);
  lightF[1].diffuse     = glm::vec3( 0.9,  0.9,  0.9);
  lightF[1].specular    = glm::vec3( 0.9,  0.9,  0.9);
  lightF[1].innerCutOff = 5.0;
  lightF[1].outerCutOff = lightF[1].innerCutOff + 1.0;
  lightF[1].c0          = 1.000;
  lightF[1].c1          = 0.090;
  lightF[1].c2          = 0.032;
}

void renderScene() {

// Borramos el buffer de color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 // Indicamos los shaders a utilizar
  shaders.useShaders();

 // Matriz P
  float nplane =  0.1;
  float fplane = 25.0;
  float aspect = (float)w/(float)h;
  glm::mat4 P = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

 // Matriz V
  float x = 10.0f*glm::cos(glm::radians(alphaY))*glm::sin(glm::radians(alphaX));
  float y = 10.0f*glm::sin(glm::radians(alphaY));
  float z = 10.0f*glm::cos(glm::radians(alphaY))*glm::cos(glm::radians(alphaX));
  glm::vec3 eye   (x + cameraMovX, y + cameraMovY, z + cameraMovZ);
  glm::vec3 center(cameraMovX, cameraMovY, cameraMovZ);
  glm::vec3 up    (0.0, 1.0,  0.0);
  glm::mat4 V = glm::lookAt(eye, center, up);
  shaders.setVec3("ueye",eye);

 // Fijamos las luces
  setLights(P,V);

 // Dibujamos la escena
  drawMatrix(P,V);

  glm::mat4 S = glm::scale    (I, glm::vec3(8.0, 2.0, 8.0)); //suelo
  glm::mat4 T = glm::translate(I, glm::vec3(0.0,-3.0, 0.0));
  drawObjectTex(plane, textureLoader.getWall(), P, V, T * S);

  S = glm::scale               (I, glm::vec3(8.0, 1.0, 4.0));
  glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1,0,0)); //fondo de atras
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 Tz = glm::translate(I, glm::vec3(0.0, 0.0, -8.0));
  drawObjectTex(plane, textureLoader.getWall(), P, V, Tz * Ty * Rx * S);

  S = glm::scale               (I, glm::vec3(4.0, 1.0, 8.0));
  glm::mat4 Rz = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,0,1)); //fondo del lado
  Ty = glm::translate          (I, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 Tx = glm::translate(I, glm::vec3(-8.0, 0.0, 0.0));
  drawObjectTex(plane, textureLoader.getWall(), P, V, Ty * Tx * Rz * S);

  glm::mat4 Tfin = glm::translate(I, glm::vec3(-2.0, 0.0, 3.0));
  drawCrystal1(P, V, Tfin);

  Tfin = glm::translate(I, glm::vec3(0.0, 0.0, -3.0));
  drawCrystal1(P, V, Tfin);

  Tfin = glm::translate(I, glm::vec3(2.0, 0.0, 3.0));
  drawCrystal2(P, V, Tfin);

  Tfin = glm::translate(I, glm::vec3(-2.0, 1.0, -3.0));
  drawBook(P, V, Tfin, true);

  Tfin = glm::translate(I, glm::vec3(3.0, autoYBook, 2.0));
  drawBook(P, V, Tfin, false);

  Tfin = glm::translate(I, glm::vec3(autoXBook + 1.0, autoYBook + 2.0, -3.0));
  glm::mat4 Rfin = glm::rotate(I, glm::radians(90.0f), glm::vec3(0,1,0));
  drawBook(P, V, Tfin * Rfin, false);

  glm::mat4 Mago = glm::translate(I, glm::vec3(0.0, 0.0, 0.0));
  drawMago (P, V, Mago);

  /*
  
  
  glm::mat4 Rv = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1,0,0));
  glm::mat4 Tv = glm::translate(I, glm::vec3(0.0, 0.0, 3.0));
  glDepthMask(GL_FALSE);
    drawObjectTex(plane, texWindow, P, V, Tv * Rv);
  glDepthMask(GL_TRUE);
  */
}

void setLights(glm::mat4 P, glm::mat4 V) {

  shaders.setLight("ulightG",lightG);
  for(int i=0; i<NLD; i++) shaders.setLight("ulightD["+toString(i)+"]",lightD[i]);
  for(int i=0; i<NLP; i++) shaders.setLight("ulightP["+toString(i)+"]",lightP[i]);
  for(int i=0; i<NLF; i++) shaders.setLight("ulightF["+toString(i)+"]",lightF[i]);

  for(int i=0; i<NLP; i++) {
    glm::mat4 M = glm::translate(I,lightP[i].position) * glm::scale(I,glm::vec3(0.1));
    drawObjectMat(sphere, materialLoader.getMluz(), P, V, M);
  }

  for(int i=0; i<NLF; i++) {
    glm::mat4 M = glm::translate(I,lightF[i].position) * glm::scale(I,glm::vec3(0.025));
    drawObjectMat(sphere, materialLoader.getMluz(), P, V, M);
  }

}

void drawMatrix(glm::mat4 P, glm::mat4 V) {

  glm::mat4 S = glm::scale (I, glm::vec3(0.015, 0.015, 0.015));
  for(int i = 0; i < 15; i++)
    for(int j = 0; j < 7; j++)
      for(int k = 0; k < 15; k++) {
        glm::mat4 T = glm::translate(I, glm::vec3(i - 7.0f, j - 3.0f, k - 7.0f));
        drawObjectMat(sphere, materialLoader.getGold(), P, V, T * S);
      }
}

void drawBook(glm::mat4 P, glm::mat4 V, glm::mat4 M, bool control) {

  glm::mat4 Dx = glm::translate(I, glm::vec3(control ? desX : 0.0f, 0.0f, 0.0f)); //Para mover el libro
  glm::mat4 Dy = glm::translate(I, glm::vec3(0.0f, control ? desY : 0.0f, 0.0f));
  glm::mat4 Dz = glm::translate(I, glm::vec3(0.0f, 0.0f, control ? desZ : 0.0f));

  glm::mat4 Rz = glm::rotate   (I, glm::radians(rotZBook), glm::vec3(0,0,1)); //Portada del libro 1
  glm::mat4 T1 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f)); //Para rotar en el extremo del libro
  glm::mat4 T2 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f));
  glm::mat4 S = glm::scale(I, glm::vec3(1.0/3, 0.15/3, 1.0/3));
  drawObjectTex(cube, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(rotZBook), glm::vec3(0,0,1)); //Paginas del libro 1
  T1 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f)); //Para rotar en el extremo del libro
  T2 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f));
  S = glm::scale(I, glm::vec3(1.0/4, 0.15/5, 1.0/4));
  glm::mat4 Tp = glm::translate(I, glm::vec3(0.05f, 0.05f, 0.0f));
  drawObjectMat(cube, materialLoader.getPage(), P, V, Dz * Dy * Dx * M * Tp * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(-rotZBook), glm::vec3(0,0,1)); //Portada del libro 2
  T1 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f)); 
  T2 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f));
  glm::mat4 Tx = glm::translate(I, glm::vec3(0.75, 0.0, 0.0));
  S = glm::scale(I, glm::vec3(1.0/3, 0.15/3, 1.0/3));
  drawObjectTex(cube, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * Tx * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(-rotZBook), glm::vec3(0,0,1)); //Paginas del libro 2
  T1 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f)); 
  T2 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f));
  Tx = glm::translate(I, glm::vec3(0.75, 0.0, 0.0));
  Tp = glm::translate(I, glm::vec3(-0.05f, 0.05f, 0.0f));
  S = glm::scale(I, glm::vec3(1.0/4, 0.15/5, 1.0/4));
  drawObjectMat(cube, materialLoader.getPage(), P, V, Dz * Dy * Dx * M * Tp * Tx * T2 * Rz * T1 * S);
  
  Rz = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,0,1)); //Cilindro del libro
  glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,1,0));
  Tx = glm::translate(I, glm::vec3(0.37, 0.0, 0.0));
  S = glm::scale(I, glm::vec3(0.2/3, 1.0/3, 0.2/3));
  drawObjectTex(cylinder, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * Tx * Ry * Rz * S);
}

void drawCrystal1(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

  glm::mat4 S = glm::scale(I, glm::vec3(3.0f, 3.0f, 3.0f));
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, -3.0f, 0.0f)); 
  drawObjectTex(crystal1, textureLoader.getCrystal(), P, V, M * Ty * S);

}

void drawCrystal2(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

  glm::mat4 S = glm::scale(I, glm::vec3(4.0f, 4.0f, 4.0f));
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, -2.1f, 0.0f)); 
  drawObjectTex(crystal2, textureLoader.getRuby(), P, V, M * Ty * S);

}

void drawObjectMat(Model &model, Material material, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

  shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
  shaders.setMat4("uM"  ,M);
  shaders.setMat4("uPVM",P*V*M);
  shaders.setBool("uWithMaterials",true);
  shaders.setMaterial("umaterial",material);
  model.renderModel(GL_FILL);

}

void drawObjectTex(Model &model, Textures textures, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

  shaders.setMat4("uN"  ,glm::transpose(glm::inverse(M)));
  shaders.setMat4("uM"  ,M);
  shaders.setMat4("uPVM",P*V*M);
  shaders.setBool("uWithMaterials",false);
  shaders.setTextures("utextures",textures);
  if(textures.normal!=0) shaders.setBool("uWithNormals",true);
  else                   shaders.setBool("uWithNormals",false);
  model.renderModel(GL_FILL);

}

void funFramebufferSize(GLFWwindow* window, int width, int height) {

// Configuracion del Viewport
  glViewport(0, 0, width, height);

// Actualizacion de w y h
  w = width;
  h = height;

}

void funKey(GLFWwindow* window, int key  , int scancode, int action, int mods) {
  if (action == GLFW_RELEASE) return;
  switch(key) {
    case GLFW_KEY_LEFT:  desX -= 0.2f;   break;
    case GLFW_KEY_RIGHT: desX += 0.2f;   break;
    case GLFW_KEY_DOWN:  desY -= 0.2f;   break;
    case GLFW_KEY_UP:    desY += 0.2f;   break;
    case GLFW_KEY_Z:
      if (mods == GLFW_MOD_SHIFT)
        desZ -= 0.2f;   // Shift + Z
      else
        desZ += 0.2f;   // z
      break;
    case GLFW_KEY_A:  cameraMovX -= 0.2f;   break; 
    case GLFW_KEY_D:  cameraMovX += 0.2f;   break;
    case GLFW_KEY_S:  cameraMovY -= 0.2f;   break;
    case GLFW_KEY_W:  cameraMovY += 0.2f;   break;
    case GLFW_KEY_Q:  cameraMovZ -= 0.2f;   break;
    case GLFW_KEY_E:  cameraMovZ += 0.2f;   break;
    case GLFW_KEY_R:
      desX = 0.0f;
      desY = 0.0f;
      desZ = 0.0f;
      cameraMovX = 0.0f;
      cameraMovY = 0.0f;
      cameraMovZ = 0.0f;
      break;   
  }

}

void funScroll(GLFWwindow* window, double xoffset, double yoffset) {

  if(yoffset>0) fovy -= fovy>10.0f ? 5.0f : 0.0f;
  if(yoffset<0) fovy += fovy<120.0f ? 5.0f : 0.0f;

}

void funCursorPos(GLFWwindow* window, double xpos, double ypos) {

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
    firstMouse = true;
    return;
  }

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
    return;
  }

  float dx = xpos - lastX;
  float dy = lastY - ypos; // invertido para Y

  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.3f;

  alphaX += dx * sensitivity;
  alphaY += dy * sensitivity;

  float limY = 89.0f;
  if (alphaY < -limY) alphaY = -limY;
  if (alphaY >  limY) alphaY =  limY;
}


void funTimer(double seconds, double &t0) { 
  double t1 = glfwGetTime();
  bool up = true;
  if(t1-t0 > seconds) { 
    if(rotZUp) { //animacion del libro abriendo y cerrando
        rotZBook -= 5.0f;
        if(rotZBook <= -90.0f) {
          rotZBook = -90.0f;
          rotZUp = false;
        }
    } else {
      rotZBook += 5.0f;
      if(rotZBook >= 0.0f) {
        rotZBook = 0.0f;
        rotZUp = true;
      }
    }
    if(autoYUp) { //animacion del libro que oscila arriba y abajo
        autoYBook -= 0.05f;
        if(autoYBook <= 0.0f) {
          autoYBook = 0.0f;
          autoYUp = false;
        }
    } else {
      autoYBook += 0.05f;
      if(autoYBook >= 1.0f) {
        autoYBook = 1.0f;
        autoYUp = true;
      }
    }
    if(autoXleft) { //animacion del libro que se mueve izquierda y derecha
        autoXBook -= 0.05f;
        if(autoXBook <= -2.0f) {
          autoXBook = -2.0f;
          autoXleft = false;
        }
    } else {
      autoXBook += 0.05f;
      if(autoXBook >= 2.0f) {
        autoXBook = 2.0f;
        autoXleft = true;
      }
    }
    t0 = t1;
  }
}

void drawMago(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
  glm::mat4 sMago = glm::scale    (I, glm::vec3(1.1, 0.75, 1));
  glm::mat4 tMago = glm::translate(I, glm::vec3(0.0, -3.0, 0.0));
  glm::mat4 M1 = tMago * sMago;
  drawObjectMat(cone, materialLoader.getGold(), P, V, M * M1);
  glm::mat4 sBrazos = glm::scale    (I, glm::vec3(0.3, 0.4, 0.3));
  glm::mat4 rotBrazo1 = glm::rotate   (I, glm::radians(30.0f), glm::vec3(0,0,1));
  glm::mat4 transBrazo1 = glm::translate(I, glm::vec3(0.95, -2.0, 0.0));
  M1 = transBrazo1 * rotBrazo1 * sBrazos;
  drawObjectMat(cone, materialLoader.getGold(), P, V, M * M1);
  glm::mat4 rotBrazo2 = glm::rotate   (I, glm::radians(-30.0f), glm::vec3(0,0,1));
  glm::mat4 transBrazo2 = glm::translate(I, glm::vec3(-0.95, -2.0, 0.0));
  M1 = transBrazo2 * rotBrazo2 * sBrazos;
  drawObjectMat(cone, materialLoader.getGold(), P, V, M * M1);
  glm::mat4 sCabeza = glm::scale    (I, glm::vec3(0.45, 0.20, 0.49));
  glm::mat4 tCabeza = glm::translate(I, glm::vec3(0.0, -0.50, 0.2));
  glm::mat4 rCabeza = glm::rotate   (I, glm::radians(-80.0f), glm::vec3(1,0,0));
  M1 = tCabeza * rCabeza * sCabeza;
  drawObjectMat(cone, materialLoader.getGold(), P, V, M * M1);
  glm::mat4 sCara = glm::scale    (I, glm::vec3(0.15, 0.10, 0.20));
  glm::mat4 tCara = glm::translate(I, glm::vec3(0.0, -0.47, 0.2));
  M1 = tCara * rCabeza * sCara;
  drawObjectMat(sphere, materialLoader.getGold(), P, V, M * M1);
  glm::mat4 R = glm::rotate   (I, glm::radians(-25.0f), glm::vec3(0,0,1));
  glm::mat4 Ry = glm::rotate   (I, glm::radians(120.0f), glm::vec3(0,1,0));
  glm::mat4 T = glm::translate(I, glm::vec3(1.0, -0.9, 0.2));
  glm::mat4 S = glm::scale    (I, glm::vec3(0.1, 0.1, 0.1));
  drawObjectTex(staff, textureLoader.getStaff(), P, V, M * T * Ry * R  * S);
}