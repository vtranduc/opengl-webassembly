#include "../headers/webglHandle.h"

GLuint getShader(const GLchar* source, GLenum type) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    GLint  success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // return 0;

        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "Shader has failed to compiled: " << infoLog << endl;
    }

    return shader;
};

GLuint getShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint  success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Program has failed to link: " << infoLog << endl;
    }

    return program;
};

int WebGLHandle::initialize(char* canvasId, int clearColor) {
    setContextAttribute();
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context
        = emscripten_webgl_create_context(canvasId, &attrs);
    if (context < 0) {
        printf("failed to create webgl context %d\n", context);
        return 0;
    };
    EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(context);
    if (r < 0) {
        printf("failed to make webgl current %d\n", r);
        return 0;
    }
    int purple = 0xff00ff;
    RGB rgb = hexToRGB(clearColor);
    glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    cout << "=== hello triangle starts ===" << endl;

    const GLchar* vertexShaderSource =
        "precision highp float;"
        "\n"
        // "layout (location = 0) in vec3 aPos;"
        "attribute vec3 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 1.0);\n"
    "}\n";

    const GLchar* fragmentShaderSource =
        "precision highp float;"
        "\n"
        "uniform vec3 uColor;\n"
        // "uniform vec3 helloWorld;\n"
        "uniform float r;\n"
        "uniform float b;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vec4(uColor, 1.0);\n"
    "}\n";

    // --------------

    std::string content = "hello hello hello aoru: ";

    // cout << build_number << endl;

    ifstream  f("basic.glsl");

    // fileStream.open(("basicdfadsfdss.glsl"));

    if (f.fail()) {
        cout << "failed???" << endl;
    }

    // // std::ifstream t("file.txt");
    // // std::string buffer;
    // // buffer << t.rdbuf();


    // // ifstream fileStream("../glsl/vertex/basic.glsl", ios::in);

    // // ifstream fileStream("/home/vtranduc/code/may/opengl-webassembly/engine/src/basic.glsl");

    // std::string line = "";

    // if (fileStream.is_open()) {
    //     cout << "12345 file is open right now: " << endl;

    //     while(!fileStream.eof()) {

    //         cout << "aaaaaaaaaa ___" << endl;

    //         getline(fileStream, line);

    //         content.append(line + "\n");
    //     }
        
    //     cout << "now show: " << endl << content << endl;

    //     fileStream.close();
    // } else {
    //     cout << "nope!!!!!!!!!!!!!!!!!" << endl;
    // }

    // if (fileStream.fail()) {
    //     cout << "FAILED --------------" << endl;
    // }

    // return 1;

    // --------------

    GLuint vertexShader = getShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = getShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLuint program = getShaderProgram(vertexShader, fragmentShader);

    GLuint uColorUniformLocation = glGetUniformLocation(program, "uColor");

    cout << "color location: " << uColorUniformLocation << endl;

    float color[3] = { 1.0, 0.0, 1.0 };

    const vec3 hatsune(1.0, 0.0, 0.0);

    

    // glutSwapBuffers();

    // glm::vec4


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glUseProgram(program);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glUniform3fv(uColorUniformLocation, 1, color);

    for (int i = 0; i < 100000; i++) {
        // cout << "looping the color" << endl;

        glClear(GL_COLOR_BUFFER_BIT);

        // if (i >= 100000 - 1) continue;

        glUniform3fv(uColorUniformLocation, 1, color);

        // GLuint r = glGetUniformLocation(program, "r");
        // GLuint b = glGetUniformLocation(program, "b");

        // cout << "loop: " << i << endl;

        // glUniform1f(r, 1.0);
        // glUniform1f(b, 1.0);

        // float tempfloat;
        // glGetUniformfv(program,b,&tempfloat);
        // printf("%f\n",tempfloat); // output depends on glUniform1f, see below

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    cout << "=== end of experiment ===" << endl;

    return 1;
};

int WebGLHandle::setClearColor(int hex) {
    RGB rgb = hexToRGB(hex);
    glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    return 1;
}

void WebGLHandle::setContextAttribute() {
    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;
};