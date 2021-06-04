//
// Created by avalibit on 03/06/2021.
//

#include <SDL.h>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <lib.h>
#include <nfd.h>

int main() {
    interpreter interp;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
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
    ImGui_ImplOpenGL3_Init("#version 130");

    bool running = true;

    Coord curPos = {};
    Colour curColour = {};

    uint8_t min, max;

    while (running) {
        // Input

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }

                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

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
        if ((changedX || changedY || changedZ || changedW) && (interp.space.size()-1 <= curPos.w)) {
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

        if (interp.space.size()-1 <= curPos.w) {
            interp.space[curPos.w][curPos.x][curPos.y][curPos.z] = curColour;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    SDL_DestroyWindow(window);

    SDL_Quit();
}