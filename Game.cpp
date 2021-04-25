#include <iostream>

#include <string>

#include <ctime>



#include "SDL2/SDL.h"

#include "Game.hpp"



using namespace std;



Game::Game()

{
    // Khoi tao cac o rong.
    for (int i = 0; i < so_o_ngang; ++i)

        for (int j = 0; j < so_o_doc; ++j)

        {

            luoi[i][j] = Loai_o::empty;

        }



    srand(static_cast<unsigned int>(time(0)));

}



void Game::Chay_tro_choi()

{


    if (SDL_Init(SDL_INIT_VIDEO) < 0)

    {

        cerr << "Khong the khoi tao: loi " << SDL_GetError() << endl;

        exit(EXIT_FAILURE);

    }




    window = SDL_CreateWindow("Ran San Moi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,

        do_rong_man_hinh, do_cao_man_hinh, SDL_WINDOW_SHOWN);



    if (window == NULL)

    {

        cout << "Khong the khoi tao window: " << SDL_GetError() << endl;

        exit(EXIT_FAILURE);

    }




    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)

    {

        cout << "Loi hien thi: " << SDL_GetError() << endl;

        exit(EXIT_FAILURE);

    }



    con_song = true;

    dang_chay = true;

    Thay_the_thuc_an();

    Vong_lap_game();

}



void Game::Thay_the_thuc_an()

{
    // Toa do cua o do an.

    int x, y;

    // Tim kiem cac o trong luoi, neu tim duoc o trong thi dat do an vao.

    while (true)

    {
        // Khoi tao toa do ngau nhien.

        x = rand() % so_o_ngang;

        y = rand() % so_o_doc;


        // Neu dat thanh cong thi thoat ra khoi vong lap while.

        if (luoi[x][y] == Loai_o::empty)

        {

            luoi[x][y] = Loai_o::vi_tri_thuc_an;

            vi_tri_thuc_an.x = x;

            vi_tri_thuc_an.y = y;

            break;

        }

    }

}



void Game::Vong_lap_game()

{

    Uint32 truoc, so_giay = SDL_GetTicks(), sau;

    int khung_thoi_gian, khung_hinh = 0;



    while (dang_chay)

    {

        truoc = SDL_GetTicks();



        Xu_li_su_kien();

        Cap_nhat();

        Render();


        khung_hinh++;

        sau = SDL_GetTicks();

        khung_thoi_gian = sau - truoc;



        if (sau - so_giay >= 1000)

        {

            do_tre = khung_hinh;

            khung_hinh = 0;

            so_giay = sau;

            Cap_nhat_tieu_de();

        }



        if (FRAME_RATE > khung_thoi_gian)

        {

            SDL_Delay(FRAME_RATE - khung_thoi_gian);

        }

    }



}



void Game::Xu_li_su_kien()

{

    SDL_Event e;

    while (SDL_PollEvent(&e))

    {

        if (e.type == SDL_QUIT)

        {

            dang_chay = false;

        }

        else if (e.type == SDL_KEYDOWN)

        {

            switch (e.key.keysym.sym)

            {

                case SDLK_UP:

                    if (last_dir != kieu_di_chuyen::down || kich_co == 1)

                        dir = kieu_di_chuyen::up;

                    break;



                case SDLK_DOWN:

                    if (last_dir != kieu_di_chuyen::up || kich_co == 1)

                        dir = kieu_di_chuyen::down;

                    break;



                case SDLK_LEFT:

                    if (last_dir != kieu_di_chuyen::right || kich_co == 1)

                        dir = kieu_di_chuyen::left;

                    break;



                case SDLK_RIGHT:

                    if (last_dir != kieu_di_chuyen::left || kich_co == 1)

                        dir = kieu_di_chuyen::right;

                    break;

            }

        }

    }

}



int Game::Lay_kich_co()

{

    return kich_co;

}



void Game::Tang_than(int so_luong)

{

    tang += so_luong;

}



void Game::Cap_nhat()

{

    if (!con_song)

        return;



    switch (dir)

    {

        case kieu_di_chuyen::up:

            vi_tri_dau.y -= toc_do;

            vi_tri_dau.x = floorf(vi_tri_dau.x);

            break;



        case kieu_di_chuyen::down:

            vi_tri_dau.y += toc_do;

            vi_tri_dau.x = floorf(vi_tri_dau.x);

            break;



        case kieu_di_chuyen::left:

            vi_tri_dau.x -= toc_do;

            vi_tri_dau.y = floorf(vi_tri_dau.y);

            break;



        case kieu_di_chuyen::right:

            vi_tri_dau.x += toc_do;

            vi_tri_dau.y = floorf(vi_tri_dau.y);

            break;

    }




    if (vi_tri_dau.x < 0) vi_tri_dau.x = so_o_ngang - 1;

    else if (vi_tri_dau.x > so_o_ngang - 1) vi_tri_dau.x = 0;



    if (vi_tri_dau.y < 0) vi_tri_dau.y = so_o_doc - 1;

    else if (vi_tri_dau.y > so_o_doc - 1) vi_tri_dau.y = 0;



    int new_x = static_cast<int>(vi_tri_dau.x);

    int new_y = static_cast<int>(vi_tri_dau.y);




    if (new_x != head.x || new_y != head.y)

    {

        last_dir = dir;




        if (tang > 0)

        {

            kich_co++;

            than.push_back(head);

            tang--;

            luoi[head.x][head.y] = Loai_o::than;

        }

        else

        {


			// Tham khao tren mang.
            SDL_Point cot_chay = head;

            vector<SDL_Point>::reverse_iterator rit = than.rbegin();

            for ( ; rit != than.rend(); ++rit)

            {

                luoi[cot_chay.x][cot_chay.y] = Loai_o::than;

                swap(*rit, cot_chay);

            }



            luoi[cot_chay.x][cot_chay.y] = Loai_o::empty;

        }



    }



    head.x = new_x;

    head.y = new_y;



    Loai_o & next = luoi[head.x][head.y];


    if (next == Loai_o::vi_tri_thuc_an)

    {

        diem++;

        Thay_the_thuc_an();

        Tang_than(1);

    }


    else if (next == Loai_o::than)

    {

        con_song = false;

    }



    next = Loai_o::head;

}



int Game::Lay_diem()

{

    return diem;

}



void Game::Cap_nhat_tieu_de()

{

    string tieu_de_window = "Diem: " + to_string(diem);

    SDL_SetWindowTitle(window, tieu_de_window.c_str());

}



void Game::Render()

{

    SDL_Rect khoi_o;

    khoi_o.w = do_rong_man_hinh / so_o_ngang;

    khoi_o.h = do_rong_man_hinh / so_o_doc;




	// Mau nen.
    SDL_SetRenderDrawColor(renderer, 68, 102, 92, 40);

    SDL_RenderClear(renderer);




	// Mau o thuc an.
    SDL_SetRenderDrawColor(renderer, 245, 110, 41, 96);

    khoi_o.x = vi_tri_thuc_an.x * khoi_o.w;

    khoi_o.y = vi_tri_thuc_an.y * khoi_o.h;

    SDL_RenderFillRect(renderer, &khoi_o);




	// Mau cua than.
    SDL_SetRenderDrawColor(renderer, 89, 255, 245, 100);

    for (SDL_Point & point : than)

    {

        khoi_o.x = point.x * khoi_o.w;

        khoi_o.y = point.y * khoi_o.h;

        SDL_RenderFillRect(renderer, &khoi_o);

    }




    khoi_o.x = head.x * khoi_o.w;

    khoi_o.y = head.y * khoi_o.h;

	if (con_song)
	{
		// Mau cua dau.
		SDL_SetRenderDrawColor(renderer, 74, 255, 80, 100);
	}
	else
	{
		// Mau cua o bi dam.
		SDL_SetRenderDrawColor(renderer, 124, 98, 133, 52);
	}
	

    SDL_RenderFillRect(renderer, &khoi_o);




    SDL_RenderPresent(renderer);

}



void Game::Close()

{

    SDL_DestroyWindow(window);

    SDL_Quit();

}
