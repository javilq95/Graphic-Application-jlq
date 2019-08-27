/*
 * File:   PagRenderer.cpp
 * Author: Javier López Quesada
 */
#include "PagRenderer.h"

// Aquí se inicializa el singleton. Todavía no se construye
// el objeto de la clase PagRenderer porque se usa inicialización
// perezosa (lazy initialization).
// La primera vez que se consulte el singleton se inicializará.
PagRenderer * PagRenderer::instance = nullptr;

/**
 * @brief Constructor por defecto de PagRenderer
 */
PagRenderer::PagRenderer() {
}

/**
 * @brief Destructor por defecto de PagRenderer
 */
PagRenderer::~PagRenderer() {
	delete camera;
	delete escene;
}

/**
 * @brief Método que se encarga de redibujar el área OpenGL. Será llamado desde el callback
		  void window_refresh_callback(GLFWwindow *window). Por ahora lo único que hace es
		  borrar el área de dibujo OpenGL con la orden glClear. En próximas prácticas se irá completando.
 */
void PagRenderer::refreshCallback() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	std::cout << "Refresh callback called" << std::endl;

	glm::mat4 viewProjMatrix = camera->getViewProj();
	glm::mat4 viewMatrix = camera->getView();

	switch (modeShader) {
	case 0:
		//Activamos el shader program que se va a usar.
		pointShader.use();
		//Asignamos los parámetros de tipo uniform del shader program. Cada shader program tiene su propio conjunto de parámetros.
		pointShader.setUniform("pointSize", 4.0f);
		pointShader.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));
		escene->drawAsPoints(&pointShader, viewProjMatrix);
		break;
	case 1:
		trianglesShader.use();
		trianglesShader.setUniform("mModelViewProj", viewProjMatrix);
		escene->drawAsTriangles(&trianglesShader, viewProjMatrix, viewMatrix);
		break;
	case 2:
		wiresShader.use();
		wiresShader.setUniform("mModelViewProj", viewProjMatrix);
		escene->drawAsLines(&wiresShader, viewProjMatrix);
		break;
	case 3:
		debugShader.use();
		debugShader.setUniform("debugOption", modeDebug);
		debugShader.setUniform("mModelViewProj", viewProjMatrix);
		escene->drawAsTriangles(&debugShader, viewProjMatrix, viewMatrix);
		break;
	case 4:
		adsShader.use();
		if (modeLight <= 2) {
			lights[modeLight]->shaderApplicator(&adsShader, viewMatrix);
			escene->drawAsTriangles(&adsShader, viewProjMatrix, viewMatrix);
		} 
		else {
			for (int i = 0; i < lights.size(); i++) {
				lights[i]->shaderApplicator(&adsShader, viewMatrix);
				escene->drawAsTriangles(&adsShader, viewProjMatrix, viewMatrix);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			}
		}
		break;
	case 5:
		textureShader.use();
		textureShader.setUniform("TexSamplerColor", 0);
		textureShader.setUniform("TexSamplerShininess", 1);

		for (int i = 0; i < lights.size(); i++) {
			lights[i]->shaderApplicator(&textureShader, viewMatrix);
			escene->drawAsTriangles(&textureShader, viewProjMatrix, viewMatrix);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
		break;
	}
}

/**
 * @brief Método que se encarga de cambiar el tamaño del área de dibujo OpenGL. Será llamado desde el callback
		  void framebuffer_size_callback(GLFWwindow *window, int width, int height). Por ahora lo único que hace es
		  inicializar el viewport.
 */
void PagRenderer::framebuffer_size_callback(int width, int height) {
	glViewport(0, 0, width, height);
	camera->setWidth(width);
	camera->setHeight(height);
	std::cout << "Resize callback called" << std::endl;
}

/**
 * @brief Método que se encarga del uso de las teclas dirigidas al área OpenGL. Será llamado desde el callback
		  void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods). Por ahora lo único que hace es
		  administrar la salida por teclado.
 */
void PagRenderer::key_callback(int key, int scancode, int action, int mods) {
	switch (key) {
	case 'P':
		//modo puntos
		modeShader = 0;
		break;
	case 'M':
		//modo mallatriang
		modeShader = 1;
		break;
	case 'W':
		//modo alambre
		modeShader = 2;
		break;
	case 'N':
		//vernormales
		modeShader = 3;
		modeDebug = 0;
		break;
	case 'T':
		//vertang
		modeShader = 3;
		modeDebug = 1;
		break;
	case 'C':
		//vercoordtext
		modeShader = 3;
		modeDebug = 2;
		break;
	case 'A':
		//luz ambiental
		modeShader = 4;
		modeLight = 0;
		break;
	case 'F':
		//luz spot
		modeShader = 4;
		modeLight = 1;
		break;
	case 'D':
		//luz puntual
		modeShader = 4;
		modeLight = 2;
		break;
	case 'L':
		//luz total
		modeShader = 4;
		modeLight = 3;
		break;
	case 'X':
		//texturas
		modeShader = 5;
		break;
	case '0':
		//stop
		modeMov = 0;
		break;
	case '1':
		//orbit
		modeMov = 1;
		break;
	case '2':
		//pan
		modeMov = 2;
		break;
	case '3':
		//truck
		modeMov = 3;
		break;
	case '4':
		//crane
		modeMov = 4;
		break;
	case '5':
		//dolly
		modeMov = 5;
		break;
	case '6':
		if (cameraChange) {
			glm::vec3 pos(20.0f, 10.0f, 0.0f);
			glm::vec3 ref(0.0f, 0.0f, 0.0f);
			glm::vec3 up(0.0f, 1.0f, 0.0f);
			camera->setCamera(pos, ref, up, 60.0f, 0.1f, 150.0f, 1024.0f, 576.0f);
		}
		else {
			glm::vec3 pos(0.0f, 20.0f, 0.0f);
			glm::vec3 ref(0.0f, 0.0f, 0.0f);
			glm::vec3 up(1.0f, 0.0f, 0.0f);
			camera->setCamera(pos, ref, up, 60.0f, 0.1f, 150.0f, 1024.0f, 576.0f);
		}
		cameraChange = !cameraChange;
		break;
	default:
		std::cout << "Key callback called" << std::endl;
	}
}

/**
 * @brief Método que se encarga del uso del ratón en el área OpenGL. Será llamado desde el callback
		  void mouse_button_callback(GLFWwindow *window, int button, int action, int mods). Por ahora lo único que hace es
		  mostrar cuando se pulsa y se suelta el ratón.
 */
void PagRenderer::mouse_button_callback(int button, int action, int mods) {
	if (action == 1) {
		std::cout << "Pulsado el boton: " << button << std::endl;
	}
	else if (action == 0) {
		std::cout << "Soltado el boton: " << button << std::endl;
	}
}


/**
 * @brief Método que se encarga del uso de la rueda de ratón en el área OpenGL.
		  Será llamado desde el callback void scroll_callback(GLFWwindow *window, double xoffset, double yoffset).
		  Por ahora lo único que hace es mostrar las unidades en horizontal y vertical.
 */
void PagRenderer::scroll_callback(double xoffset, double yoffset) {
	std::cout << "Movida la rueda del raton " << xoffset <<
		" Unidades en horizontal y " << yoffset << " unidades en vertical" << std::endl;
	if (yoffset == 1) {
		camera->movZoom(-0.5f);
	}
	else {
		camera->movZoom(0.5f);
	}
}

/**
 * @brief Método que se encarga del cálculo de la posición del cursor.
		  Será llamado desde el callback cursor_position_callback(GLFWwindow *window, double xpos, double ypos).
		  Llama a los distintos movimientos de la cámara.
 */
void PagRenderer::cursorPositionCallback(double xpos, double ypos) {

	switch (modeMov) {
	case 1:
		camera->movOrbit(xpos, cursorX, ypos, cursorY);
		break;
	case 2:
		camera->movPan(xpos, cursorX, ypos, cursorY);
		break;
	case 3:
		camera->movTruck(xpos, cursorX, ypos, cursorY);
		break;
	case 4:
		camera->movCrane(xpos, cursorX, ypos, cursorY);
		break;
	case 5:
		camera->movDolly(xpos, cursorX, ypos, cursorY);
		break;
	}

	//Actualizamos para que se guarde la última posición del cursor
	cursorX = xpos;
	cursorY = ypos;
}

/**
 * @brief Acceder al singleton. Si es la primera vez que se llama a este método de clase instance es nullptr
		  y se construye. Es lo que se llama inicialización perezosa. Sólo se inicializa cuando se necesita.
 * @return puntero a PagRenderer
 */
PagRenderer * PagRenderer::getInstance() {
	if (!instance) {
		instance = new PagRenderer();
	}
	return instance;
}
/**
 * @brief Método encargado de preparar la escena de visualización
 */
void PagRenderer::prepareOpenGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);

	//Definimos los puntos de perfil del jarrón
	std::vector<glm::vec2> vJarron;
	vJarron.push_back(glm::vec2(0, 0));
	vJarron.push_back(glm::vec2(2, 0));
	vJarron.push_back(glm::vec2(4, 1));
	vJarron.push_back(glm::vec2(2, 2));
	vJarron.push_back(glm::vec2(4, 3));
	vJarron.push_back(glm::vec2(2, 4));
	vJarron.push_back(glm::vec2(4, 5));
	vJarron.push_back(glm::vec2(2, 6));
	vJarron.push_back(glm::vec2(4, 7));

	////Definimos los puntos de perfil de la peonza
	std::vector<glm::vec2> vPeonza;
	vPeonza.push_back(glm::vec2(0, 0));
	vPeonza.push_back(glm::vec2(0.1, 0));
	vPeonza.push_back(glm::vec2(0.25, 0.75));
	vPeonza.push_back(glm::vec2(0.5, 1));
	vPeonza.push_back(glm::vec2(1, 1.5));
	vPeonza.push_back(glm::vec2(1.25, 2));
	vPeonza.push_back(glm::vec2(1.6, 2.25));
	vPeonza.push_back(glm::vec2(1.75, 2.5));
	vPeonza.push_back(glm::vec2(1.6, 2.75));
	vPeonza.push_back(glm::vec2(1.25, 3));
	vPeonza.push_back(glm::vec2(1, 3.5));
	vPeonza.push_back(glm::vec2(0.75, 3.75));
	vPeonza.push_back(glm::vec2(0.5, 4));
	vPeonza.push_back(glm::vec2(0.2, 4.5));
	vPeonza.push_back(glm::vec2(0.2, 5));
	vPeonza.push_back(glm::vec2(0, 5));

	//Definimos los puntos de perfil de la linterna
	std::vector<glm::vec2> vLinterna;
	vLinterna.push_back(glm::vec2(0, 0));
	vLinterna.push_back(glm::vec2(1, 0));
	vLinterna.push_back(glm::vec2(1, 6));
	vLinterna.push_back(glm::vec2(2, 7));
	vLinterna.push_back(glm::vec2(1.75, 7));
	vLinterna.push_back(glm::vec2(0.75, 6));
	vLinterna.push_back(glm::vec2(0, 6));

	//Definimos los puntos de perfil de la bombilla
	std::vector<glm::vec2> vBombilla;
	vBombilla.push_back(glm::vec2(0, 6));
	vBombilla.push_back(glm::vec2(0.75, 6));
	vBombilla.push_back(glm::vec2(0.7, 6.25));
	vBombilla.push_back(glm::vec2(0.56, 6.5));
	vBombilla.push_back(glm::vec2(0.27, 6.7));
	vBombilla.push_back(glm::vec2(0, 6.75));

	//Rellenamos la biblioteca de materiales
	PagMaterial *m1 = new PagMaterial(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 400);
	PagLibraryMaterial::getInstance()->insertMaterial("Azul", m1);

	PagMaterial *m2 = new PagMaterial(glm::vec3(0.7f, 0.6f, 0.2f), glm::vec3(0.7f, 0.6f, 0.2f), 200);
	PagLibraryMaterial::getInstance()->insertMaterial("Beige", m2);

	PagMaterial *m3 = new PagMaterial(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 200);
	PagLibraryMaterial::getInstance()->insertMaterial("Rojo", m3);

	PagMaterial *m4 = new PagMaterial(glm::vec3(0.9f, 0.85f, 0.0f), glm::vec3(0.9f, 0.85f, 0.0f), 200);
	PagLibraryMaterial::getInstance()->insertMaterial("Amarillo", m4);

	PagMaterial *m5 = new PagMaterial(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10);
	PagLibraryMaterial::getInstance()->insertMaterial("Blanco", m5);

	//Rellenamos la biblioteca de texturas
	PagTexture *t1 = new PagTexture("TextureDirectory/Estampado",GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	PagLibraryTexture::getInstance()->insertTexture("Estampado", t1);

	PagTexture *t2 = new PagTexture("TextureDirectory/Madera", GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	PagLibraryTexture::getInstance()->insertTexture("Madera", t2);

	PagTexture *t3 = new PagTexture("TextureDirectory/Plastico", GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	PagLibraryTexture::getInstance()->insertTexture("Plastico", t3);

	PagTexture *t4 = new PagTexture("TextureDirectory/Luz", GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	PagLibraryTexture::getInstance()->insertTexture("Luz", t4);

	PagTexture *t5 = new PagTexture("TextureDirectory/Marmol", GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	PagLibraryTexture::getInstance()->insertTexture("Marmol", t5);

	//Definimos los objetos de la escena
	PagPlane *plane = new PagPlane(20.0f, 20.0f, 10, 10);
	PagRevolutionObject *obj1 = new PagRevolutionObject(vJarron, 3, 50);
	PagRevolutionObject *obj2 = new PagRevolutionObject(vPeonza, 3, 50);
	PagRevolutionObject *obj3 = new PagRevolutionObject(vLinterna, 0, 50);
	PagRevolutionObject *obj4 = new PagRevolutionObject(vBombilla, 3, 50);

	//Asignamos los materiales
	obj1->setMaterial(PagLibraryMaterial::getInstance()->getMaterial("Azul"));
	obj2->setMaterial(PagLibraryMaterial::getInstance()->getMaterial("Beige"));
	obj3->setMaterial(PagLibraryMaterial::getInstance()->getMaterial("Rojo"));
	obj4->setMaterial(PagLibraryMaterial::getInstance()->getMaterial("Amarillo"));
	plane->setMaterial(PagLibraryMaterial::getInstance()->getMaterial("Blanco"));

	//Asignamos las texturas
	obj1->getMaterial().setTexture(PagLibraryTexture::getInstance()->getTexture("Estampado"));
	obj2->getMaterial().setTexture(PagLibraryTexture::getInstance()->getTexture("Madera"));
	obj3->getMaterial().setTexture(PagLibraryTexture::getInstance()->getTexture("Plastico"));
	obj4->getMaterial().setTexture(PagLibraryTexture::getInstance()->getTexture("Luz"));
	plane->getMaterial().setTexture(PagLibraryTexture::getInstance()->getTexture("Marmol"));

	//Transformamos los objetos
	plane->translate(glm::vec3(-10.0f, 0.0f, -10.0f));

	obj1->translate(glm::vec3(-5.0f, 0.0f, -5.0f));
	obj1->scale(glm::vec3(0.75f, 0.75f, 0.75f));

	obj2->translate(glm::vec3(3.7f, 0.0f, -6.0f));
	obj2->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	obj2->rotate(glm::vec3(1.0, 0.0, 0.0), 45);

	obj3->scale(glm::vec3(0.75f, 0.75f, 0.75f));
	obj3->translate(glm::vec3(5.0f, 1.0f, 5.0f));
	obj3->rotate(glm::vec3(1.0, 0.0, 0.0), 278);

	obj4->scale(glm::vec3(0.75f, 0.75f, 0.75f));
	obj4->translate(glm::vec3(5.0f, 1.0f, 5.0f));
	obj4->rotate(glm::vec3(1.0, 0.0, 0.0), 278);
	
	//Inserción en la escena
	escene = new Pag3DGroup();
	escene->insertElement(obj1);
	escene->insertElement(obj2);
	escene->insertElement(obj3);
	escene->insertElement(obj4);
	escene->insertElement(plane);

	//Creamos los distintos shader program
	pointShader.createShaderProgram("pointShader");
	trianglesShader.createShaderProgram("trianglesShader");
	wiresShader.createShaderProgram("wiresShader");
	debugShader.createShaderProgram("debugShader");
	adsShader.createShaderProgram("adsShader");
	textureShader.createShaderProgram("textureShader");

	//Inicialización de la cámara
	glm::vec3 pos(20.0f, 10.0f, 0.0f);
	glm::vec3 ref(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	float fovy = 60.0f;
	float znear = 0.1f;
	float zfar = 150.0f;
	float ancho = 1024.0f;
	float alto = 576.0f;
	camera = new PagCamera(pos, ref, up, fovy, znear, zfar, ancho, alto);
	
	//Definición de luces
	PagAmbientLight *a = new PagAmbientLight(glm::vec3(0.1, 0.1, 0.1));
	lights.push_back(a);

	PagSpotLight *s = new PagSpotLight(glm::vec3(0.6, 0.6, 0.4), glm::vec3(0.4, 0.4, 0.3),
		glm::vec3(0.0, 0.0, -1.0), glm::vec3(3.7, 1.5, -1.2), 1.0f, 50.0f, 0.0f, 0.0f, 0.0f);
	lights.push_back(s);

	PagPuntualLight *p = new PagPuntualLight(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.0, 10.0, 0.0), 0.0f, 0.0f, 0.0f);
	lights.push_back(p);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}