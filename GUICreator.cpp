#include "dependencies/imgui/imgui.h"
#include "GUICreator.h"
#include "GameManager.h"
#include <type_traits>


namespace GUICreator {

    // Open windows
    bool new_game_window = false;

    // Theme
    bool dark_mode { false }; // Toggle Dark Mode

    // Component names and colours for theming
    enum class UIComponent { Text = 0, WindowBG = 2, PopupBG = 4, Border = 5, FrameBG = 7, TitleBG = 10, TitleBGActive = 11, MenuBarBG = 13, CheckMark = 19, Button = 22, ButtonHovered = 23, ButtonActive = 24 };

    // Difficulty in GUI
    GameManager::Difficulty mines{ GameManager::Difficulty::easy };
    GameManager::Difficulty size { GameManager::Difficulty::easy };

    // Overrides the unary + operator to convert ui_component into an int
    constexpr auto operator+(UIComponent a) noexcept
    {
        return static_cast<std::underlying_type_t<UIComponent>>(a);
    }

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


    void NewGameWindow(bool* p_open, ImGuiStyle& style)
    {
        ImGuiWindowFlags new_game_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        style.WindowBorderSize = 1.f;


        ImGui::Begin("New Game", p_open, new_game_flags);

        ImGui::TextUnformatted("Select Difficulty:");

        using GameManager::Difficulty; // Shorten enum names
        ImGui::Indent();

        if (ImGui::RadioButton("Easy",  mines == Difficulty::easy))    mines = Difficulty::easy;
        if (ImGui::RadioButton("Medium",mines == Difficulty::medium))  mines = Difficulty::medium;
        if (ImGui::RadioButton("Hard",  mines == Difficulty::hard))    mines = Difficulty::hard;

        ImGui::Unindent();

        ImGui::TextUnformatted("Select Size:");

        ImGui::Indent();

        if (ImGui::RadioButton("Small  (20x20)", size == Difficulty::easy))    size = Difficulty::easy;
        if (ImGui::RadioButton("Medium (50x50)", size == Difficulty::medium))  size = Difficulty::medium;
        if (ImGui::RadioButton("Big  (100x100)", size == Difficulty::hard))    size = Difficulty::hard;

        ImGui::Unindent();

        if (ImGui::Button("Start", ImVec2{ 50.f, 20.f }))
        {
            GameManager::NewGame(mines, size);
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

    bool DrawGUI() 
    {
        ImGui::ShowDemoWindow();

        bool close = false; // Exit the program if true
        ImGuiStyle& style{ ImGui::GetStyle() };
        
        style.WindowBorderSize = 0.0f; 
        style.FramePadding = ImVec2(6.f, 6.f);

        // Unary + is overrode to get underlying variable of enums
        if (dark_mode) 
        {
            style.Colors[+UIComponent::Text]           = white;
            style.Colors[+UIComponent::Border]         = white;
            style.Colors[+UIComponent::MenuBarBG]      = d_primary;
            style.Colors[+UIComponent::FrameBG]        = d_primary;
            style.Colors[+UIComponent::TitleBG]        = d_primary;
            style.Colors[+UIComponent::TitleBGActive]  = d_primary;
            style.Colors[+UIComponent::WindowBG]       = d_primary_d;
            style.Colors[+UIComponent::PopupBG]        = d_primary_d;
        }
        else 
        {
            style.Colors[+UIComponent::Text]           = black;
            style.Colors[+UIComponent::Border]         = black;
            style.Colors[+UIComponent::MenuBarBG]      = l_primary_d;
            style.Colors[+UIComponent::FrameBG]        = l_primary_d;
            style.Colors[+UIComponent::TitleBG]        = l_primary_d;
            style.Colors[+UIComponent::TitleBGActive]  = l_primary_d;
            style.Colors[+UIComponent::WindowBG]       = l_primary;
            style.Colors[+UIComponent::PopupBG]        = l_primary;
        }

        style.Colors[+UIComponent::CheckMark]          = secondary;
        style.Colors[+UIComponent::Button]             = secondary;
        style.Colors[+UIComponent::ButtonHovered]      = secondary_l;
        style.Colors[+UIComponent::ButtonActive]       = secondary_d;

        // Create menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("New Game")) new_game_window = !new_game_window;
                if (ImGui::MenuItem("Dark Mode", NULL, dark_mode)) dark_mode = !dark_mode;
                if (ImGui::MenuItem("Quit", "Alt + F4")) close = ExitPopup();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("How To Play")) HowToPopup();
                if (ImGui::MenuItem("About")) AboutPopup();

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Create main window
        static ImGuiWindowFlags main_window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("Main Window", 0, main_window_flags))
        {



        }
        ImGui::End();

        // Open extra windows
        if (new_game_window) NewGameWindow(&new_game_window, style);

        return close;
    }
    
}