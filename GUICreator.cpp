#include "GUICreator.h"


namespace GUICreator {

    // Open windows
    bool new_game_window = false;
    bool how_to_window = false;
    bool about_window = false;
    bool game_over_window = false;
    bool victory_window  = false;

    // Game Variables for GUI
    GameManager::Difficulty mines{ GameManager::Difficulty::easy };
    GameManager::Difficulty size { GameManager::Difficulty::easy };
        
    const ImVec2 easy_tile_size     { 62.f , 62.f  };
    const ImVec2 medium_tile_size   { 30.5f, 30.5f };
    const ImVec2 hard_tile_size     { 20.f , 20.f  };
    ImVec2 tile_size{ easy_tile_size };
    
    // Theme
    bool dark_mode { false }; // Toggle Dark Mode

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

    // Special Tile Colours
    constexpr ImVec4 explored_col   { 0.212f, 0.212f, 0.295f, 1.f };
    constexpr ImVec4 mine_col       { 0.892f, 0.112f, 0.353f, 1.f };
    constexpr ImVec4 flagged_col    { 0.892f, 0.612f, 0.253f, 1.f };
    constexpr ImVec4 flagged_minecol{ 0.892f, 0.412f, 0.353f, 1.f };

    // Adjacent Mine Number Colours
    constexpr ImVec4 one_mine_col   { 0.36f , 0.86f , 0.96f , 1.f };
    constexpr ImVec4 two_mine_col   { 0.37f , 0.91f , 0.24f , 1.f };
    constexpr ImVec4 three_mine_col { 0.86f , 0.93f , 0.25f , 1.f };
    constexpr ImVec4 four_mine_col  { 0.97f , 0.56f , 0.13f , 1.f };
    constexpr ImVec4 five_mine_col  { 0.95f , 0.24f , 0.25f , 1.f };
    constexpr ImVec4 six_mine_col   { 0.98f , 0.06f , 0.32f , 1.f };
    constexpr ImVec4 seven_mine_col { 0.96f , 0.27f , 0.78f , 1.f };
    constexpr ImVec4 eight_mine_col { 0.73f , 0.19f , 0.91f , 1.f };

    // Forward Declarations
    void NewGameWindow(bool* p_open);
    void HowToWindow(bool* p_open);
    void GameOverWindow(bool* p_open);
    void VictoryWindow(bool* p_open);
    void AboutWindow(bool* p_open);
    void StyleMainGUI(); 
    bool DrawGUI();
    void DrawBoard();
    const char* GetTileLable(GameManager::TileState state);


    void NewGameWindow(bool* p_open)
    {
        ImGuiWindowFlags new_game_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::SetNextWindowFocus();
        ImGui::Begin("New Game", p_open, new_game_flags);

        ImGui::TextUnformatted("Select Difficulty:");

        using GameManager::Difficulty; // Shorten enum names
        ImGui::Indent();

        if (ImGui::RadioButton("Easy", mines == Difficulty::easy))      mines = Difficulty::easy;
        if (ImGui::RadioButton("Medium", mines == Difficulty::medium))  mines = Difficulty::medium;
        if (ImGui::RadioButton("Hard", mines == Difficulty::hard))      mines = Difficulty::hard;

        ImGui::Unindent();

        ImGui::Separator();

        ImGui::TextUnformatted("Select Size:");

        ImGui::Indent();

        if (ImGui::RadioButton("Small  (10x10)", size == Difficulty::easy))    size = Difficulty::easy;
        if (ImGui::RadioButton("Medium (20x20)", size == Difficulty::medium))  size = Difficulty::medium;
        if (ImGui::RadioButton("Big    (40x40)", size == Difficulty::hard))    size = Difficulty::hard;

        ImGui::Unindent();

        ImGui::TextUnformatted("");

        if (ImGui::Button("Start"))
        {
            GameManager::NewGame(mines, size);
            
            if      (size == Difficulty::easy)   tile_size = easy_tile_size;
            else if (size == Difficulty::medium) tile_size = medium_tile_size;
            else if (size == Difficulty::hard)   tile_size = hard_tile_size;
            
            new_game_window = false;
        }

        ImGui::End();
    }

    void HowToWindow(bool* p_open)
    {
        ImGuiWindowFlags how_to_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::SetNextWindowFocus();
        ImGui::Begin("How to Play", p_open, how_to_flags);

        ImGui::TextUnformatted("The objective of Minesweeper is to expose all non-mine tiles\n");

        ImGui::Button("##", ImVec2{ 62.f, 62.f });

        ImGui::SameLine();
        
        ImGui::TextUnformatted(" <-- This is a tile \n To expose a tile, click on it\n\n Clicking on a mine is game-over");

        ImGui::TextUnformatted("\nMines are randomly placed but there is a way to guess where they are!");
        ImGui::TextUnformatted("When you reveal a tile, if it isn't a mine it will tell you how many");
        ImGui::TextUnformatted("tiles around it is a mine:");

        ImGui::PushStyleColor(ImGuiCol_Button,          explored_col);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    explored_col);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   explored_col);
        ImGui::PushStyleColor(ImGuiCol_Text,            two_mine_col);

        ImGui::Button("2", ImVec2{ 62.f, 62.f });

        ImGui::PopStyleColor(4);

        ImGui::SameLine();

        ImGui::TextUnformatted(" <-- This tile has two mines neighbouring it");

        ImGui::TextUnformatted("\nIf you know a tile is a mine, you can right-click it to flag it. Flagged");
        ImGui::TextUnformatted("tiles can't be clicked so it's a good way of keeping track of mines:");

        ImGui::PushStyleColor(ImGuiCol_Button,          flagged_col);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    flagged_col);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   flagged_col);

        ImGui::Button("##", ImVec2{ 62.f, 62.f });

        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        ImGui::TextUnformatted(" <-- This is a flagged tile");
        
        ImGui::TextUnformatted("\nUsing the middle mouse button will clear all unflagged tiles around the"
                               "\nclicked tile, only if there are the same amount or more flagged tiles"
                               "\naround it, as indicated on the tile. If a mine is cleared this way it'll"
                               "\nresult in a game-over so be careful!");

        ImGui::TextUnformatted("\nGood luck!");

        ImGui::End();
    }

    void GameOverWindow(bool* p_open)
    {
        ImGuiWindowFlags victory_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::SetNextWindowFocus();
        ImGui::Begin("Game over!", p_open, victory_flags);

        ImGui::TextUnformatted("Oops, you stepped on a mine!");
        ImGui::TextUnformatted("");

        if (ImGui::Button("Try Again?"))
        {
            new_game_window = true;
            *p_open = false;
        }

        ImGui::End();
    }

    void VictoryWindow(bool* p_open) 
    {
        ImGuiWindowFlags victory_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::SetNextWindowFocus();
        ImGui::Begin("You Win!", p_open, victory_flags);

        ImGui::TextUnformatted("Congratulations!");
        ImGui::TextUnformatted("");

        if (ImGui::Button("Play Again"))
        {
            new_game_window = true;
            *p_open = false;
        }

        ImGui::End();
    }

    void AboutWindow(bool* p_open)
    {
        ImGuiWindowFlags about_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::SetNextWindowFocus();
        ImGui::Begin("About", p_open, about_flags);

        ImGui::TextUnformatted("Minesweeper, written in C++");
        ImGui::TextUnformatted("Makes use of the GUI library Dear ImGui");
        
        ImGui::PushStyleColor(ImGuiCol_Button,          dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_Text, secondary);
        
        if (ImGui::Button("Github")) system("start https://github.com/DillaDJ/Minesweeper"); 
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        ImGui::PopStyleColor(4);

        ImGui::SameLine();
        ImGui::TextUnformatted(" | ");
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button,          dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   dark_mode ? d_primary_d : l_primary);
        ImGui::PushStyleColor(ImGuiCol_Text, secondary);

        if (ImGui::Button("Dear ImGui")) system("start https://github.com/ocornut/imgui");
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        ImGui::PopStyleColor(4);

        ImGui::TextUnformatted("Dylan Jansen 2022");

        ImGui::End();
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
#ifdef _DEBUG
        ImGui::ShowDemoWindow();
#endif
        bool done = false; // Exit the program if true

        StyleMainGUI();

        // Create menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("New Game"))                    new_game_window = !new_game_window;
                if (ImGui::MenuItem("Dark Mode", NULL, dark_mode))  dark_mode = !dark_mode;
                if (ImGui::MenuItem("Quit", "Alt + F4"))            done = true;

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("How To Play")) how_to_window = !how_to_window;
                if (ImGui::MenuItem("About"))       about_window = !about_window;

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Create main window
        static ImGuiWindowFlags main_window_flags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize };

        const ImGuiViewport* viewport{ ImGui::GetMainViewport() };
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("Main Window", 0, main_window_flags))
        {
            DrawBoard();
        }
        ImGui::End();

        // Open extra windows
        if (new_game_window)    NewGameWindow(&new_game_window);
        if (how_to_window)      HowToWindow(&how_to_window);
        if (about_window)       AboutWindow(&about_window);
        if (game_over_window)   GameOverWindow(&game_over_window);
        if (victory_window)     VictoryWindow(&victory_window);

        return done;
    }

    void DrawBoard() 
    {
        ImGuiStyle& style{ ImGui::GetStyle() };
        style.ItemSpacing = ImVec2(1.f, 1.f);

        int dimensions{ GameManager::GetDimensions() };
        if (!GameManager::IsGenerated()) GameManager::NewGame(mines, size);

        for (int y = 0; y < dimensions; ++y)
        {
            for (int x = 0; x < dimensions; ++x)
            {
                using GameManager::TileState;

                int id{ y * dimensions + x }; // 2D to 1D
                int color_count{ 0 };

                if (x > 0) ImGui::SameLine();

                ImGui::PushID(id);
                
                // Color based on mine, explored or untouched
                TileState tilestate{ GameManager::GetTileState(id) };
                
                // Colour special color change on gameover
                if (GameManager::IsGameOver())
                {
                    switch (tilestate)
                    {
                        case TileState::mine:
                            ImGui::PushStyleColor(ImGuiCol_Button,          mine_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    mine_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   mine_col);
                            color_count += 3;
                            break;
                        case TileState::unexplored:
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    secondary);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   secondary);
                            color_count += 2;
                            break;
                        case TileState::flagged_mine:
                            ImGui::PushStyleColor(ImGuiCol_Button,          flagged_minecol);
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    flagged_minecol);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   flagged_minecol);
                            color_count += 3;
                            break;
                        case TileState::flagged_tile:
                            ImGui::PushStyleColor(ImGuiCol_Button,          flagged_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    flagged_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   flagged_col);
                            color_count += 3;
                            break;
                    }
                }

                // Colour numbers on tiles and flagged tiles
                switch (tilestate) 
                {
                    case TileState::flagged_mine:
                        if (!GameManager::IsGameOver())
                        {
                            ImGui::PushStyleColor(ImGuiCol_Button,          flagged_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    flagged_col);
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   flagged_col);
                            color_count += 3;
                        }
                        break;
                    case TileState::flagged_tile:
                        ImGui::PushStyleColor(ImGuiCol_Button,          flagged_col);
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    flagged_col);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   flagged_col);
                        color_count += 3;
                        break;
                    case TileState::one_adjacent_mine:
                        ImGui::PushStyleColor(ImGuiCol_Text, one_mine_col);
                        break;
                    case TileState::two_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, two_mine_col);
                        break;
                    case TileState::three_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, three_mine_col);
                        break;
                    case TileState::four_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, four_mine_col);
                        break;
                    case TileState::five_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, five_mine_col);
                        break;
                    case TileState::six_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, six_mine_col);
                        break;
                    case TileState::seven_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, seven_mine_col);
                        break;
                    case TileState::eight_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, eight_mine_col);
                        break;
                }

                // Colour explored (even numbered ones) tiles
                if (tilestate != TileState::mine && tilestate != TileState::unexplored && tilestate != TileState::flagged_tile && tilestate != TileState::flagged_mine)
                {
                    bool numbered{ tilestate != TileState::no_adjacent_mines && tilestate != TileState::flagged_tile && tilestate != TileState::flagged_mine };
                    
                    if (numbered) // Pop text color
                        ++color_count;
                    
                    ImGui::PushStyleColor(ImGuiCol_Button,          explored_col);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    explored_col);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   explored_col);
                    
                    color_count += 3;
                }
                
                // Generate tile
                const char* tile_label = GetTileLable(tilestate);

                if (ImGui::Button(tile_label, tile_size))
                {
                    GameManager::ProcessTile(id);

                    if (GameManager::IsVictory())  victory_window   = true;
                    if (GameManager::IsGameOver()) game_over_window = true;
                }

                // Process neighbouring tiles (mmb)
                if (ImGui::IsItemClicked(2))
                {
                    GameManager::ProcessNeighbouringTiles(id);

                    if (GameManager::IsVictory())  victory_window = true;
                    if (GameManager::IsGameOver()) game_over_window = true;
                }

                // Flag tile (rmb)
                if (ImGui::IsItemClicked(1))
                {
                    GameManager::FlagTile(id);
                }

                // Pop all color styles
                ImGui::PopStyleColor(color_count);
                
                ImGui::PopID();
            }
        }
        
    }

    const char* GetTileLable(GameManager::TileState state)
    {
        const char* lable{};

        switch (state)
        {
            case GameManager::TileState::one_adjacent_mine:
                lable = "1";
                break;
            case GameManager::TileState::two_adjacent_mines:
                lable = "2";
                break;
            case GameManager::TileState::three_adjacent_mines:
                lable = "3";
                break;
            case GameManager::TileState::four_adjacent_mines:
                lable = "4";
                break;
            case GameManager::TileState::five_adjacent_mines:
                lable = "5";
                break;
            case GameManager::TileState::six_adjacent_mines:
                lable = "6";
                break;
            case GameManager::TileState::seven_adjacent_mines:
                lable = "7";
                break;
            case GameManager::TileState::eight_adjacent_mines:
                lable = "8";
                break;
            default:
                lable = "##";
                break;
        }

        return lable;
    }
}