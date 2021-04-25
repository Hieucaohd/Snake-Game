#include <iostream>

#include "Game.hpp"



using namespace std;

void choi_game()
{
	Game game = Game();

	game.Chay_tro_choi();

	cout << "Diem cua ban la: " << game.Lay_diem() << endl;
	cout << "Kich thuoc ran cua ban la: "<< game.Lay_kich_co() << endl;
}

void chay_game()
{
	choi_game();
    SDL_Quit();
	
	while (true)
	{
		cout << "Ban co muon tiep tuc choi khong? (Y/n): ";

		char tra_loi;
		cin >> tra_loi;

		if (tra_loi == 'n' || tra_loi == 'N')
		{
			break;    
		}
		else if (tra_loi == 'Y' || tra_loi == 'y')
		{
		}
		else
		{
			cout << "Cau tra loi khong hop le." << endl;	
			break;
		}
		choi_game();
		SDL_Quit();
	} // End while.
}


int main(int argc, char * argv)
{
	chay_game();
    return 0;
}
