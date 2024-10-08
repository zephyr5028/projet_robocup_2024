//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor 1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0   // if 1 true,  0 false
#define debug 1  // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin 10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime;  // For non-blocking delays

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==========
// Variables
//==========
char caractere = '0';  // lecture can
int id = 0x0;          // valeur hexa de l'identification id sur le can bus
int flag_bras = 0;     // flag bras
int flag_extinction = 0;  // flag extinction de l'afficheur
int flag_demarrage = 0;   // flag demarrage du convoyeur
int flag_lache = 0;       // flag lache du cube
int flag_couleur = 0;     // flag couleur du cube
int flag_objet_present = 0 ; // sur le convoyeur
int flag_objet_absent = 0;  // sur le convoyeur
char couleur = '0';     // sauvegarde de la couleur
