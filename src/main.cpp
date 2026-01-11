#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "MaterialLoader.h"
#include "LightsManager.h"

void configScene();
void renderScene();
void setLights (glm::mat4 P, glm::mat4 V);
void drawBook(glm::mat4 P, glm::mat4 V, glm::mat4 M, bool control, bool inPlace);
void drawCrystal1(glm::mat4 P, glm::mat4 V, glm::mat4 Tfin, glm::mat4 Ry, glm::mat4 Sfin);
void drawCrystal2(glm::mat4 P, glm::mat4 V, glm::mat4 Tfin, glm::mat4 Ry, glm::mat4 Sfin);
void drawAllCrystals(glm::mat4 P, glm::mat4 V);
void drawBookshelf(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawMago(glm::mat4 P, glm::mat4 V, glm::mat4 M);
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
  Model bookshelf;
  Model table;

// Loaders/Managers
  TextureLoader textureLoader; 
  MaterialLoader materialLoader;
  LightsManager lightsManager;

  Material  mluz;
  Material  ruby;
  Material  gold;

// Viewport
  int w = 500;
  int h = 500;

// Animaciones
  bool controlBook = false;
  bool controlLight = false;
  bool firstTime = true;
  float desX = 0.0; // desplazamiento libro
  float desY = 0.0;
  float desZ = 0.0;
  float desXMage = 0.0; // desplazamiento mago
  float desZMage = 0.0;
  float rotArmMage = 0.0;
  float mageLookAt = 0.0;
  float rotZBook = 0.0;
  bool  rotZUp = true; // para animar libro
  float autoYBook = 1.0;
  bool  autoYUp = true; // para animar libro
  float autoXBook = 0.0;
  bool  autoXleft = true; // para animar libro
  float bookLookAt = 0.0;
  bool  showBook = false; // dibujar libro que controlas
  bool  bookPlaced = false; 
  float cameraMovX = 0.0;
  float cameraMovY = 0.0;
  float cameraMovZ = 0.0;
  bool  hechizoLanzado = false;
  float outOfCamera1 = 0.0; // "parpadeo" hechizo
  float outOfCamera2 = 0.0;
  int outOfCameraTimer = 0;

  //Mejorar rotacion camara
  bool firstMouse = true;
  double lastX, lastY;
  float sensitivity = 0.1f;

// Movimiento de camara
  float fovy   = 80.0;
  float alphaX =  0.0;
  float alphaY =  0.0;

// Control de luz direccional (sol)
  float sunAngle = 0.0f;

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
  bookshelf.initModel("resources/models/bookshelf.obj");
  table.initModel("resources/models/table.obj");

  // Imagenes (texturas)
  textureLoader.loadTextures();

  // Cargar materiales
  materialLoader.loadMaterials();

  // Cargar luces
  // lightsManager = LightsManager();

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
  glm::vec3 eye   (2.0 + x + cameraMovX, 2.0 + y + cameraMovY, z + cameraMovZ);
  glm::vec3 center(cameraMovX, cameraMovY, cameraMovZ);
  glm::vec3 up    (0.0, 1.0, 0.0);
  glm::mat4 V = glm::lookAt(eye, center, up);
  shaders.setVec3("ueye",eye);

 // Actualizamos la luz de cámara (linterna) con la posición y dirección de la cámara
  glm::vec3 cameraDirection = glm::normalize(center - eye);
  lightsManager.updateCameraLight(eye, cameraDirection);

 // Actualizamos la dirección del sol según sunAngle
  glm::vec3 sunDirection = glm::vec3(glm::cos(glm::radians(sunAngle)), -0.5f, glm::sin(glm::radians(sunAngle)));
  lightsManager.setLightDDirection(0, sunDirection);

  if (hechizoLanzado) {
    lightsManager.turnOffDirectionalLights();
    lightsManager.turnOffPositionalLights();
    lightsManager.setSpellLight(glm::vec3(0.0, 5.0, 10.0)); // Luz focal potente sobre la escena
  }
  
  if (showBook && controlBook && firstTime) {
    lightsManager.setFrontSpotlight(); // Luz focal frontal cuando el libro que controlas aparece
  } else {
    lightsManager.turnOffFrontSpotlight();
  }

 // Fijamos las luces
  setLights(P,V);

 // Dibujamos la escena

  glm::mat4 S = glm::scale    (I, glm::vec3(8.0, 2.0, 8.0)); //suelo
  glm::mat4 T = glm::translate(I, glm::vec3(0.0,-3.0, 0.0));
  drawObjectTex(plane, textureLoader.getGreyRock(), P, V, T * S);
  S = glm::scale               (I, glm::vec3(8.0, 1.0, 4.0));
  glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1,0,0)); //fondo de atras
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 Tz = glm::translate(I, glm::vec3(0.0, 0.0, -8.0));
  drawObjectTex(plane, textureLoader.getStoneWall(), P, V, Tz * Ty * Rx * S);

  drawAllCrystals(P, V);

  if(showBook) { 
    glm::mat4 Tfin = glm::translate(I, glm::vec3(-2.0, 2.3, -6.5)); //libro que controlas
    glm::mat4 Ry = glm::rotate   (I, glm::radians(bookLookAt), glm::vec3(0,1,0));
    drawBook(P, V, Tfin * Ry, true, false);
  }
  if(bookPlaced) {
    glm::mat4 Tfin = glm::translate(I, glm::vec3(-5.8, -1.0, 0.4)); //libro colocado en mesa
    glm::mat4 Ry = glm::rotate     (I, glm::radians(90.0f), glm::vec3(0,1,0));
    drawBook(P, V, Tfin * Ry, false, true);
  }
  glm::mat4 Tfin = glm::translate(I, glm::vec3(3.0, autoYBook + 0.5, 3.0)); //libros automaticos animados
  drawBook(P, V, Tfin, false, false);
  Tfin = glm::translate(I, glm::vec3(autoXBook + 3.0, autoYBook + 2.0, -2.0));
  glm::mat4 Ry = glm::rotate(I, glm::radians(90.0f), glm::vec3(0,1,0));
  drawBook(P, V, Tfin * Ry, false, false);

  glm::mat4 Mago = glm::translate(I, glm::vec3(desXMage, 0.66f, desZMage)); //mago
  Ry = glm::rotate   (I, glm::radians(mageLookAt), glm::vec3(0,1,0));
  auto escaladoMago = glm::scale(I,glm::vec3(1.2));
  drawMago (P, V, Mago * Ry * escaladoMago);

  Tfin = glm::translate(I, glm::vec3(-1.8, 0.0, -7.0)); //librerias
  drawBookshelf(P, V, Tfin);
  Tfin = glm::translate(I, glm::vec3(1.8, 0.0, -7.0));
  drawBookshelf(P, V, Tfin);

  S = glm::scale       (I, glm::vec3(4.0, 1.0, 3.0)); //alfombra
  Tfin = glm::translate(I, glm::vec3(0.0, -2.99, 2.2));
  drawObjectTex(plane, textureLoader.getRug(), P, V, Tfin * S);

  S = glm::scale       (I, glm::vec3(0.03, 0.03, 0.03)); //mesa
  Ry = glm::rotate     (I, glm::radians(90.0f), glm::vec3(0,1,0));
  Tfin = glm::translate(I, glm::vec3(-6.0, -3.0, 0.0));
  drawObjectTex(table, textureLoader.getWood(), P, V, Tfin * Ry * S);

  if(hechizoLanzado){
    S = glm::scale       (I, glm::vec3(0.2, 0.2, 0.2)); //esfera ruby semitransparente en camara tras hechizo
    T = glm::translate   (I, glm::vec3(2.0 + x + cameraMovX, 2.0 + y + cameraMovY + outOfCamera1, z + cameraMovZ));
    glDepthMask(GL_FALSE);
    drawObjectMat(sphere, materialLoader.getRubyAlpha(), P, V, T * S);
    glDepthMask(GL_TRUE);

    S = glm::scale       (I, glm::vec3(0.2, 0.2, 0.2)); //esfera gold semitransparente en camara tras hechizo
    T = glm::translate   (I, glm::vec3(2.0 + x + cameraMovX, 2.0 + y + cameraMovY + outOfCamera2, z + cameraMovZ));
    glDepthMask(GL_FALSE);
    drawObjectMat(sphere, materialLoader.getGoldAlpha(), P, V, T * S);
    glDepthMask(GL_TRUE);
  }

  S = glm::scale               (I, glm::vec3(4.0, 1.0, 8.0));
  glm::mat4 Rz = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,0,1)); //fondo del lado || pared transparente
  Ty = glm::translate          (I, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 Tx = glm::translate(I, glm::vec3(-8.0, 0.0, 0.0));
  glDepthMask(GL_FALSE);
  drawObjectMat(plane, materialLoader.getWall(), P, V, Ty * Tx * Rz * S);
  glDepthMask(GL_TRUE);
 
}

void setLights(glm::mat4 P, glm::mat4 V) {

  shaders.setLight("ulightG",lightsManager.getLightG());
  for(int i=0; i<lightsManager.getNumLightD(); i++) shaders.setLight("ulightD["+toString(i)+"]",lightsManager.getLightD(i));
  for(int i=0; i<lightsManager.getNumLightP(); i++) shaders.setLight("ulightP["+toString(i)+"]",lightsManager.getLightP(i));
  for(int i=0; i<lightsManager.getNumLightF(); i++) shaders.setLight("ulightF["+toString(i)+"]",lightsManager.getLightF(i));

  for(int i=0; i<lightsManager.getNumLightP(); i++) {
    glm::mat4 M = glm::translate(I,lightsManager.getLightP(i).position) * glm::scale(I,glm::vec3(0.1));
    drawObjectMat(sphere, materialLoader.getMluz(), P, V, M);
  }

  for(int i=0; i<lightsManager.getNumLightF(); i++) {
    glm::mat4 M = glm::translate(I,lightsManager.getLightF(i).position) * glm::scale(I,glm::vec3(0.025));
    drawObjectMat(sphere, materialLoader.getMluz(), P, V, M);
  }

}

void drawBook(glm::mat4 P, glm::mat4 V, glm::mat4 M, bool control, bool inPlace) {

  glm::mat4 Dx = glm::translate(I, glm::vec3(control ? desX : 0.0f, 0.0f, 0.0f)); //Para mover el libro
  glm::mat4 Dy = glm::translate(I, glm::vec3(0.0f, control ? desY : 0.0f, 0.0f));
  glm::mat4 Dz = glm::translate(I, glm::vec3(0.0f, 0.0f, control ? desZ : 0.0f));

  glm::mat4 Rz = glm::rotate   (I, glm::radians(inPlace ? 0.0f : rotZBook), glm::vec3(0,0,1)); //Portada del libro 1
  glm::mat4 T1 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f)); //Para rotar en el extremo del libro
  glm::mat4 T2 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f));
  glm::mat4 S = glm::scale(I, glm::vec3(1.0/3, 0.15/3, 1.0/3));
  drawObjectTex(cube, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(inPlace ? 0.0f : rotZBook), glm::vec3(0,0,1)); //Paginas del libro 1
  T1 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f)); //Para rotar en el extremo del libro
  T2 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f));
  S = glm::scale(I, glm::vec3(1.0/4, 0.15/5, 1.0/4));
  glm::mat4 Tp = glm::translate(I, glm::vec3(0.05f, 0.05f, 0.0f));
  drawObjectMat(cube, materialLoader.getPage(), P, V, Dz * Dy * Dx * M * Tp * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(inPlace ? 0.0f : -rotZBook), glm::vec3(0,0,1)); //Portada del libro 2
  T1 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f)); 
  T2 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f));
  glm::mat4 Tx = glm::translate(I, glm::vec3(0.75, 0.0, 0.0));
  S = glm::scale(I, glm::vec3(1.0/3, 0.15/3, 1.0/3));
  drawObjectTex(cube, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * Tx * T2 * Rz * T1 * S);

  Rz = glm::rotate   (I, glm::radians(inPlace ? 0.0f : -rotZBook), glm::vec3(0,0,1)); //Paginas del libro 2
  T1 = glm::translate(I, glm::vec3(0.35f, 0.0f, 0.0f)); 
  T2 = glm::translate(I, glm::vec3(-0.35f, 0.0f, 0.0f));
  Tx = glm::translate(I, glm::vec3(0.75, 0.0, 0.0));
  Tp = glm::translate(I, glm::vec3(-0.05f, 0.05f, 0.0f));
  S = glm::scale(I, glm::vec3(1.0/4, 0.15/5, 1.0/4));
  drawObjectMat(cube, materialLoader.getPage(), P, V, Dz * Dy * Dx * M * Tp * Tx * T2 * Rz * T1 * S);
  
  Rz = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,0,1)); //Cilindro del libro
  glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0,1,0));
  Tx = glm::translate(I, glm::vec3(0.375, 0.0, 0.0));
  S = glm::scale(I, glm::vec3(0.2/3, 1.0/3, 0.2/3));
  drawObjectTex(cylinder, textureLoader.getCover(), P, V, Dz * Dy * Dx * M * Tx * Ry * Rz * S);
}

void drawCrystal1(glm::mat4 P, glm::mat4 V, glm::mat4 Tfin, glm::mat4 Ry, glm::mat4 Sfin) {

  glm::mat4 S = glm::scale(I, glm::vec3(3.0f, 3.0f, 3.0f));
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, -3.0f, 0.0f)); 
  drawObjectTex(crystal1, textureLoader.getCrystal(), P, V, Tfin * Ty * Ry * Sfin * S);

}

void drawCrystal2(glm::mat4 P, glm::mat4 V, glm::mat4 Tfin, glm::mat4 Ry, glm::mat4 Sfin) {

  glm::mat4 S = glm::scale(I, glm::vec3(1.5f, 1.5f, 1.5f));
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, -3.0f, 0.0f)); 
  drawObjectTex(crystal2, textureLoader.getCrystal2(), P, V, Tfin * Ty * Ry * Sfin * S);

}

void drawAllCrystals(glm::mat4 P, glm::mat4 V) {

  glm::mat4 Tfin = glm::translate(I, glm::vec3(-5.0, 0.0, -5.0));
  glm::mat4 Sfin = glm::scale    (I, glm::vec3(3.0, 4.0, 3.0)); 
  glm::mat4 Ry = glm::rotate     (I, glm::radians(45.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(-4.0, 0.0, -6.0));
  Sfin = glm::scale    (I, glm::vec3(2.0, 3.0, 3.0)); 
  Ry = glm::rotate     (I, glm::radians(90.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(-6.0, 0.0, -4.0));
  Sfin = glm::scale    (I, glm::vec3(2.0, 2.75, 3.0)); 
  Ry = glm::rotate     (I, glm::radians(-90.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(-6.1, 0.0, -6.3));
  Sfin = glm::scale    (I, glm::vec3(4.3, 5.0, 4.3)); 
  Ry = glm::rotate     (I, glm::radians(30.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(-7.0, 0.0, -3.5));
  Sfin = glm::scale    (I, glm::vec3(1.5, 2, 1.5)); 
  Ry = glm::rotate     (I, glm::radians(270.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(-3.5, 0.0, -7.2));
  Sfin = glm::scale    (I, glm::vec3(1.5, 2, 1.5)); 
  Ry = glm::rotate     (I, glm::radians(270.0f), glm::vec3(0,1,0));
  drawCrystal1(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(5.0, 0.0, -5.0));
  Sfin = glm::scale    (I, glm::vec3(3.0, 4.0, 3.0)); 
  Ry = glm::rotate     (I, glm::radians(-45.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(4.0, 0.0, -6.0));
  Sfin = glm::scale    (I, glm::vec3(2.0, 3.0, 3.0)); 
  Ry = glm::rotate     (I, glm::radians(-90.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(6.0, 0.0, -4.0));
  Sfin = glm::scale    (I, glm::vec3(2.0, 2.75, 3.0)); 
  Ry = glm::rotate     (I, glm::radians(90.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(6.1, 0.0, -6.0));
  Sfin = glm::scale    (I, glm::vec3(4.3, 5.0, 4.3)); 
  Ry = glm::rotate     (I, glm::radians(-30.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(7.0, 0.0, -3.5));
  Sfin = glm::scale    (I, glm::vec3(1.5, 2, 1.5)); 
  Ry = glm::rotate     (I, glm::radians(-270.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);

  Tfin = glm::translate(I, glm::vec3(3.5, 0.0, -7.0));
  Sfin = glm::scale    (I, glm::vec3(1.5, 2, 1.5)); 
  Ry = glm::rotate     (I, glm::radians(-270.0f), glm::vec3(0,1,0));
  drawCrystal2(P, V, Tfin, Ry, Sfin);
} 

void drawBookshelf(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

  glm::mat4 S = glm::scale     (I, glm::vec3(4.5, 3.5, 3.0));
  glm::mat4 Ry = glm::rotate   (I, glm::radians(180.0f), glm::vec3(0,1,0));
  glm::mat4 Ty = glm::translate(I, glm::vec3(0.0, -3.0, 0.0));
  drawObjectTex(bookshelf, textureLoader.getBookshelf(), P, V, M * Ty * Ry * S);

}
  
void drawMago(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
  
  glm::mat4 sMago = glm::scale    (I, glm::vec3(1.1, 0.75, 1));
  glm::mat4 tMago = glm::translate(I, glm::vec3(0.0, -3.0, 0.0));
  glm::mat4 M1 = tMago * sMago;
  drawObjectTex(cone, textureLoader.getBlueCotton(), P, V, M * M1);

  glm::mat4 sBrazos = glm::scale    (I, glm::vec3(0.3, 0.4, 0.3));
  glm::mat4 rotBrazo1 = glm::rotate   (I, glm::radians(30.0f), glm::vec3(0,0,1));
  glm::mat4 transBrazo1 = glm::translate(I, glm::vec3(0.95, -2.0, 0.0));
  glm::mat4 rotBrazoManual = glm::rotate   (I, glm::radians(rotArmMage), glm::vec3(1,0,0));
  glm::mat4 translate1 = glm::translate(I, glm::vec3(-0.8, 1.25, 0.0)); //para que rote en el hombro
  glm::mat4 translate2 = glm::translate(I, glm::vec3(0.8, -1.25, 0.0));
  M1 = translate2 * rotBrazoManual * translate1 * transBrazo1 * rotBrazo1 * sBrazos;
  drawObjectTex(cone, textureLoader.getBlueCotton(), P, V, M * M1);

  glm::mat4 rotBrazo2 = glm::rotate   (I, glm::radians(-30.0f), glm::vec3(0,0,1));
  glm::mat4 transBrazo2 = glm::translate(I, glm::vec3(-0.95, -2.0, 0.0));
  M1 = transBrazo2 * rotBrazo2 * sBrazos;
  drawObjectTex(cone, textureLoader.getBlueCotton(), P, V, M * M1);

  glm::mat4 sCabeza = glm::scale    (I, glm::vec3(0.45, 0.20, 0.49));
  glm::mat4 tCabeza = glm::translate(I, glm::vec3(0.0, -0.50, 0.2));
  glm::mat4 rCabeza = glm::rotate   (I, glm::radians(-80.0f), glm::vec3(1,0,0));
  M1 = tCabeza * rCabeza * sCabeza;
  drawObjectTex(cone, textureLoader.getBlueCotton(), P, V, M * M1);

  glm::mat4 sCara = glm::scale    (I, glm::vec3(0.15, 0.10, 0.20));
  glm::mat4 tCara = glm::translate(I, glm::vec3(0.0, -0.47, 0.2));
  M1 = tCara * rCabeza * sCara;
  drawObjectMat(sphere, materialLoader.getPage(), P, V, M * M1);

  glm::mat4 R = glm::rotate   (I, glm::radians(-25.0f), glm::vec3(0,0,1));
  glm::mat4 Ry = glm::rotate   (I, glm::radians(120.0f), glm::vec3(0,1,0));
  glm::mat4 T = glm::translate(I, glm::vec3(1.0, -0.9, 0.2));
  glm::mat4 S = glm::scale    (I, glm::vec3(0.1, 0.1, 0.1));
  glm::mat4 R1 = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1,0,0));
  glm::mat4 T1 = glm::translate(I, glm::vec3(0.0, -1.0, 0.4));
  drawObjectTex(staff, textureLoader.getStaff(), P, V, M * translate2 * rotBrazoManual * translate1 * T1 * T * R1 * Ry * R * S);

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
      case GLFW_KEY_SPACE:
        if(!bookPlaced){
          showBook = true;
          controlBook = !controlBook;
          if (firstTime && !controlBook) firstTime = false;
        }
        break;
      case GLFW_KEY_A:  cameraMovX -= 0.2f;   break; 
      case GLFW_KEY_D:  cameraMovX += 0.2f;   break;
      case GLFW_KEY_S:  cameraMovZ += 0.2f;   break;
      case GLFW_KEY_W:  cameraMovZ -= 0.2f;   break;
      case GLFW_KEY_Q:  cameraMovY += 0.2f;   break;
      case GLFW_KEY_E:  cameraMovY -= 0.2f;   break;
      case GLFW_KEY_R:
        desX = 0.0f;
        desY = 0.0f;
        desZ = 0.0f;
        cameraMovX = 0.0f;
        cameraMovY = 0.0f;
        cameraMovZ = 0.0f;
        sunAngle = 0.0f;
        break;
      // Control del sol (luz direccional)
      case GLFW_KEY_O:  sunAngle -= 5.0f;  break;
      case GLFW_KEY_P:  sunAngle += 5.0f;  break;
      case GLFW_KEY_K:  //interactuar con mesa y lanzar hechizo
        if(!hechizoLanzado){
          if(!bookPlaced){
            if(desX < -3.0f && desZ > 5.8f && desZ < 7.6f && desY < -2.5f && controlBook){
              bookPlaced = true;
              showBook = false;
              controlBook = false;
            }
            else{
              std::cout << "Trata de colocar el libro encima de la mesa y prueba de nuevo" << std::endl;
            }
          }
          else{
            if(desXMage > -5.0f && desXMage < -3.0f && desZMage > -1.0f && desZMage < 1.0f && rotArmMage == -90.0f && mageLookAt == 270.0f){
              hechizoLanzado = true;
            }
            else{
              std::cout << "Trata de acercar el mago a la mesa con el libro colocado y levanta el baston" << std::endl;
            }
          }
        }else{
          hechizoLanzado = false;
        }
      break;
    }  
    if (controlBook){
      switch(key) {
        case GLFW_KEY_LEFT:  
          desX -= 0.2f; 
          if(desX < -4.5f) desX = -4.5f;
          bookLookAt = 90.0f;
          break;
        case GLFW_KEY_RIGHT: 
          desX += 0.2f;   
          if(desX > 8.5f) desX = 8.5f;
          bookLookAt = 90.0f;
          break;
        case GLFW_KEY_UP:     
          desZ -= 0.2f;  
          if(desZ < 0.0f) desZ = 0.0f;
          bookLookAt = 0.0f; 
        break;
        case GLFW_KEY_DOWN:   
          desZ += 0.2f;  
          if(desZ > 12.5f) desZ = 12.5f;
          bookLookAt = 0.0f;   
          break;    
        case GLFW_KEY_X:  
          desY -= 0.2f;  
          if(desY < -4.0f) desY = -4.0f;
          break;
        case GLFW_KEY_Z:  
          desY += 0.2f; 
          if(desY > 2.0f) desY = 2.0f;  
          break;
        }
    }
    if (!controlBook){
      switch(key) {
      case GLFW_KEY_LEFT:  
        desXMage -= 0.2f;
        if(desXMage < -6.0f) desXMage = -6.0f;
        mageLookAt = 270.0f;
        break;
      case GLFW_KEY_RIGHT: 
        desXMage += 0.2f;  
        if(desXMage > 6.0f) desXMage = 6.0f;
        mageLookAt = 90.0f;
        break;
      case GLFW_KEY_DOWN:  
        desZMage += 0.2f; 
        if(desZMage > 6.0f) desZMage = 6.0f;
        mageLookAt = 0.0f;
        break;
      case GLFW_KEY_UP:    
        desZMage -= 0.2f;  
        if(desZMage < -5.6f) desZMage = -5.6f; 
        mageLookAt = 180.0f;
        break;
      case GLFW_KEY_Z:     rotArmMage -= 5.0f; if(rotArmMage < -90.0f) rotArmMage = -90.0f; break;
      case GLFW_KEY_X:     rotArmMage += 5.0f; if(rotArmMage > 60.0f)  rotArmMage = 20.0f;  break;
      }
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
    if(hechizoLanzado){ //parpadeo de pantalla al lanzar hechizo
      outOfCameraTimer += 1; 
      if(outOfCamera1 == 0.0f && outOfCameraTimer > 5){    
        outOfCamera1 = 100.f;
        outOfCamera2 = 0.0f;
        outOfCameraTimer = 0;
      } 
      if(outOfCamera1 == 100.0f && outOfCameraTimer > 5){    
        outOfCamera1 = 0.0f;
        outOfCamera2 = 100.0f;
        outOfCameraTimer = 0;
      }
    }
    t0 = t1;
  }
}

