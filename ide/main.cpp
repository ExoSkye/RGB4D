//
// Created by avalibit on 03/06/2021.
//

#include <SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <lib.h>
#include <nfd.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"

bool checkOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
       printf("glError: %s",gluErrorString(glErr));
       foundError = true;
       glErr = glGetError();
    }
    return foundError;
}

void printShaderLog(GLuint shader)
{
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        printf("Shader Info Log: %s",log);
        free(log);
    }
}

int main() {
    interpreter interp;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* window = SDL_CreateWindow("PPEN IDE",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);

    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window,glContext);
    ImGui_ImplOpenGL3_Init("#version 430");

    bool running = true;

    Coord curPos = {};
    Colour curColour = {};

    uint8_t min, max;

    // Shaders

    GLuint vert, frag, shader;

    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);

    const std::string vertStr =
#include "vert.glsl.h"
            ;

    const std::string fragStr =
#include "frag.glsl.h"
            ;

    const char* vertCStr = vertStr.c_str();
    const char* fragCStr = fragStr.c_str();

    glShaderSource(vert,1,&vertCStr,nullptr);
    glShaderSource(frag,1,&fragCStr,nullptr);

    glCompileShader(vert);

#ifdef _DEBUG
    printShaderLog(vert);
#endif

    glCompileShader(frag);

#ifdef _DEBUG
    printShaderLog(frag);
#endif

    shader = glCreateProgram();
    glAttachShader(shader,vert);
    glAttachShader(shader,frag);
    glLinkProgram(shader);

    glUseProgram(shader);

    checkOpenGLError();

    GLuint vao[1];
    GLuint vbo[1];

    glGenVertexArrays(1,vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(1,vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubePositions),cubePositions,GL_STATIC_DRAW);

    glm::mat4 pMat, vMat, mMat, mvMat;
    GLuint mvLoc, projLoc, color;
    glm::vec3 cameraPos{0,0,8};

    mvLoc = glGetUniformLocation(shader,"mv_matrix");
    projLoc = glGetUniformLocation(shader,"proj_matrix");
    color = glGetUniformLocation(shader,"inColor");

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    pMat = glm::perspective(1.0472f,(float)w/(float)h,0.1f,1000.0f);

    checkOpenGLError();
    while (running) {
        // Input

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_w:
                            cameraPos.x++;
                            break;
                        case SDLK_s:
                            cameraPos.x--;
                            break;
                        case SDLK_a:
                            cameraPos.y++;
                            break;
                        case SDLK_d:
                            cameraPos.y--;
                            break;
                        case SDLK_SPACE:
                            cameraPos.z++;
                            break;
                        case SDLK_LSHIFT:
                            cameraPos.z--;
                            break;
                    }
                    printf("%f %f %f",cameraPos.x,cameraPos.y,cameraPos.z);
                    break;

                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_WINDOWEVENT_RESIZED:
                    SDL_GetWindowSize(window, &w, &h);
                    glViewport(0, 0, w, h);
                    pMat = glm::perspective(1.0472f,(float)w/(float)h,0.1f,1000.0f);
            }
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        checkOpenGLError();

        vMat = glm::translate(glm::mat4(1.0f),-cameraPos);
        //vMat = glm::rotate(vMat,glm::radians(45.0f),glm::vec3(0,1,1));
        if (curPos.w < interp.space.size()) {
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    for (int z = 0; z < 16; z++) {
                        glm::vec3 position{x * 1.5, y * 1.5, z * 1.5};
                        Colour colorVal = interp.space[curPos.w][x][y][z];
                        mMat = glm::translate(glm::mat4(1.0f), position);
                        mvMat = vMat * mMat;
                        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
                        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
                        glm::vec4 glmColour = glm::vec4((float) colorVal.r / 255.0f, (float) colorVal.g / 255.0f,
                                                        (float) colorVal.b / 255.0f, (float) colorVal.a / 255.0f);
                        glUniform4fv(color, 1, glm::value_ptr(glmColour));

                        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(0);

                        glEnable(GL_DEPTH_TEST);
                        glDepthFunc(GL_LEQUAL);
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                        checkOpenGLError();
                    }
                }
            }
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        ImGui::Begin("File");
        if(ImGui::Button("Open File")) {
            char* out = nullptr;
            NFD_OpenDialog(nullptr,nullptr,&out);
            auto outstr = std::string(out);
            readFromFile(interp.space, outstr);
            curPos = {0,0,0,0};
            curColour = interp.space[curPos.w][curPos.x][curPos.y][curPos.z];
        }
        if (ImGui::Button("Save")) {
            char* out = nullptr;
            NFD_SaveDialog(nullptr,nullptr,&out);
            auto outstr = std::string(out);
            saveToFile(interp.space, outstr);
        }
        ImGui::End();
        ImGui::Begin("Navigation");
        ImGui::Text("Position");
        min = 0;
        max = 15;
        bool changedX, changedY, changedZ, changedW;
        changedX = ImGui::SliderScalar("X",ImGuiDataType_U8,&curPos.x,&min, &max, "%d");
        changedY = ImGui::SliderScalar("Y",ImGuiDataType_U8,&curPos.y,&min, &max, "%d");
        changedZ = ImGui::SliderScalar("Z",ImGuiDataType_U8,&curPos.z,&min, &max, "%d");
        changedW = ImGui::SliderScalar("W",ImGuiDataType_U8,&curPos.w,&min, &max, "%d");
        if ((changedX || changedY || changedZ || changedW) && (curPos.w < interp.space.size())) {
            curColour = interp.space[curPos.w][curPos.x][curPos.y][curPos.z];

        }
        if(ImGui::Button("Add W Plane")) {
            interp.space.push_back(plane{});
        }
        if(ImGui::Button("Remove W Plane")) {
            interp.space.resize(interp.space.size()-1);
        }
        ImGui::Text("Number of W planes: %zu",interp.space.size());
        min = 0;
        max = 255;
        ImGui::Text("Colour");
        ImGui::SliderScalar("R", ImGuiDataType_U8, &curColour.r, &min, &max, "%d");
        ImGui::SliderScalar("G", ImGuiDataType_U8, &curColour.g, &min, &max, "%d");
        ImGui::SliderScalar("B", ImGuiDataType_U8, &curColour.b, &min, &max, "%d");
        ImGui::SliderScalar("A", ImGuiDataType_U8, &curColour.a, &min, &max, "%d");
        ImGui::End();
        ImGui::Begin("Info");
        ImGui::Text("FPS: %f",io.Framerate);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);

        if (curPos.w < interp.space.size()) {
            interp.space[curPos.w][curPos.x][curPos.y][curPos.z] = curColour;
        }

        checkOpenGLError();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    SDL_DestroyWindow(window);

    SDL_Quit();
}