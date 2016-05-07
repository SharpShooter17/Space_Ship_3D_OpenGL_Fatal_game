//#include <SFML/Network.hpp>

bool DownloadFile()
{
    bool bReturn = true;

   /* sf::Ftp ftp;
    ftp.connect("cba.pl");
    ftp.login("admin", "haslo");

    sf::Ftp::ListingResponse response = ftp.getDirectoryListing();
    if (response.isOk()){
        ftp.download( "3DSpaceShip/ranking.txt", "", sf::Ftp::Ascii );
    } else {
        bReturn = false;
    }

    ftp.disconnect();
*/
    return bReturn;
}
