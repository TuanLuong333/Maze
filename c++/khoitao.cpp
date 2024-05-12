
#include"Time.h"

BaseObject bg;
GameMap game_map;
Slime player;
Text textofgame;
BaseObject pause;
Time timer;
Time buff_count;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "Unable to init the SDL" << SDL_GetError()<<endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    window = SDL_CreateWindow("SLIME GO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        cout << "window gets null " << endl;
        return false;
    }

    ss = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (ss == nullptr)
    {
        cout << "renderer ss is null"<<endl;
        return false;
    }

    SDL_SetRenderDrawColor(ss, 255, 255, 255, 255);

    if (!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG))
    {
        cout << "Unable to init the img" << IMG_GetError() << endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        cout << "sai cai ttf";
        return false;
    }
    g_font_text = TTF_OpenFont("Font//Starcraft Normal.ttf", 20);
    pause_font_text = TTF_OpenFont("Font//Starcraft Normal.ttf", 20);

    if (g_font_text == nullptr)
    {
        cout << "font text is null";
        return false;
    }

    return true;
}

void close()
{
    TTF_CloseFont(g_font_text);
    TTF_CloseFont(pause_font_text);
    bg.Free();
    SDL_DestroyRenderer(ss);
    ss = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyTexture(gem);
    gem = nullptr;
    SDL_DestroyTexture(menu_img);
    menu_img = nullptr;

    Mix_FreeChunk(move_sound);
    Mix_FreeChunk(button_click);
    Mix_FreeChunk(P_sound);
    Mix_FreeChunk(win_sound);
    Mix_FreeMusic(game_music);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

bool LoadBackground() {

    bool OK = bg.LoadImg("C://Users//ASUS//source//repos//Project1//image//battleground3.png", ss);

    if (!OK) {
        cout << "background is unalble to be updated" << endl;
        return false;
    }
    return true;
}

bool Loadpausescreen() {

    bool OK = pause.LoadImg("C://Users//ASUS//Pictures//Screenshots//water1_00036.png", ss);

    if (!OK) {
        cout << "background is unalble to be updated" << endl;
        return false;
    }
    return true;
}

void LoadMusic()
{
    game_music = Mix_LoadMUS("gamesound//mixkit-game-level-music-689.wav");
    if (game_music == NULL)
    {
        cout<<"Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError();
    }

    P_sound = Mix_LoadWAV("gamesound//mixkit-arcade-mechanical-bling-210.wav");
    if (P_sound == NULL)
    {
        cout<<"1Failed to load button click effect! SDL_mixer Error: %s\n", Mix_GetError();
    }

    win_sound = Mix_LoadWAV("gamesound//mixkit-completion-of-a-level-2063.wav");
    if (win_sound == NULL)
    {
        cout<<"1Failed to load button click effect! SDL_mixer Error: %s\n", Mix_GetError();
    }
}

int main(int argc, char* args[])
{

    if (!init()) {
        cout << " init() failed"<<endl;
        return -1;
    }

    if (!LoadBackground()) {
        cout << "loadbackground() failed"<<endl;
        return -1;
    }

    if (!Loadpausescreen()) {
        cout << "loadpausescreen() failed" << endl;
        return -1;
    }

    LoadMusic();

    Mix_PlayMusic(game_music, -1);

    

    bool quit = false;
    int pause_point = 0;
    int again = 0;
    int refresh_point = 0;
    int back_point = 0;

    player.LoadImg("movement//B_right.png", ss);
    player.SetClips();
    player.GenerateWalkSkin();

    int get_menu = textofgame.DemoMenu(ss, g_font_text);

    while(get_menu != 0)
    {
        if (back_point == 1)
        {
            back_point = 0;
            get_menu = textofgame.DemoMenu(ss, g_font_text);
        }

        if (get_menu == 1)
        {
            quit = true;
            break;
        }
        else if (get_menu == 2)
        {
            int get_skin = textofgame.SkinShow(ss, g_font_text);
            if (get_skin == 3)
            {
                back_point = 1;
            }
            else if (get_skin == 0)
            {
                player.SetSkinColor(1);//blue
                cout << "pick blue skin" << endl;
            }
            else if (get_skin == 1)
            {
                player.SetSkinColor(2);//green
                player.LoadImg("movement//G_right.png", ss); // link of green slime
                cout << "pick green skin" << endl;
            }
            else if(get_skin == 2)
            {
                player.SetSkinColor(3);//red
                player.LoadImg("movement//R_right.png", ss);// link of red slime
                cout << "pick red skin" << endl;
            }
            else if (get_skin == 5)//SDL_Quit
            {
                quit = true;
                break;
            }
            else if (get_skin == 4)//Play when finishing choosing skin
            {
                get_menu = 0;
            }
        }
        else if (get_menu == 3)
        {
            int get_level = textofgame.SelectLevel(ss, g_font_text);
            if (get_level == 0)
            {
                game_level = 1;
                get_menu = 0;
            }
            else if (get_level == 1)
            {
                game_level = 2;
                get_menu = 0;
            }
            else if (get_level == 2) back_point = 1; // back menu
            else if (get_level == 3) get_menu = 0;
            else if (get_level == -1)
            {
                quit = true;
                break;
            }
        }
    }

    string link;
    //player.SetClips();
    if(game_level == 1) 
        link = "C://Users//ASUS//source//repos//Project1//map//map00.txt";
    else if(game_level == 2) 
        link = "C://Users//ASUS//source//repos//Project1//map//map02.txt";
    game_map.LoadMap(link);
    game_map.LoadTiles(ss);

    
    while (!quit)
    {
        timer.start();
        Map map_data = game_map.getMap();
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.key.keysym.sym == SDLK_p || e.key.keysym.sym == SDLK_ESCAPE)
            {
                Mix_PlayChannel(-1, P_sound, 0);
                pause_point = 1;
                int ok = textofgame.ServiceProgram(ss, pause_font_text, "Continue", "Menu");
                if (ok == 0) pause_point = 0;
                else
                {
                    get_menu = textofgame.DemoMenu(ss, g_font_text);
                    refresh_point = 1;
                    if (get_menu == 0)
                        pause_point = 0;
                    else
                    {

                        while (get_menu != 0)
                        {
                            if (back_point == 1)
                            {
                                back_point = 0;
                                get_menu = textofgame.DemoMenu(ss, g_font_text);
                            }

                            if (get_menu == 1)
                            {
                                quit = true;
                                break;
                            }
                            else if (get_menu == 2)
                            {
                                int get_skin = textofgame.SkinShow(ss, g_font_text);
                                if (get_skin == 3)
                                {
                                    back_point = 1;
                                }
                                else if (get_skin == 0)
                                {
                                    player.SetSkinColor(1);//blue
                                    player.LoadImg("movement//B_right.png", ss);
                                }
                                else if (get_skin == 1)
                                {
                                    player.SetSkinColor(2);//green
                                    player.LoadImg("movement//G_right.png", ss);
                                }
                                else if(get_skin == 2)
                                {
                                    player.SetSkinColor(3);//red
                                    player.LoadImg("movement//R_right.png", ss);
                                }
                                else if (get_skin == 5)
                                {
                                    quit = true;
                                    break;
                                }
                                else if (get_skin == 4)
                                {
                                    get_menu = 0;
                                }
                            }
                            else if (get_menu == 3)
                            {
                                int get_level = textofgame.SelectLevel(ss, g_font_text);
                                if (get_level == 0)
                                {
                                    game_level = 1;
                                    get_menu = 0;
                                }
                                else if (get_level == 1)
                                {
                                    game_level = 2;
                                    get_menu = 0;
                                }
                                else if (get_level == 2) back_point = 1;
                                else if (get_level == -1)
                                {
                                    quit = true;
                                    break;
                                }
                                if (game_level == 1)
                                    link = "C://Users//ASUS//source//repos//Project1//map//map00.txt";
                                else if (game_level == 2)
                                    link = "C://Users//ASUS//source//repos//Project1//map//map02.txt";
                                game_map.LoadMap(link);
                                game_map.LoadTiles(ss);
                            }
                        }
                        pause_point = 0;
                    }/*if (get_menu == 1)
                        quit = true;*/


                }
            }
            player.HandleInputAction(e, ss);
        }

        if (refresh_point == 1)
        {
            cout << "be in refresh point" << endl;
            player.SetStatus();
            refresh_point = 0;
        }

        if (pause_point == 0)
        {
            SDL_SetRenderDrawColor(ss, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(ss);

            bg.Render(ss);
            game_map.DrawMap(ss);

            player.DoPlayper(map_data);
            player.Show(ss);

            if(player.CheckPos())
            {
                //again = 0;
                cout << "You won!" << endl;
                Mix_PlayChannel(-1, win_sound, 0);
                string text_ = "Continue";
                if (game_level == 2) text_ = "Exit";
                int ok2 = textofgame.ServiceProgram(ss, pause_font_text, text_, "Menu");
                if (ok2 == 1)
                {
                    get_menu = textofgame.DemoMenu(ss, g_font_text);
                    refresh_point = 1;
                    if (get_menu == 0)
                    {
                        pause_point = 0;
                        player.SetStatus();
                    }
                    else
                    {
                        while (get_menu != 0)
                        {
                            if (back_point == 1)
                            {
                                back_point = 0;
                                get_menu = textofgame.DemoMenu(ss, g_font_text);
                            }

                            if (get_menu == 1)
                            {
                                quit = true;
                                break;
                            }
                            else if (get_menu == 2)
                            {
                                int get_skin = textofgame.SkinShow(ss, g_font_text);
                                if (get_skin == 3)
                                {
                                    back_point = 1;
                                }
                                else if (get_skin == 0)
                                {
                                    player.SetSkinColor(1);//blue
                                    player.LoadImg("movement//B_right.png", ss);
                                }
                                else if (get_skin == 1)
                                {
                                    player.SetSkinColor(2);//green
                                    player.LoadImg("movement//G_right.png", ss);
                                }
                                else if (get_skin == 2)
                                {
                                    player.SetSkinColor(3);//red
                                    player.LoadImg("movement//R_right.png", ss);
                                }
                                else if (get_skin == 5)
                                {
                                    quit = true;
                                    break;
                                }
                                else if (get_skin == 4)
                                {
                                    get_menu = 0;
                                }
                            }
                            else if (get_menu == 3)
                            {
                                int get_level = textofgame.SelectLevel(ss, g_font_text);
                                if (get_level == 0)
                                {
                                    game_level = 1;
                                    get_menu = 0;
                                }
                                else if (get_level == 1)
                                {
                                    game_level = 2;
                                    get_menu = 0;
                                }
                                else if (get_level == 2) back_point = 1;
                                else if (get_level == 3) get_menu = 0;
                                else if (get_level == -1)
                                {
                                    quit = true;
                                    break;
                                }
                                if (game_level == 1)
                                    link = "C://Users//ASUS//source//repos//Project1//map//map00.txt";
                                else if (game_level == 2)
                                    link = "C://Users//ASUS//source//repos//Project1//map//map02.txt";
                                game_map.LoadMap(link);
                                game_map.LoadTiles(ss);
                            }
                        }
                        pause_point = 0;
                    }
                }
                else if (game_level == 1)
                {
                    link = "C://Users//ASUS//source//repos//Project1//image//map02.txt";
                    game_map.LoadMap(link);
                    game_map.LoadTiles(ss);
                    refresh_point = 1;
                }
                else if (game_level == 2) quit = true;
            }

            SDL_RenderPresent(ss);

            int real_time = timer.get_ticks();
            int time_one_frame = 1000 / 25;

            if (real_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_time;
                SDL_Delay(delay_time);
            }
        }
    }
    close();
    return 0;
}

