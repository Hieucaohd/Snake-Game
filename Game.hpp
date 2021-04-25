#pragma once

#include <vector>

#include "SDL2/SDL.h"

using namespace std;


class Game

{



public:



    Game();

    void Chay_tro_choi();

    int Lay_diem();

    int Lay_kich_co();



private:



    bool dang_chay = false;

    bool con_song = false;

    int do_tre = 0;



    static const int FRAME_RATE     = 1000 / 60;

    static const int do_rong_man_hinh   = 640;

    static const int do_cao_man_hinh  = 640;

    static const int so_o_ngang     = 32;

    static const int so_o_doc    = 32;



    SDL_Window * window = nullptr;

    SDL_Renderer * renderer = nullptr;



    enum class Loai_o { head, than, vi_tri_thuc_an, empty };

    enum class kieu_di_chuyen { up, down, left, right };



    kieu_di_chuyen last_dir = kieu_di_chuyen::up;

    kieu_di_chuyen dir = kieu_di_chuyen::up;



    struct { float x = so_o_ngang / 2, y = so_o_doc / 2; } vi_tri_dau;



    SDL_Point head = { static_cast<int>(vi_tri_dau.x), static_cast<int>(vi_tri_dau.y) };

    SDL_Point vi_tri_thuc_an;

    vector<SDL_Point> than;



    Loai_o luoi[so_o_ngang][so_o_doc];



    float toc_do = 0.5f;

    int tang = 0;

    int diem = 0;

    int kich_co = 1; // kich co ban dau co 1 o.



    void Thay_the_thuc_an();

    void Tang_than(int so_luong);

    void Cap_nhat_tieu_de();

    void Vong_lap_game();

    void Render();

    void Cap_nhat();

    void Xu_li_su_kien();

    void Close();

};

