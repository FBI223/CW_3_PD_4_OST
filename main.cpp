#include <iostream>
#include<fcntl.h>
#include <fstream>


using namespace std;


int readBMP_moj(char* filename_1 , char* filename_2  )
{

    const int max_size_arr = 65536 ;


    FILE* f = std::fopen(filename_1 , "rb") ;
    FILE* ff = std::fopen(filename_2 , "wb") ;

    int ile_padding_szer = 0;
    int ile_padding_wys = 0 ;

    unsigned char header[54] ;
    std::fread(header, sizeof(unsigned char), 54 , f )  ;


    cout<< *(int*)&header[18] << endl;
    cout<< *(int*)&header[22] << endl;
    cout<< *(int*)&header[44] << endl;
    cout<< *(int*)&header[46] << endl;
    cout<< *(int*)&header[48] << endl;
    cout<< *(int*)&header[50] << endl;
    cout<< *(int*)&header[0] << endl;




    std::fseek(f,0,SEEK_END) ;
    const int poczatek_pixeli = *(int*)&header[10] ;
    const long long int rozmiar_pliku =  std::ftell(f) ;
    int szerokosc = *(int*)&header[18] ;
    if ( (szerokosc ) != ((szerokosc / 4 )*4 ) )
    {
        ile_padding_szer = ( (szerokosc ) - ((szerokosc / 4 )*4 ) ) ;
    }

    int wysokosc = *(int*)&header[22] ;
    {
        ile_padding_wys = ( (wysokosc ) - ((wysokosc / 4 )*4 ) ) ;
    }
    long long int ile_pikseli = (szerokosc+ile_padding_szer)* (wysokosc+ile_padding_wys)*3 ;
    unsigned char* dynamic_arr = new unsigned char[ile_pikseli] ;
    long long int ile_pikseli_padding = (ile_pikseli - ( wysokosc*szerokosc*3 ))*3 ;
    const int dlg_arr_reszty = rozmiar_pliku - ile_pikseli - 54 ;
    unsigned char reszta[dlg_arr_reszty] ;
    std::fseek(f,54+ile_pikseli,SEEK_SET) ;
    std::fread(header, sizeof(unsigned char), dlg_arr_reszty , f ) ;

    int ile_pikslei_wcz = 0;
    long long int ile_pikseli_wczytales = 0;
    int czy_koniec = 0 ;


    std::fseek(f,54,SEEK_SET) ;
    std::fwrite(header,sizeof(unsigned char),54,ff) ;
    std::fseek(f,54,SEEK_CUR) ;
    std::fread(dynamic_arr, sizeof(unsigned char),ile_pikseli , f) ;
//    std::fseek(f,54,SEEK_SET) ;
    int row_size = wysokosc*3 ;
    int column_size = szerokosc*3 ;
    int ktory_piksel = 0 ;
    int ktory_row = 0;

    long long int i_dynamic = 0;
    while ( i_dynamic < ile_pikseli )
    {
        dynamic_arr[i_dynamic] = 255;
        i_dynamic+= 3 ;

    }


    ile_pikslei_wcz = std::fwrite(dynamic_arr,sizeof(unsigned char),ile_pikseli,ff) ;

//
//
//    while ( czy_koniec == 0  )
//    {
//        unsigned char temp_arr[max_size_arr ] ;
//        ile_pikslei_wcz = std::fread(temp_arr,sizeof(unsigned char),max_size_arr,f) ;
//        cout << ile_pikslei_wcz << endl;
//
//        for (int i = 0 ; i < max_size_arr ; i+=18 )
//        {
//
//            temp_arr[i + ktory_piksel] = 255;
////            ktory_piksel++;
////            if ( ktory_piksel == 3 )
////            {
////                ktory_piksel = 0;
////            }
//
//        }
//
//        // 81 paskow
//
//        std::fwrite(temp_arr,sizeof(unsigned char),ile_pikslei_wcz,ff) ;
//
////        ktory_piksel = 0;
////        if ( ktory_piksel == 3 )
////        {
////            ktory_piksel = 0;
////        }
//
//        ile_pikseli_wczytales += ile_pikslei_wcz ;
//
//        if ( ile_pikseli_wczytales >= ile_pikseli )
//        {
//            czy_koniec = 1 ;
//        }
//
//
//    }
//
//    cout << " flaga " << endl;
//
//    long long int ile_mozesz_Wczytac_pikseli = 0;
//    long long int ile_pikseli_paddingg_tylko = ile_pikseli_padding - ile_pikseli ;
//    long long int ile_wczytales_pikslei_w_paddingu = 0;
//    czy_koniec = 0;
//
//    unsigned char temp_arr[max_size_arr ] ;
//
//    for (int i = 0 ; i < max_size_arr ; i+=3)
//    {
//        temp_arr[i] = 255 ;
//        temp_arr[i+1] = std::rand() / 255 ;
//        temp_arr[i+2] = std::rand() / 255 ;
//    }
//
//    std::fwrite(temp_arr,sizeof(unsigned char),ile_pikseli_paddingg_tylko,ff) ;

//
//
//    int j = 0 ;
//    while ( j < ile_pikseli_paddingg_tylko)
//    {
//        unsigned char temp_arr[max_size_arr ] ;
//
//        for (int i = 0 ; i < max_size_arr ; i+=3)
//        {
//            temp_arr[i] = 255 ;
//            temp_arr[i+1] = std::rand() / 255 ;
//            temp_arr[i+2] = std::rand() / 255 ;
//        }
//
//
//
//    }
//

//
//    while ( (czy_koniec == 0) && (ile_pikseli_padding != 0) )
//    {
//        unsigned char temp_arr[max_size_arr ] ;
//
//        for (int i = 0 ; i < max_size_arr ; i+=3)
//        {
//            temp_arr[i] = 255 ;
//            temp_arr[i+1] = std::rand() / 255 ;
//            temp_arr[i+2] = std::rand() / 255 ;
//        }
//
//        std::fwrite(temp_arr,sizeof(unsigned char),ile_pikslei_wcz,ff) ;
//
//        ile_pikseli_wczytales += ile_pikslei_wcz ;
//
//        if ( ile_pikseli_wczytales >= ile_pikseli )
//        {
//            czy_koniec = 1 ;
//        }
//
//
//    }


    std::fwrite(reszta,sizeof(unsigned char),dlg_arr_reszty,ff) ;



//    streambuf *cout_old_buf = nullptr ;
//    ofstream out;
//    out.open("C:\\Users\\msztu\\Pictures\\wartosci_przed_i_po.txt", ios::out) ;
//    cout_old_buf = cout.rdbuf() ;
//    cout.rdbuf( out.rdbuf() ) ;

    //std::fseek(f,0,SEEK_END) ;
    cout << " flaga " << endl;



    cout << " ftell "<< rozmiar_pliku << endl;




    //cout << " flaga " << endl;

    //std::fseek(f,0,SEEK_SET ) ;
    //cout << " flaga " << endl;
    //std::fread(temp_arr, sizeof(unsigned char), rozmiar_pliku , f ) ;

    //cout << " flaga " << endl;




    cout << szerokosc << endl;
    cout << wysokosc << endl;


//    int temp_int = 0;
//
//    int countt = 0;
//    int i = poczatek_pixeli ;
//    int ile_pikseli_lacznie = szerokosc*wysokosc*3 ;
//    while ( i < ile_pikseli_lacznie )
//    {
//
//        // as (B, G, R) triples, not (R, G, B)
//        // B G R
//
//        //temp_arr[i] = 250  ;
//        //cout <<"PIXEL PO      ,nr : "<< countt <<"        X1 : " << (int)temp_arr[i] << "     x2 : " << (int)temp_arr[i+1] << "    x3 : " << (int)temp_arr[i+2] << endl;
//        //cout << endl << endl;
//
//        countt += 1 ;
//        i+=3;
//    }


    int info_1;
    //info_1 = std::fwrite(temp_arr, sizeof(unsigned char) , rozmiar_pliku , ff ) ;


    //cout.rdbuf(cout_old_buf) ;
    std::fclose(f) ;
    std::fclose(ff) ;

    //out.close() ;

    return 0;
}


int main() {

    readBMP_moj("C:\\Users\\msztu\\Pictures\\krakow.bmp" , "C:\\Users\\msztu\\Pictures\\krakow_nowy.bmp") ;

    cout << "Hello, World!" << endl;
    return 0;
}
