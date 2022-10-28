#include "GUICreator.h"
#include <iostream>

namespace GUICreator {

    // Open windows
    bool new_game_window = false;

    // Theme
    bool dark_mode { false }; // Toggle Dark Mode

    // Game Variables for GUI
    GameManager::Difficulty mines{ GameManager::Difficulty::easy };
    GameManager::Difficulty size { GameManager::Difficulty::easy };

    std::vector<std::vector<bool>> tile_state { }; // 2D vector

    constexpr ImVec2 tile_size{ 50.f, 50.f };

    // Colour Presets
    constexpr ImVec4 white          { 1.f   , 1.f   , 1.f   , 1.f };
    constexpr ImVec4 black          { 0.f   , 0.f   , 0.f   , 1.f };

    // Dark Mode
    constexpr ImVec4 d_primary      { 0.2f  , 0.2f  , 0.2f  , 1.f };
    constexpr ImVec4 d_primary_l    { 0.427f, 0.427f, 0.427f, 1.f };
    constexpr ImVec4 d_primary_d    { 0.106f, 0.106f, 0.106f, 1.f };

    // Light Mode
    constexpr ImVec4 l_primary      { 0.925f, 0.937f, 0.945f, 1.f };
    constexpr ImVec4 l_primary_d    { 0.729f, 0.741f, 0.745f, 1.f };

    // Secondary Colour
    constexpr ImVec4 secondary      { 0.129f, 0.588f, 0.953f, 1.f };
    constexpr ImVec4 secondary_l    { 0.431f, 0.776f, 1.f   , 1.f };
    constexpr ImVec4 secondary_d    { 0.f   , 0.412f, 0.753f, 1.f };

    // Forward Declarations
    void ResetBoard();
    void DrawBoard();


    void NewGameWindow(bool* p_open)
    {
        ImGuiWindowFlags new_game_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::Begin("New Game", p_open, new_game_flags);

        ImGui::TextUnformatted("Select Difficulty:");

        using GameManager::Difficulty; // Shorten enum names
        ImGui::Indent();

        if (ImGui::RadioButton("Easy",  mines == Difficulty::easy))    mines = Difficulty::easy;
        if (ImGui::RadioButton("Medium",mines == Difficulty::medium))  mines = Difficulty::medium;
        if (ImGui::RadioButton("Hard",  mines == Difficulty::hard))    mines = Difficulty::hard;

        ImGui::Unindent();

        ImGui::Separator();

        ImGui::TextUnformatted("Select Size:");

        ImGui::Indent();

        if (ImGui::RadioButton("Small  (20x20)", size == Difficulty::easy))    size = Difficulty::easy;
        if (ImGui::RadioButton("Medium (50x50)", size == Difficulty::medium))  size = Difficulty::medium;
        if (ImGui::RadioButton("Big  (100x100)", size == Difficulty::hard))    size = Difficulty::hard;

        ImGui::Unindent();

        ImGui::Separator();

        if (ImGui::Button("Start"))
        {
            tile_state = GameManager::NewGame(mines, size);
            new_game_window = false;
        }

        ImGui::End();
    }

    void HowToPopup()
    {



    }

    void AboutPopup()
    {



    }

    bool ExitPopup()
    {
        // Are you sure popup

        return true;
    }

    void StyleMainGUI() 
    {
        ImGuiStyle& style{ ImGui::GetStyle() };

        style.WindowBorderSize = 0.0f;
        style.FramePadding = ImVec2(6.f, 6.f);
        style.ItemSpacing = ImVec2(8.f, 4.f);

        // Unary + is overrode to get underlying variable of enums
        if (dark_mode)
        {
            style.Colors[ImGuiCol_Text]         = white;
            style.Colors[ImGuiCol_Border]       = white;
            style.Colors[ImGuiCol_MenuBarBg]    = d_primary;
            style.Colors[ImGuiCol_FrameBg]      = d_primary;
            style.Colors[ImGuiCol_TitleBg]      = d_primary;
            style.Colors[ImGuiCol_TitleBgActive]= d_primary;
            style.Colors[ImGuiCol_WindowBg]     = d_primary_d;
            style.Colors[ImGuiCol_PopupBg]      = d_primary_d;
        }
        else
        {
            style.Colors[ImGuiCol_Text]         = black;
            style.Colors[ImGuiCol_Border]       = black;
            style.Colors[ImGuiCol_MenuBarBg]    = l_primary_d;
            style.Colors[ImGuiCol_FrameBg]      = l_primary_d;
            style.Colors[ImGuiCol_TitleBg]      = l_primary_d;
            style.Colors[ImGuiCol_TitleBgActive]= l_primary_d;
            style.Colors[ImGuiCol_WindowBg]     = l_primary;
            style.Colors[ImGuiCol_PopupBg]      = l_primary;
        }

        style.Colors[ImGuiCol_CheckMark]        = secondary;
        style.Colors[ImGuiCol_Button]           = secondary;
        style.Colors[ImGuiCol_ButtonHovered]    = secondary_l;
        style.Colors[ImGuiCol_ButtonActive]     = secondary_d;
    }
        
    bool DrawGUI() 
    {
        bool close = false; // Exit the program if true

        ImGui::ShowDemoWindow();
        StyleMainGUI();

        // Create menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("New Game"))                    new_game_window = !new_game_window;
                if (ImGui::MenuItem("Dark Mode", NULL, dark_mode))  dark_mode = !dark_mode;
                if (ImGui::MenuItem("Quit", "Alt + F4"))            close = ExitPopup();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("How To Play")) HowToPopup();
                if (ImGui::MenuItem("About"))       AboutPopup();

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Create main window
        static ImGuiWindowFlags main_window_flags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings };

        const ImGuiViewport* viewport{ ImGui::GetMainViewport() };
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("Main Window", 0, main_window_flags))
        {
            DrawBoard();
        }
        ImGui::End();

        // Open extra windows
        if (new_game_window) NewGameWindow(&new_game_window);

        return close;
    }
    
    void ResetBoard()
    {
        


    }

    void DrawBoard() 
    {
        ImGuiStyle& style{ ImGui::GetStyle() };
        style.ItemSpacing = ImVec2(1.f, 1.f);

        for (int y = 0; y < 10; ++y)
        {
            for (int x = 0; x < 10; ++x)
            {
                if (x > 0) ImGui::SameLine();

                ImGui::PushID(y * x + x);
                ImGui::Button("##", tile_size);
                ImGui::PopID();
            }
        }
        
    }
}